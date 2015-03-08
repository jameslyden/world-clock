/* WorldClock: a multiple time-zone clock for a 16x2 display
 * Copyright 2015, James Lyden <james@lyden.org>
 * This code is licensed under the terms of the GNU General Public License.
 * See COPYING, or refer to http://www.gnu.org/licenses, for further details.
 *
 * This file contains the function prototypes, constants, and configurable
 * variables for WorldClock.
 */

// timezone attributes
#define SZ_TZ			7		// total number of timezones to manage
#define SZ_LABEL		8		// number of characters to allow for labels (+1 for null terminator)
#define TZ_LOCAL		0		// index of local time

// date/time attributes
#define SZ_TIME		7		// must be equal to total number of indices below
#define YEAR			0		// indices into the date/time array (must be sequential)
#define MONTH			1
#define DAY				2
#define DOW				3
#define HOUR			4
#define MINUTE			5
#define SECOND			6

// EEPROM memory locations for config values
#define MEM_TZ			0x00	// Starting point for TZ indices
#define MEM_LABEL		0x20	// starting point for timezone labels

// special display characters
#define SYM_DST		0xEB	// superscript X
#define SYM_NEXTDAY	0xDF	// high dot
#define SYM_PREVDAY	0xA1	// low dot
#define SYM_LARROW	0x7F	// left arrow
#define SYM_RARROW	0x7E	// right arrow
#define SYM_LINE		0xFF	// thick vertical line
#define SYM_BOX		0xDB	// rectangular box

// alternate to true/false for booleans
#define ON	true
#define OFF false

// number-to-text mappings
const char* DOW_NAME[] = {
	"Sun",
	"Mon",
	"Tue",
	"Wed",
	"Thu",
	"Fri",
	"Sat" };

const char* MON_NAME[] = {
	"   ",
	"JAN",
	"FEB",
	"MAR",
	"APR",
	"MAY",
	"JUN",
	"JUL",
	"AUG",
	"SEP",
	"OCT",
	"NOV",
	"DEC" };

const short SZ_MONTH[] = {
	31, // december, rolled over
	31,
	28,
	31,
	30,
	31,
	30,
	31,
	31,
	30,
	31,
	30,
	31 };

// function prototypes
void updateDisp();
void updateTime();
void utcToLocal(short tznum);
void localToUtc(short tznum);
void normalizeDateTime(short* minute, short* hour, short* dow, short* day, short* month, short* year);
void normalizeDate(short* dow, short* day, short* month, short* year);
bool isDst(short tznum);
bool isNextDay(short tznum);
bool isPrevDay(short tznum);
void moveCursor(SoftwareSerial &disp, short row, short col);
void clearScreen(SoftwareSerial &disp);
void setSplash(SoftwareSerial &disp);
void setBacklight(SoftwareSerial &disp, bool state);

