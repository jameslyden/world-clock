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
 */

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

/*
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

const short TZ_HOUR[] = {
  0,
  0,
  1,
  1,
  1,
  2,
  2,
  2,
  2,
  2,
  3,
  3,
  3,
  3,
  3,
  3,
  3,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  4,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  5,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  6,
  7,
  7,
  7,
  7,
  7,
  7,
  7,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  8,
  9,
  9,
  9,
  9,
  9,
  9,
  10,
  10,
  10,
  10,
  10,
  10,
  10,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  11,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  12,
  13,
  13,
  13,
  14,
  -1,
  -1,
  -1,
  -2,
  -2,
  -3,
  -3,
  -3,
  -3,
  -3,
  -3,
  -3,
  -3,
  -3,
  -4,
  -4,
  -4,
  -4,
  -4,
  -4,
  -4,
  -4,
  -4,
  -4,
  -5,
  -5,
  -5,
  -5,
  -5,
  -6,
  -6,
  -6,
  -7,
  -8,
  -8,
  -9,
  -9,
  -9,
  -10,
  -10,
  -10,
  -10,
  -11,
  -11,
  -12 };

const short TZ_MIN[] = {
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  30,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  30,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  30,
  30,
  45,
  0,
  0,
  0,
  0,
  0,
  0,
  30,
  30,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  30,
  0,
  0,
  0,
  0,
  0,
  0,
  30,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  30,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  45,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  -30,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  -30,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  -30,
  0,
  0,
  0,
  0,
  0,
  0,
  0 };

#define DS_NONE 0

// add additional DS_<name> entries here
const byte TZ_DST[] = {
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE,
  DS_NONE };

// the first entry in each DS_* table represent impossible values to ensure DS_NONE has no effect.
const byte DS_SMON[] = {
  99 };

const byte DS_SWEEK[] = {
  99 };

const byte DS_SDOW[] = {
  99 };

const byte DS_FMON[] = {
  99 };

const byte DS_FWEEK[] = {
  99 };

const byte DS_FDOW[] = {
  99 };

