#!/bin/bash

# First I should clean my directory
rm /tmp/eazyk4/*

# My tmp file is /tmp/eazyk4
cp /krypton/krypton3/found* /tmp/eazyk4/

# Variable containing all of the encrypted files
FILES=/tmp/eazyk4/found*

# Remove all spaces, then fill in the table of characters to replace
# These were found by trial and error, using the crak4.c file
for file in $FILES
do
	sed -i.old $file -e 's/ //g'	\
		-e 's/S/e/g'		\
		-e 's/D/h/g'		\
		-e 's/J/t/g'		\
		-e 's/Q/a/g'		\
		-e 's/N/r/g'		\
		-e 's/U/s/g'		\
		-e 's/G/n/g'		\
		-e 's/C/i/g'		\
		-e 's/Z/c/g'		\
		-e 's/X/f/g'		\
		-e 's/Y/p/g'		\
		-e 's/L/y/g'		\
		-e 's/V/l/g'		\
		-e 's/F/k/g'		\
		-e 's/K/w/g'		\
		-e 's/T/m/g'		\
		-e 's/E/g/g'		\
		-e 's/W/d/g'		\
		-e 's/M/u/g'		\
		-e 's/H/q/g'		\
		-e 's/A/b/g'		\
		-e 's/O/x/g'		\
		-e 's/R/j/g'		\
		-e 's/B/o/g'		\
		-e 's/I/v/g'		\
		-e 's/P/z/g'
done

# Now that I have completed the conversion; need password
sed -i.old /tmp/eazyk4/krypton4 \
	-e 's/ //g'		\
	-e 's/S/e/g'		\
	-e 's/D/h/g'		\
	-e 's/J/t/g'		\
	-e 's/Q/a/g'		\
	-e 's/N/r/g'		\
	-e 's/U/s/g'		\
	-e 's/G/n/g'		\
	-e 's/C/i/g'		\
	-e 's/Z/c/g'		\
	-e 's/X/f/g'		\
	-e 's/Y/p/g'		\
	-e 's/L/y/g'		\
	-e 's/V/l/g'		\
	-e 's/F/k/g'		\
	-e 's/K/w/g'		\
	-e 's/T/m/g'		\
	-e 's/E/g/g'		\
	-e 's/W/d/g'		\
	-e 's/M/u/g'		\
	-e 's/H/q/g'		\
	-e 's/A/b/g'		\
	-e 's/O/x/g'		\
	-e 's/R/j/g'		\
	-e 's/B/o/g'		\
	-e 's/I/v/g'		\
	-e 's/P/z/g'
cat /tmp/eazyk4/krypton4 | tr '[:lower:]' '[:upper:]'
echo # Newline
