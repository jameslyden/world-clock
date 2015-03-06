tzBuilder -- programmatic timezones.h generation
================================================

This directory contains the script and data file used to generate timezones.h
programmatically. The data file (tz.data) is a lightly sanitized copy of the
table found at:
```
http://en.wikipedia.org/wiki/List_of_time_zone_abbreviations
```
By lightly sanitized, I mean tags for footnotes and parenthetical text was
removed, daylight savings/summer time entries were removed, duplicate entries
(using different names/abbreviations) were removed, and entries with duplicate
abbreviations were deconflicted (generally by adding a letter to the less
significant one, where significance was determined solely by whether I will be
likely to use it).

The data was then converted to the format to be used in timezones.h by running
tzparse.sh on the sanitized file and appending the output to a mostly bare file.

Manually input data
-------------------
The TZ_LOC table is seeded with the TZ_NAME values, but in most cases, this 
should be replaced with the most recognizable city or country in each time zone.

Unfortunately, the daylight savings/summer time information isn't available in a
similarly parseable format, and doesn't lend itself to procedural templatizing
like the "representative place name", so it is almost entirely manually
generated. The only automated construct is the TZ_DST table, which is set to all
DS_NONE (equivalent to no DST ruleset). Creation of the various rulesets, from
enum names to start and finish dates, is a manual process.
