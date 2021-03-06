/* WorldClock: a multiple time-zone clock for a 16x2 display
 * Copyright 2015, James Lyden <james@lyden.org>
 * This code is licensed under the terms of the GNU General Public License.
 * See COPYING, or refer to http://www.gnu.org/licenses, for further details.
 *
 * Setup requires configuring the serial port as needed by the SerLCD backpack,
 * getting the current time from the RTC, and setting the initial configurable
 * variables (such as timezones to display) from the internal EEPROM.
 *
 * Input handling is performed in the main loop. Updates from the RTC trigger an
 * interrupt handler, and display updates are triggered asynchronously via flag.
 */

#include <SoftwareSerial.h>
#include <EEPROM.h>
#include "timezones.h"
#include "WorldClock.h"
#include "IO.h"
// FIXME-RTC: for RTC simulation only
#include <TimerOne.h>

// GLOBAL VARIABLES

// persistent tracking of selected timezone data
int tz[SZ_TZ];
bool tzDst[SZ_TZ], tzNext[SZ_TZ], tzPrev[SZ_TZ];
char tzLabel[SZ_TZ][SZ_LABEL];

// current date/time in UTC
volatile int realtime[SZ_TIME];		// updated by interrupt
int time[SZ_TIME];						// copied from realtime[] outside of interrupt
volatile bool fUpdateTime = false;	// trigger copy in main loop
int ltime[SZ_TIME];						// synced to/from time[] when requested

// display attributes
bool heartbeat = false;
bool primaryView = true;
volatile bool fUpdateDisp = false;
volatile bool fRedrawDisp = false;

// display devices
SoftwareSerial LCD0(LCD0_IN ,LCD0_OUT);
SoftwareSerial LCD1(LCD1_IN, LCD1_OUT);

// MANDATORY FUNCTIONS

void setup() {
	// configure hardware first
	pinMode(BUTTON[UP], INPUT);
	pinMode(BUTTON[DN], INPUT);
	pinMode(BUTTON[LT], INPUT);
	pinMode(BUTTON[RT], INPUT);
	pinMode(BUTTON[OK], INPUT);
	LCD0.begin(9600);
	LCD1.begin(9600);

	// backlight to max
	setBacklight(LCD0, ON);
	setBacklight(LCD1, ON);

	// LCD needs time to settle
	delay(250);

	// configure splash screen
	setSplash(LCD0);
	setSplash(LCD1);
	delay(250);

	// FIXME-RTC: set clock vars from RTC
	// FIXME-RTC: remove hardcoded values once RTC is online
	time[YEAR] = 15;
	time[MONTH] = 3;
	time[DAY] = 7;
	time[DOW] = 6;
	time[HOUR] = 0;
	time[MINUTE] = 30;
	time[SECOND] = 55;
	for (int t = 0; t < SZ_TIME; t++) realtime[t] = time[t];

	// FIXME-RTC: setup one second timer
	Timer1.initialize(1000000);
	Timer1.attachInterrupt(updateTime);
	Timer1.start();

	// initialize timezone values
	for (int t = 0; t < SZ_TZ; t++) {
		tz[t] = EEPROM.read(MEM_TZ + t);
		tzDst[t] = isDst(tz[t]);
		tzNext[t] = isNextDay(tz[t]);
		tzPrev[t] = isPrevDay(tz[t]);
		for (int c = 0; c < SZ_LABEL; c++) {
			tzLabel[t][c] = (char)EEPROM.read(MEM_LABEL + (t * SZ_LABEL) + c);
		}
	}

/* FIXME-CONFIG: sample values to load into EEPROM until runtime config is coded
 * Insert EEPROM.write() calls into last portion of setup() immediately prior to
 * the equivalent EEPROM.read() calls.
	int tzload[SZ_TZ] = { 137, 69, 143, 130, 2, 2, 10};
	int tznames[SZ_TZ][SZ_LABEL] = { "Calif", "Japan", "Hawaii", "Wash DC", "Spain", "Italy", "Bahrain"};
		EEPROM.write(MEM_TZ + t, tzload[t]);
			EEPROM.write(MEM_LABEL + (t * SZ_LABEL) + c, tznames[t][c]);
*/
	clearScreen(LCD0);
	clearScreen(LCD1);
}

void loop() {
	// handle inputs
	if (PRESSED(OK)) {
		if (primaryView) primaryView = false;
		else primaryView = true;
		fRedrawDisp = true;
		delay(IODELAY);
	}
	if (PRESSED(RIGHT)) {
		noInterrupts();
		realtime[HOUR]++;
		interrupts();
		fUpdateDisp = true;
		delay(IODELAY);
	}
	if (PRESSED(LEFT)) {
		noInterrupts();
		realtime[HOUR]--;
		interrupts();
		fUpdateDisp = true;
		delay(IODELAY);
	}

	if (PRESSED(DOWN)) {
		noInterrupts();
		realtime[MINUTE]++;
		interrupts();
		fUpdateDisp = true;
		delay(IODELAY);
	}
	if (PRESSED(UP)) {
		noInterrupts();
		realtime[MINUTE]--;
		interrupts();
		fUpdateDisp = true;
		delay(IODELAY);
	}

	// update non-volatile time
	if (fUpdateTime) {
		noInterrupts();
		for (int t = 0; t < SZ_TIME; t++) time[t] = realtime[t];
		interrupts();
		fUpdateTime = false;
	}

	// redraw display
	if (fRedrawDisp) {
		updateDisp(true);
		fRedrawDisp = false;
		fUpdateDisp = false;
	}
	if (fUpdateDisp) {
		updateDisp();
		fUpdateDisp = false;
	}

	// for stability
	delay(1);
}

// DATE/TIME FUNCTIONS

// get the current time and date from the RTC once a minute, just increment seconds otherwise
// FIXME-RTC: stub will require replacement once the RTC is integrated.
void updateTime() {
	fUpdateTime = true;
	fUpdateDisp = true;

	// currently faking time using built-in timers, will be replaced with RTC reads
	realtime[SECOND]++;
	if (realtime[SECOND] > 59) {
		realtime[SECOND] = 0;
		realtime[MINUTE]++;
	}
	// once seconds-to-minutes is taken care of, use normalizeDateTime to fix the rest
	int nminute = realtime[MINUTE], nhour = realtime[HOUR], ndow = realtime[DOW];
	int nday = realtime[DAY], nmonth = realtime[MONTH], nyear = realtime[YEAR];
	normalizeDateTime(&nminute, &nhour, &ndow, &nday, &nmonth, &nyear);
	realtime[MINUTE] = nminute;
	realtime[HOUR] = nhour;
	realtime[DOW] = ndow;
	realtime[DAY] = nday;
	realtime[MONTH] = nmonth;
	realtime[YEAR] = nyear;
}

// populate time[] by adjusting ltime[] into UTC
void localToUtc(int tznum) {
	if (tznum == TZ_UTC) {
		for (int t = 0; t < SZ_TIME; t++) {
			time[t] = ltime[t];
		}
		return;
	}
	int udow = time[DOW], uday = time[DAY], umonth = time[MONTH], uyear = time[YEAR];
	int umin = time[MINUTE] - LOADINT(TZ_MIN + tznum);
	int uhour = time[HOUR] - LOADINT(TZ_HOUR + tznum);
	if (isDst(tznum)) uhour--;

	normalizeDateTime(&umin, &uhour, &udow, &uday, &umonth, &uyear);
	time[MINUTE] = umin;
	time[HOUR] = uhour;
	time[DOW] = udow;
	time[DAY] = uday;
	time[MONTH] = umonth;
	time[YEAR] = uyear;

	// last steps need to be copying time[] to realtime[], then setting RTC to realtime[]
	noInterrupts();
	for (int t = 0; t < SZ_TIME; t++) realtime[t] = time[t];
	interrupts();
	return;
}

// populate ltime[] by adjusting time[] into the provided timezone
void utcToLocal(int tznum) {
	if (tznum == TZ_UTC) {
		for (int t = 0; t < SZ_TIME; t++) {
			ltime[t] = time[t];
		}
		return;
	}

	int ldow = time[DOW], lday = time[DAY], lmonth = time[MONTH], lyear = time[YEAR];
	int lmin = time[MINUTE] + LOADINT(TZ_MIN + tznum);
	int lhour = time[HOUR] + LOADINT(TZ_HOUR + tznum);

	// isDst requires an up-to-date ltime, so normalize and dump before calling
	normalizeDateTime(&lmin, &lhour, &ldow, &lday, &lmonth, &lyear);
	ltime[MINUTE] = lmin;
	ltime[HOUR] = lhour;
	ltime[DOW] = ldow;
	ltime[DAY] = lday;
	ltime[MONTH] = lmonth;
	ltime[YEAR] = lyear;

	if (isDst(tznum)) lhour++;

	// then again afterward in case the shift caused lhour to overflow
	normalizeDateTime(&lmin, &lhour, &ldow, &lday, &lmonth, &lyear);
	ltime[MINUTE] = lmin;
	ltime[HOUR] = lhour;
	ltime[DOW] = ldow;
	ltime[DAY] = lday;
	ltime[MONTH] = lmonth;
	ltime[YEAR] = lyear;
}

// Normalize date/time based on standard ruleset. This function is only able to
// fully normalize date/times where each value is no more than one "decade" off
// (for instance, the myhours value must fall in the range -24 < *myhour < 47).
void normalizeDateTime(int* mymin, int* myhour,  int* mydow,  int* myday,  int* mymonth,  int* myyear) {
	if (*mymin < 0) {
		--*myhour;
		*mymin += 60;
	}
	else if (*mymin > 59) {
		++*myhour;
		*mymin -= 60;
	}

	if (*myhour < 0) {
		--*myday;
		--*mydow;
		*myhour += 24;
	}
	else if (*myhour > 23) {
		++*myday;
		++*mydow;
		*myhour -= 24;
	}

	normalizeDate(mydow, myday, mymonth, myyear);
}

// like normalizeDateTime, but for date only
void normalizeDate(int* mydow, int* myday, int* mymonth, int* myyear) {
	int leapfactor = 0;
	if ((*mymonth == 2) && (((*myyear % 4) == 0) && (*myyear % 100) != 0)) leapfactor = 1;

	if (*mydow < 0) *mydow += 7;
	if (*mydow > 6) *mydow -= 7;

	if (*myday < 1) {
		--*mymonth;
		if (*mymonth < 1) {
			*mymonth += 12;
			--*myyear;
		}
		// recalculate leapfactor since month changed
		if ((*mymonth == 2) && (((*myyear % 4) == 0) && ((*myyear % 100) != 0))) leapfactor = 1;
		*myday += (SZ_MONTH[*mymonth] + leapfactor);
	}

	else if (*myday > (SZ_MONTH[*mymonth] + leapfactor)) {
		++*mymonth;
		if (*mymonth > 12) {
			*mymonth -= 12;
			++*myyear;
		}
		// recalculate leapfactor since month changed (but we need the previous month's size)
		if (((*mymonth - 1) == 2) && (((*myyear % 4) == 0) && ((*myyear % 100) != 0))) leapfactor = 1;
		*myday -= (SZ_MONTH[(*mymonth - 1)] + leapfactor);
	}
}

// determine if it is currently daylight savings time by deduction
bool isDst(int tznum) {
	int ds = LOADBYTE(TZ_DST + tznum);
	// return immediately if not a DST time zone
	if (ds == DS_NONE) return false;

	int m = ltime[MONTH], sm = DS_SMON[ds], fm = DS_FMON[ds], sd, fd;

	// if day of month provided, just use that...
	if (DS_SDAY[ds]) sd = DS_SDAY[ds];
	// otherwise, calculate start and end calendar days assuming we're in the right month
	else {
		int sdow = DS_SDOW[ds], syear = ltime[YEAR];
		sd = ((ltime[DAY] - ltime[DOW] + sdow) % 7) + (7 * (DS_SWEEK[ds] - 1));
		if (sd < 1) normalizeDate(&sdow, &sd, &sm, &syear);
	}

	// ditto for finish day
	if (DS_FDAY[ds]) fd = DS_FDAY[ds];
	else {
		int fdow = DS_FDOW[fd], fyear = ltime[YEAR];
		fd = ((ltime[DAY] - ltime[DOW] + DS_FDOW[ds]) % 7) + (7 * (DS_FWEEK[ds] - 1));
		if (fd < 1) normalizeDate(&fdow, &fd, &fm, &fyear);
	}

	// re-order month values (if necessary) then compare
	if (sm > fm) {
		fm += 12;
		m += 12;
	}
	if (m < sm || m > fm) return false;
	if (m == sm && ltime[DAY] < sd) return false; 
	if (m == fm && ltime[DAY] > sd) return false; 

	// at this point, it's not *not* DST, so return true
	return true;
}

// determine if it is currently the next day in specified timezone
bool isNextDay(int tznum) {
	// add 24 hours/60 minute offsets to work around some apparent unsigned/signed casting issue
	int thatTzHour = LOADINT(TZ_HOUR + tznum) + 24, thatTzMin = LOADINT(TZ_MIN + tznum)+ 60;
	int thisTzHour = LOADINT(TZ_HOUR + tz[TZ_LOCAL]) + 24, thisTzMin = LOADINT(TZ_MIN + tz[TZ_LOCAL]) + 60;
	// only possible for timezones larger than local
	if (thatTzHour > thisTzHour) return false;
	if (thatTzMin > thisTzMin) return false;

	utcToLocal(tznum);
	int thatDay = ltime[DAY];
	utcToLocal(tz[TZ_LOCAL]);
	int thisDay = ltime[DAY];
	if (thisDay != thatDay) return true;
	return false;
}

// determine if it is currently the previous day in specified timezone
bool isPrevDay(int tznum) {
	// add 24 hours/60 minute offsets to work around some apparent unsigned/signed casting issue
	int thatTzHour = LOADINT(TZ_HOUR + tznum) + 24, thatTzMin = LOADINT(TZ_MIN + tznum)+ 60;
	int thisTzHour = LOADINT(TZ_HOUR + tz[TZ_LOCAL]) + 24, thisTzMin = LOADINT(TZ_MIN + tz[TZ_LOCAL]) + 60;
	// only possible for timezones smaller than local
	if (thatTzHour < thisTzHour) return false;
	if (thatTzMin < thisTzMin) return false;

	utcToLocal(tznum);
	int thatday = ltime[DAY];
	utcToLocal(tz[TZ_LOCAL]);
	int thisday = ltime[DAY];
	if (thisday != thatday) return true;
	return false;
}

// DISPLAY FUNCTIONS

// render the date and clocks (local, zulu, tz1-tz3) to the displays
void updateDisp(bool refresh) {
	// build formatted times
	char date[8], dow[8], utcTime[8], dispTime[SZ_TZ][8];
   char dst [SZ_TZ], day[SZ_TZ], dayUtc;  // symbols for DST, previous/next day

	// set indicator characters first
	for (int t = 0; t < SZ_TZ; t++) {
		// day: next, prev, or blank
		if (isNextDay(tz[t])) day[t] = SYM_NEXTDAY;
		else if (isPrevDay(tz[t])) day[t] = SYM_PREVDAY;
		else day[t] = ' ';
		#ifdef SHOWDST
		if(isDst(tz[t])) dst[t] = SYM_DST;
		else dst[t] = ' ';
		#else
		dst[t] = ' ';
		#endif
	}
	if (isNextDay(TZ_UTC)) dayUtc = SYM_NEXTDAY;
	else if (isPrevDay(TZ_UTC)) dayUtc = SYM_PREVDAY;
	else dayUtc = ' ';

	// populate UTC
   sprintf(utcTime, "%c%02d:%02dZ", dayUtc, time[HOUR], time[MINUTE]);
	// make adjustments for localized times
	utcToLocal(tz[TZ_LOCAL]);
	sprintf(date, "%02d%s%02d", ltime[DAY], MON_NAME[ltime[MONTH]], ltime[YEAR]);
	sprintf(dow, "  %s  ", DOW_NAME[ltime[DOW]]);
	// populate time strings for every time zone other than UTC
	for (int t = 0; t < SZ_TZ; t++) {
		utcToLocal(tz[t]);
		sprintf(dispTime[t], "%c%02d:%02d%c", day[t], ltime[HOUR], ltime[MINUTE], dst[t]);
	}

	if (refresh) {
		clearScreen(LCD0);
		clearScreen(LCD1);
	}
	
	// print date, time, and UTC
	if (primaryView) {
		printAt(LCD0, 0, 0, date);
		printAt(LCD0, 1, 0, dow);
		printAt(LCD0, 0, 9, dispTime[0]);
		printAt(LCD0, 1, 9, utcTime);
		// draw heartbeat
		if (time[SECOND] % 2) {
			printAt(LCD0, 0, 12, " ");
		}
		// print additional time zones
		printAt(LCD1, 0, 0, dispTime[1]);
		printAt(LCD1, 1, 1, tzLabel[1]);
		printAt(LCD1, 0, 8, dispTime[2]);
		printAt(LCD1, 1, 9, tzLabel[2]);
	} else {
		printAt(LCD0, 0, 0, dispTime[3]);
		printAt(LCD0, 1, 1, tzLabel[3]);
		printAt(LCD0, 0, 8, dispTime[4]);
		printAt(LCD0, 1, 9, tzLabel[4]);
		printAt(LCD1, 0, 0, dispTime[5]);
		printAt(LCD1, 1, 1, tzLabel[5]);
		printAt(LCD1, 0, 8, dispTime[6]);
		printAt(LCD1, 1, 9, tzLabel[6]);
	}
}

// LCD HELPERS

// printAt prints the provided string onto the provided display at the specified
// row and column (zero-indexed)
void printAt(SoftwareSerial &disp, int row, int column, const char* str) {
	moveCursor(disp, row, column);
	disp.print(str);
}

// moveCursor moves to the specified row and column (zero-indexed)
void moveCursor(SoftwareSerial &disp, int row, int col) {
	// error checking
	if (row < 0 || row > 1 || col < 0 || col > 15) return;

	// set cursor
	disp.write(0xFE);
	disp.write((row * 0x40) + col + 0x80);
	delay(1);
}

// clearScreen erases all characters from the display
void clearScreen(SoftwareSerial &disp) {
	disp.write(0xFE);
	disp.write(0x01);
	delay(1);
}

// setSplash configures the splash screen
void setSplash(SoftwareSerial &disp) {
	disp.print(F("   WorldClock   "));
	disp.print(F("  (multi-zone)  "));
	disp.write(0x7C);
	disp.write(0x0A);
}

// setBacklight turns on or off the backlight
void setBacklight(SoftwareSerial &disp, bool state) {
	int blPower = 0x80;

	if (state) blPower = 0x9D;

	disp.write(0x7C);
	disp.write(blPower);
}
