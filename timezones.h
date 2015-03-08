/* WorldClock: a multiple time-zone clock for a 16x2 display
 * Copyright 2015, James Lyden <james@lyden.org>
 * This code is licensed under the terms of the GNU General Public License.
 * See COPYING, or refer to http://www.gnu.org/licenses, for further details.
 *
 * This header builds the data structures for timezone attributes, including:
 *   TZ_<abbr> Timezone abbreviation for indexing the following arrays
 *   TZ_NAME	The proper name for that timezone
 *   TZ_LOC		Representative location in that timezone
 *   TZ_HOUR	Offset from UTC (hours)
 *   TZ_MIN		Offset from UTC (minutes)
 *   TZ_DST		Which daylight savings rules to apply to this timezone
 *   DS_<name>	Human-readable DST ruleset for indexing into the following arrays
 *   DS_SMON	Numeric month when DST starts
 *   DS_SDOW	Numeric day of the week when DST starts
 *   DS_FMON	Numeric month when DST finishes
 *   DS_FDOW	Numeric day of the week when DST finishes
 *   DS_SDAY	Numeric day of the month when DST starts
 *   DS_FDAY	Numeric day of the month when DST finishes
 */

// macro to simplify reading from PROGMEM arrays
#define LOAD(x) pgm_read_word_near(x)

// timezone name macros
#define TZ_ZULU	0
#define TZ_UTC	0
#define TZ_WET	1
#define TZ_CET	2
#define TZ_IRLT	3
#define TZ_WAT	4
#define TZ_CAT	5
#define TZ_EET	6
#define TZ_IST	7
#define TZ_SAST	8
#define TZ_USZ1	9
#define TZ_ARST	10
#define TZ_EAT	11
#define TZ_FET	12
#define TZ_IOT	13
#define TZ_MSK	14
#define TZ_SYOT	15
#define TZ_IRST	16
#define TZ_AMT	17
#define TZ_AZT	18
#define TZ_GET	19
#define TZ_GST	20
#define TZ_MUT	21
#define TZ_RET	22
#define TZ_SAMT	23
#define TZ_SCT	24
#define TZ_VOLT	25
#define TZ_AFT	26
#define TZ_HMT	27
#define TZ_MAWT	28
#define TZ_MVT	29
#define TZ_ORAT	30
#define TZ_PKT	31
#define TZ_TFT	32
#define TZ_TJT	33
#define TZ_TMT	34
#define TZ_UZT	35
#define TZ_YEKT	36
#define TZ_INST	37
#define TZ_SLST	38
#define TZ_NPT	39
#define TZ_BIOT	40
#define TZ_BST	41
#define TZ_BTT	42
#define TZ_KGT	43
#define TZ_OMST	44
#define TZ_VOST	45
#define TZ_CCT	46
#define TZ_MMT	47
#define TZ_CXT	48
#define TZ_DAVT	49
#define TZ_HOVT	50
#define TZ_ICT	51
#define TZ_KRAT	52
#define TZ_THA	53
#define TZ_WIT	54
#define TZ_ACT	55
#define TZ_AWST	56
#define TZ_BDT	57
#define TZ_CHOT	58
#define TZ_CIT	59
#define TZ_CT	60
#define TZ_HKT	61
#define TZ_IRKT	62
#define TZ_MYT	63
#define TZ_PHST	64
#define TZ_SGT	65
#define TZ_ULAT	66
#define TZ_WST	67
#define TZ_EIT	68
#define TZ_JST	69
#define TZ_KST	70
#define TZ_TLT	71
#define TZ_YAKT	72
#define TZ_ACST	73
#define TZ_AEST	74
#define TZ_ChST	75
#define TZ_CHUT	76
#define TZ_DDUT	77
#define TZ_PGT	78
#define TZ_VLAT	79
#define TZ_LHST	80
#define TZ_KOST	81
#define TZ_MIST	82
#define TZ_NCT	83
#define TZ_PONT	84
#define TZ_SAKT	85
#define TZ_SBT	86
#define TZ_SRET	87
#define TZ_VUT	88
#define TZ_NFT	89
#define TZ_FJT	90
#define TZ_GILT	91
#define TZ_MAGT	92
#define TZ_MHT	93
#define TZ_NZST	94
#define TZ_PETT	95
#define TZ_TVT	96
#define TZ_WAKT	97
#define TZ_CHAST	98
#define TZ_PHOT	99
#define TZ_TKT	100
#define TZ_TOT	101
#define TZ_LINT	102
#define TZ_AZOST	103
#define TZ_CVT	104
#define TZ_EGT	105
#define TZ_FNT	106
#define TZ_SGST	107
#define TZ_ART	108
#define TZ_BRT	109
#define TZ_FKST	110
#define TZ_GFT	111
#define TZ_PMST	112
#define TZ_ROTT	113
#define TZ_SRT	114
#define TZ_UYT	115
#define TZ_NT	116
#define TZ_AMZT	117
#define TZ_AST	118
#define TZ_BOT	119
#define TZ_CLT	120
#define TZ_COST	121
#define TZ_ECT	122
#define TZ_FKT	123
#define TZ_GYT	124
#define TZ_PYT	125
#define TZ_VET	126
#define TZ_COT	127
#define TZ_CUST	128
#define TZ_ECUT	129
#define TZ_EST	130
#define TZ_PET	131
#define TZ_CST	132
#define TZ_EAST	133
#define TZ_GALT	134
#define TZ_MST	135
#define TZ_CIST	136
#define TZ_PST	137
#define TZ_AKST	138
#define TZ_GIT	139
#define TZ_MART	140
#define TZ_CKT	141
#define TZ_HAST	142
#define TZ_HST	143
#define TZ_TAHT	144
#define TZ_NUT	145
#define TZ_SST	146
#define TZ_BIT	147

/* full names take up far too much space -- maybe move to progmem later
const char* TZ_NAME[] = {
	"Coordinated Universal Time",
	"Western European Time",
	"Central European Time",
	"Irish Standard Time",
	"West Africa Time",
	"Central Africa Time",
	"Eastern European Time",
	"Israel Standard Time",
	"South African Standard Time",
	"Kaliningrad Time",
	"Arabia Standard Time",
	"East Africa Time",
	"Further-eastern European Time",
	"Indian Ocean Time",
	"Moscow Time",
	"Showa Station Time",
	"Iran Standard Time",
	"Armenia Time",
	"Azerbaijan Time",
	"Georgia Standard Time",
	"Gulf Standard Time",
	"Mauritius Time",
	"Réunion Time",
	"Samara Time",
	"Seychelles Time",
	"Volgograd Time",
	"Afghanistan Time",
	"Heard and McDonald Islands Time",
	"Mawson Station Time",
	"Maldives Time",
	"Oral Time",
	"Pakistan Standard Time",
	"Indian/Kerguelen",
	"Tajikistan Time",
	"Turkmenistan Time",
	"Uzbekistan Time",
	"Yekaterinburg Time",
	"Indian Standard Time",
	"Sri Lanka Time",
	"Nepal Time",
	"British Indian Ocean Time",
	"Bangladesh Standard Time",
	"Bhutan Time",
	"Kyrgyzstan time",
	"Omsk Time",
	"Vostok Station Time",
	"Cocos Islands Time",
	"Myanmar Time",
	"Christmas Island Time",
	"Davis Time",
	"Khovd Time",
	"Indochina Time",
	"Krasnoyarsk Time",
	"Thailand Standard Time",
	"Western Indonesian Time",
	"ASEAN Common Time",
	"Australian Western Standard Time",
	"Brunei Time",
	"Choibalsan",
	"Central Indonesia Time",
	"China time",
	"Hong Kong Time",
	"Irkutsk Time",
	"Malaysia Time",
	"Philippine Standard Time",
	"Singapore Time",
	"Ulaanbaatar Time",
	"Western Standard Time",
	"Eastern Indonesian Time",
	"Japan Standard Time",
	"Korea Standard Time",
	"Timor Leste Time",
	"Yakutsk Time",
	"Australian Central Standard Time",
	"Australian Eastern Standard Time",
	"Chamorro Standard Time",
	"Chuuk Time",
	"Dumont d'Urville Time",
	"Papua New Guinea Time",
	"Vladivostok Time",
	"Lord Howe Standard Time",
	"Kosrae Time",
	"Macquarie Island Station Time",
	"New Caledonia Time",
	"Pohnpei Standard Time",
	"Sakhalin Island time",
	"Solomon Islands Time",
	"Srednekolymsk Time",
	"Vanuatu Time",
	"Norfolk Time",
	"Fiji Time",
	"Gilbert Island Time",
	"Magadan Time",
	"Marshall Islands",
	"New Zealand Standard Time",
	"Kamchatka Time",
	"Tuvalu Time",
	"Wake Island Time",
	"Chatham Standard Time",
	"Phoenix Island Time",
	"Tokelau Time",
	"Tonga Time",
	"Line Islands Time",
	"Azores Standard Time",
	"Cape Verde Time",
	"Eastern Greenland Time",
	"Fernando de Noronha Time",
	"South Georgia and the South Sandwich Islands",
	"Argentina Time",
	"Brasilia Time",
	"Falkland Islands Standard Time",
	"French Guiana Time",
	"Saint Pierre and Miquelon Standard Time",
	"Rothera Research Station Time",
	"Suriname Time",
	"Uruguay Standard Time",
	"Newfoundland Time",
	"Amazon Time",
	"Atlantic Standard Time",
	"Bolivia Time",
	"Chile Standard Time",
	"Colombia Summer Time",
	"Eastern Caribbean Time",
	"Falkland Islands Time",
	"Guyana Time",
	"Paraguay Time",
	"Venezuelan Standard Time",
	"Colombia Time",
	"Cuba Standard Time",
	"Ecuador Time",
	"Eastern Standard Time",
	"Peru Time",
	"Central Standard Time",
	"Easter Island Standard Time",
	"Galapagos Time",
	"Mountain Standard Time",
	"Clipperton Island Standard Time",
	"Pacific Standard Time",
	"Alaska Standard Time",
	"Gambier Island Time",
	"Marquesas Islands Time",
	"Cook Island Time",
	"Hawaii-Aleutian Standard Time",
	"Hawaii Standard Time",
	"Tahiti Time",
	"Niue Time",
	"Samoa Standard Time",
	"Baker Island Time" };
*/

const char* TZ_LOC[] = {
	"UTC",
	"WET",
	"CET",
	"IRLT",
	"WAT",
	"CAT",
	"EET",
	"IST",
	"SAST",
	"USZ1",
	"ARST",
	"EAT",
	"FET",
	"IOT",
	"MSK",
	"SYOT",
	"IRST",
	"AMT",
	"AZT",
	"GET",
	"GST",
	"MUT",
	"RET",
	"SAMT",
	"SCT",
	"VOLT",
	"AFT",
	"HMT",
	"MAWT",
	"MVT",
	"ORAT",
	"PKT",
	"TFT",
	"TJT",
	"TMT",
	"UZT",
	"YEKT",
	"INST",
	"SLST",
	"NPT",
	"BIOT",
	"BST",
	"BTT",
	"KGT",
	"OMST",
	"VOST",
	"CCT",
	"MMT",
	"CXT",
	"DAVT",
	"HOVT",
	"ICT",
	"KRAT",
	"THA",
	"WIT",
	"ACT",
	"AWST",
	"BDT",
	"CHOT",
	"CIT",
	"CT",
	"HKT",
	"IRKT",
	"MYT",
	"PHST",
	"SGT",
	"ULAT",
	"WST",
	"EIT",
	"JST",
	"KST",
	"TLT",
	"YAKT",
	"ACST",
	"AEST",
	"ChST",
	"CHUT",
	"DDUT",
	"PGT",
	"VLAT",
	"LHST",
	"KOST",
	"MIST",
	"NCT",
	"PONT",
	"SAKT",
	"SBT",
	"SRET",
	"VUT",
	"NFT",
	"FJT",
	"GILT",
	"MAGT",
	"MHT",
	"NZST",
	"PETT",
	"TVT",
	"WAKT",
	"CHAST",
	"PHOT",
	"TKT",
	"TOT",
	"LINT",
	"AZOST",
	"CVT",
	"EGT",
	"FNT",
	"SGST",
	"ART",
	"BRT",
	"FKST",
	"GFT",
	"PMST",
	"ROTT",
	"SRT",
	"UYT",
	"NT",
	"AMZT",
	"AST",
	"BOT",
	"CLT",
	"COST",
	"ECT",
	"FKT",
	"GYT",
	"PYT",
	"VET",
	"COT",
	"CUST",
	"ECUT",
	"EST",
	"PET",
	"CST",
	"EAST",
	"GALT",
	"MST",
	"CIST",
	"PST",
	"AKST",
	"GIT",
	"MART",
	"CKT",
	"HAST",
	"HST",
	"TAHT",
	"NUT",
	"SST",
	"BIT" };

const short TZ_HOUR[] PROGMEM = {
	0,	// UTC
	0,	// WET
	1,	// CET
	1,	// IRLT
	1,	// WAT
	2,	// CAT
	2,	// EET
	2,	// IST
	2,	// SAST
	2,	// USZ1
	3,	// ARST
	3,	// EAT
	3,	// FET
	3,	// IOT
	3,	// MSK
	3,	// SYOT
	3,	// IRST
	4,	// AMT
	4,	// AZT
	4,	// GET
	4,	// GST
	4,	// MUT
	4,	// RET
	4,	// SAMT
	4,	// SCT
	4,	// VOLT
	4,	// AFT
	5,	// HMT
	5,	// MAWT
	5,	// MVT
	5,	// ORAT
	5,	// PKT
	5,	// TFT
	5,	// TJT
	5,	// TMT
	5,	// UZT
	5,	// YEKT
	5,	// INST
	5,	// SLST
	5,	// NPT
	6,	// BIOT
	6,	// BST
	6,	// BTT
	6,	// KGT
	6,	// OMST
	6,	// VOST
	6,	// CCT
	6,	// MMT
	7,	// CXT
	7,	// DAVT
	7,	// HOVT
	7,	// ICT
	7,	// KRAT
	7,	// THA
	7,	// WIT
	8,	// ACT
	8,	// AWST
	8,	// BDT
	8,	// CHOT
	8,	// CIT
	8,	// CT
	8,	// HKT
	8,	// IRKT
	8,	// MYT
	8,	// PHST
	8,	// SGT
	8,	// ULAT
	8,	// WST
	9,	// EIT
	9,	// JST
	9,	// KST
	9,	// TLT
	9,	// YAKT
	9,	// ACST
	10,	// AEST
	10,	// ChST
	10,	// CHUT
	10,	// DDUT
	10,	// PGT
	10,	// VLAT
	10,	// LHST
	11,	// KOST
	11,	// MIST
	11,	// NCT
	11,	// PONT
	11,	// SAKT
	11,	// SBT
	11,	// SRET
	11,	// VUT
	11,	// NFT
	12,	// FJT
	12,	// GILT
	12,	// MAGT
	12,	// MHT
	12,	// NZST
	12,	// PETT
	12,	// TVT
	12,	// WAKT
	12,	// CHAST
	13,	// PHOT
	13,	// TKT
	13,	// TOT
	14,	// LINT
	-1,	// AZOST
	-1,	// CVT
	-1,	// EGT
	-2,	// FNT
	-2,	// SGST
	-3,	// ART
	-3,	// BRT
	-3,	// FKST
	-3,	// GFT
	-3,	// PMST
	-3,	// ROTT
	-3,	// SRT
	-3,	// UYT
	-3,	// NT
	-4,	// AMZT
	-4,	// AST
	-4,	// BOT
	-4,	// CLT
	-4,	// COST
	-4,	// ECT
	-4,	// FKT
	-4,	// GYT
	-4,	// PYT
	-4,	// VET
	-5,	// COT
	-5,	// CUST
	-5,	// ECUT
	-5,	// EST
	-5,	// PET
	-6,	// CST
	-6,	// EAST
	-6,	// GALT
	-7,	// MST
	-8,	// CIST
	-8,	// PST
	-9,	// AKST
	-9,	// GIT
	-9,	// MART
	-10,	// CKT
	-10,	// HAST
	-10,	// HST
	-10,	// TAHT
	-11,	// NUT
	-11,	// SST
	-12 };	// BIT

const short TZ_MIN[] PROGMEM = {
	0,	// UTC
	0,	// WET
	0,	// CET
	0,	// IRLT
	0,	// WAT
	0,	// CAT
	0,	// EET
	0,	// IST
	0,	// SAST
	0,	// USZ1
	0,	// ARST
	0,	// EAT
	0,	// FET
	0,	// IOT
	0,	// MSK
	0,	// SYOT
	30,	// IRST
	0,	// AMT
	0,	// AZT
	0,	// GET
	0,	// GST
	0,	// MUT
	0,	// RET
	0,	// SAMT
	0,	// SCT
	0,	// VOLT
	30,	// AFT
	0,	// HMT
	0,	// MAWT
	0,	// MVT
	0,	// ORAT
	0,	// PKT
	0,	// TFT
	0,	// TJT
	0,	// TMT
	0,	// UZT
	0,	// YEKT
	30,	// INST
	30,	// SLST
	45,	// NPT
	0,	// BIOT
	0,	// BST
	0,	// BTT
	0,	// KGT
	0,	// OMST
	0,	// VOST
	30,	// CCT
	30,	// MMT
	0,	// CXT
	0,	// DAVT
	0,	// HOVT
	0,	// ICT
	0,	// KRAT
	0,	// THA
	0,	// WIT
	0,	// ACT
	0,	// AWST
	0,	// BDT
	0,	// CHOT
	0,	// CIT
	0,	// CT
	0,	// HKT
	0,	// IRKT
	0,	// MYT
	0,	// PHST
	0,	// SGT
	0,	// ULAT
	0,	// WST
	0,	// EIT
	0,	// JST
	0,	// KST
	0,	// TLT
	0,	// YAKT
	30,	// ACST
	0,	// AEST
	0,	// ChST
	0,	// CHUT
	0,	// DDUT
	0,	// PGT
	0,	// VLAT
	30,	// LHST
	0,	// KOST
	0,	// MIST
	0,	// NCT
	0,	// PONT
	0,	// SAKT
	0,	// SBT
	0,	// SRET
	0,	// VUT
	30,	// NFT
	0,	// FJT
	0,	// GILT
	0,	// MAGT
	0,	// MHT
	0,	// NZST
	0,	// PETT
	0,	// TVT
	0,	// WAKT
	45,	// CHAST
	0,	// PHOT
	0,	// TKT
	0,	// TOT
	0,	// LINT
	0,	// AZOST
	0,	// CVT
	0,	// EGT
	0,	// FNT
	0,	// SGST
	0,	// ART
	0,	// BRT
	0,	// FKST
	0,	// GFT
	0,	// PMST
	0,	// ROTT
	0,	// SRT
	0,	// UYT
	-30,	// NT
	0,	// AMZT
	0,	// AST
	0,	// BOT
	0,	// CLT
	0,	// COST
	0,	// ECT
	0,	// FKT
	0,	// GYT
	0,	// PYT
	-30,	// VET
	0,	// COT
	0,	// CUST
	0,	// ECUT
	0,	// EST
	0,	// PET
	0,	// CST
	0,	// EAST
	0,	// GALT
	0,	// MST
	0,	// CIST
	0,	// PST
	0,	// AKST
	0,	// GIT
	-30,	// MART
	0,	// CKT
	0,	// HAST
	0,	// HST
	0,	// TAHT
	0,	// NUT
	0,	// SST
	0 };	// BIT

#define DS_NONE 		0	//	never trigger DST
#define DS_AFRICA		1	// 1st Sun of SEP, 1st Sun APR
#define DS_AUSTRALIA	2	// 1st Sun of OCT, 1st Sun of APR
#define DS_EUROPE		3	// last Sun of MAR (0th Sun of APR), last Sun of OCT (0th Sun of NOV)
#define DS_FIJI		4	// 1st Sun of NOV, 3rd Sun of JAN
#define DS_IRAN		5	// 22 MAR, 22 SEP
#define DS_ISRAEL		6	// last Fri of MAR (0th Fri of APR), last Sun of OCT (0th Sun of NOV)
#define DS_NAMERICA	7	// 2nd Sun of MAR, 1st Sun of NOV
#define DS_NZEALAND	8	// last Sun of SEP (0th Sun of OCT), 1st Sun of APR
#define DS_PARAGUAY	9	// 1st Sun of OCT, 4th Sun of MAR
#define DS_URUGUAY	10	// 1st Sun of OCT, 2nd Sun of MAR

const byte TZ_DST[] PROGMEM = {
	DS_NONE,	// UTC
	DS_EUROPE,	// WET
	DS_EUROPE,	// CET
	DS_NONE,	// IRLT
	DS_AFRICA,	// WAT
	DS_NONE,	// CAT
	DS_EUROPE,	// EET
	DS_ISRAEL,	// IST
	DS_NONE,	// SAST
	DS_NONE,	// USZ1
	DS_NONE,	// ARST
	DS_NONE,	// EAT
	DS_EUROPE,	// FET
	DS_NONE,	// IOT
	DS_NONE,	// MSK
	DS_NONE,	// SYOT
	DS_IRAN,	// IRST
	DS_NONE,	// AMT
	DS_NONE,	// AZT
	DS_NONE,	// GET
	DS_NONE,	// GST
	DS_NONE,	// MUT
	DS_NONE,	// RET
	DS_NONE,	// SAMT
	DS_NONE,	// SCT
	DS_NONE,	// VOLT
	DS_NONE,	// AFT
	DS_NONE,	// HMT
	DS_NONE,	// MAWT
	DS_NONE,	// MVT
	DS_NONE,	// ORAT
	DS_NONE,	// PKT
	DS_NONE,	// TFT
	DS_NONE,	// TJT
	DS_NONE,	// TMT
	DS_NONE,	// UZT
	DS_NONE,	// YEKT
	DS_NONE,	// INST
	DS_NONE,	// SLST
	DS_NONE,	// NPT
	DS_NONE,	// BIOT
	DS_NONE,	// BST
	DS_NONE,	// BTT
	DS_NONE,	// KGT
	DS_NONE,	// OMST
	DS_NONE,	// VOST
	DS_NONE,	// CCT
	DS_NONE,	// MMT
	DS_NONE,	// CXT
	DS_NONE,	// DAVT
	DS_NONE,	// HOVT
	DS_NONE,	// ICT
	DS_NONE,	// KRAT
	DS_NONE,	// THA
	DS_NONE,	// WIT
	DS_NONE,	// ACT
	DS_NONE,	// AWST
	DS_NONE,	// BDT
	DS_NONE,	// CHOT
	DS_NONE,	// CIT
	DS_NONE,	// CT
	DS_NONE,	// HKT
	DS_NONE,	// IRKT
	DS_NONE,	// MYT
	DS_NONE,	// PHST
	DS_NONE,	// SGT
	DS_NONE,	// ULAT
	DS_NONE,	// WST
	DS_NONE,	// EIT
	DS_NONE,	// JST
	DS_NONE,	// KST
	DS_NONE,	// TLT
	DS_NONE,	// YAKT
	DS_AUSTRALIA,	// ACST
	DS_AUSTRALIA,	// AEST
	DS_NONE,	// ChST
	DS_NONE,	// CHUT
	DS_NONE,	// DDUT
	DS_NONE,	// PGT
	DS_NONE,	// VLAT
	DS_NONE,	// LHST
	DS_NONE,	// KOST
	DS_NONE,	// MIST
	DS_NONE,	// NCT
	DS_NONE,	// PONT
	DS_NONE,	// SAKT
	DS_NONE,	// SBT
	DS_NONE,	// SRET
	DS_NONE,	// VUT
	DS_NONE,	// NFT
	DS_FIJI,	// FJT
	DS_NONE,	// GILT
	DS_NONE,	// MAGT
	DS_NONE,	// MHT
	DS_NZEALAND,	// NZST
	DS_NONE,	// PETT
	DS_NONE,	// TVT
	DS_NONE,	// WAKT
	DS_NZEALAND,	// CHAST
	DS_NONE,	// PHOT
	DS_NONE,	// TKT
	DS_NONE,	// TOT
	DS_NONE,	// LINT
	DS_NONE,	// AZOST
	DS_NONE,	// CVT
	DS_EUROPE,	// EGT
	DS_NONE,	// FNT
	DS_NONE,	// SGST
	DS_NONE,	// ART
	DS_NONE,	// BRT
	DS_NONE,	// FKST
	DS_NONE,	// GFT
	DS_NAMERICA,	// PMST
	DS_NONE,	// ROTT
	DS_NONE,	// SRT
	DS_URUGUAY,	// UYT
	DS_NONE,	// NT
	DS_NONE,	// AMZT
	DS_NONE,	// AST
	DS_NONE,	// BOT
	DS_NONE,	// CLT
	DS_NONE,	// COST
	DS_NONE,	// ECT
	DS_NONE,	// FKT
	DS_NONE,	// GYT
	DS_PARAGUAY,	// PYT
	DS_NONE,	// VET
	DS_NONE,	// COT
	DS_NAMERICA,	// CUST
	DS_NONE,	// ECUT
	DS_NAMERICA,	// EST
	DS_NONE,	// PET
	DS_NAMERICA,	// CST
	DS_NONE,	// EAST
	DS_NONE,	// GALT
	DS_NAMERICA,	// MST
	DS_NONE,	// CIST
	DS_NAMERICA,	// PST
	DS_NAMERICA,	// AKST
	DS_NONE,	// GIT
	DS_NONE,	// MART
	DS_NONE,	// CKT
	DS_NAMERICA,	// HAST
	DS_NONE,	// HST
	DS_NONE,	// TAHT
	DS_NONE,	// NUT
	DS_NONE,	// SST
	DS_NONE };	// BIT

// the first entry in each DS_* table represent impossible values to ensure DS_NONE has no effect.
const short DS_SMON[] = {
	99,	// NONE
	9,		// AFRICA
	10,	// AUSTRALIA
	4,		// EUROPE
	11,	// FIJI
	3,		// IRAN
	4,		// ISRAEL
	3,		// NAMERICA
	10,	// NZEALAND
	10,	// PARAGUAY
	10	};	// URUGUAY

const short DS_SWEEK[] = {
	99,	// NONE
	1,		// AFRICA
	1,		// AUSTRALIA
	0,	// EUROPE
	1,		// FIJI
	0,		// IRAN
	0,	// ISRAEL
	2,		// NAMERICA
	0,	// NZEALAND
	1,		// PARAGUAY
	1	};	// URUGUAY

const short DS_SDOW[] = {
	99,	// NONE
	0,		// AFRICA
	0,		// AUSTRALIA
	0,		// EUROPE
	0,		// FIJI
	0,		// IRAN
	5,		// ISRAEL
	0,		// NAMERICA
	0,		// NZEALAND
	0,		// PARAGUAY
	0	};	// URUGUAY

const short DS_FMON[] = {
	99,	// NONE
	4,		// AFRICA
	4,		// AUSTRALIA
	11,	// EUROPE
	1,		// FIJI
	9,		// IRAN
	11,	// ISRAEL
	11,	// NAMERICA
	4,		// NZEALAND
	3,		// PARAGUAY
	3,	};	// URUGUAY

const short DS_FWEEK[] = {
	99,	// NONE
	1,		// AFRICA
	1,		// AUSTRALIA
	0,		// EUROPE
	3,		// FIJI
	0,		// IRAN
	0,		// ISRAEL
	1,		// NAMERICA
	1,		// NZEALAND
	4,		// PARAGUAY
	2,	};	// URUGUAY

const short DS_FDOW[] = {
	99,	// NONE
	0,		// AFRICA
	0,		// AUSTRALIA
	0,		// EUROPE
	0,		// FIJI
	0,		// IRAN
	0,		// ISRAEL
	0,		// NAMERICA
	0,		// NZEALAND
	0,		// PARAGUAY
	0,	};	// URUGUAY

// if day != 0, override week/day-of-week calculation
const short DS_SDAY[] = {
	0,		// NONE
	0,		// AFRICA
	0,		// AUSTRALIA
	0,		// EUROPE
	0,		// FIJI
	22,	// IRAN
	0,		// ISRAEL
	0,		// NAMERICA
	0,		// NZEALAND
	0,		// PARAGUAY
	0	};	// URUGUAY

const short DS_FDAY[] = {
	0,		// NONE
	0,		// AFRICA
	0,		// AUSTRALIA
	0,		// EUROPE
	0,		// FIJI
	22,	// IRAN
	0,		// ISRAEL
	0,		// NAMERICA
	0,		// NZEALAND
	0,		// PARAGUAY
	0	};	// URUGUAY

