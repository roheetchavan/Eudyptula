#########################################################
# This invokes the original checkpatch.pl script to
# check kernel coding style of file given as argument
# Usage: ./checkpatch.pl <file to test>
########################################################

#!/bin/bash

#first check headers are present
if [ ! -f /usr/src/linux-headers-`uname -r`/scripts/checkpatch.pl ]
then
	echo "Check linux-headers are installed";
else
	/usr/src/linux-headers-`uname -r`/scripts/checkpatch.pl --terse --file --no-tree $1
fi

