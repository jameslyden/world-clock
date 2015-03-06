#!/bin/bash

file=tz.data
len=$(cat $file | wc -l)

for linenum in $(seq 1 $len); do
	line="$(head -$linenum $file | tail -1)"
	abbr=$(echo $line | cut -f1 -d' ')
	name="$(echo $line | cut -f2- -d' ' | rev | cut -f2- -d' ' | rev)"
	rawoffset=$(echo $line | rev | cut -f1 -dC | rev)
	offhour=$(echo $rawoffset | cut -b1-3 | sed 's/\([-+]\)0\(.\)/\1\2/')
	offmin=$(echo ${rawoffset}" 0000" | cut -b1,5,6 | sed 's/\([-+]\)0\(.\)/\1\2/')
	if [[ ! $offhour ]]; then offhour=0; fi
	if [[ ! $offmin ]]; then offmin=0; fi

	index=$((linenum - 1))
	# writes the TZ_<abbr> entries one at a time
	printf "#define TZ_%s\t%d\n" $abbr $index

	# collects the other values for later expansion
	abbrs[$index]=$abbr
	names[$index]="$name"
	h_off[$index]=$offhour
	m_off[$index]=$offmin

	# put all last run logic here before variables go out of scope
	if [[ $linenum -eq $len ]]; then
		printf "\n"

		# create TZ_NAME table
		printf "const char* TZ_NAME[] = {\n"
		EOL=","
		for tz in $(seq 0 $index); do
			if [[ $tz -eq $index ]]; then EOL=" };"; fi
			printf "  \"%s\"%s\n" "${names[$tz]}" "$EOL";
		done
		printf "\n"
		
		# create TZ_LOC table
		printf "const char* TZ_LOC[] = {\n"
		EOL=","
		for tz in $(seq 0 $index); do
			if [[ $tz -eq $index ]]; then EOL=" };"; fi
			printf "  \"%s\"%s\n" "${abbrs[$tz]}" "$EOL";
		done
		printf "\n"
		
		# create TZ_HOUR table
		printf "const short TZ_HOUR[] = {\n"
		EOL=","
		for tz in $(seq 0 $index); do
			if [[ $tz -eq $index ]]; then EOL=" };"; fi
			printf "  %d%s\n" "${h_off[$tz]}" "$EOL";
		done
		printf "\n"
		
		# create TZ_MIN table
		printf "const short TZ_MIN[] = {\n"
		EOL=","
		for tz in $(seq 0 $index); do
			if [[ $tz -eq $index ]]; then EOL=" };"; fi
			printf "  %d%s\n" "${m_off[$tz]}" "$EOL";
		done
		printf "\n"

		# create TZ_DST table and supporting information
		printf "#define DS_NONE 0\n\n"
		printf "// add additional DS_<name> entries here\n"
		printf "const byte TZ_DST[] = {\n"
		EOL=","
		for tz in $(seq 0 $index); do
			if [[ $tz -eq $index ]]; then EOL=" };"; fi
			printf "  DS_NONE%s\n" "$EOL";
		done
		printf "\n"
		printf "// the first entry in each DS_* table represent impossible values"
		printf " to ensure DS_NONE has no effect.\n"
		printf "const byte DS_SMON[] = {\n  99 };\n\n"
		printf "const byte DS_SDOW[] = {\n  99 };\n\n"
		printf "const byte DS_FMON[] = {\n  99 };\n\n"
		printf "const byte DS_FDOW[] = {\n  99 };\n\n"

	fi
done

