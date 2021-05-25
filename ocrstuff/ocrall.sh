#!/bin/bash

# turn pdf to images using https://pdf2jpg.net/

COUNT=1
OUTS=""
FNUM=$(expr $(ls -l | wc -l) - 1)
for PFILE in *.jpg
do
	ocrmypdf -l ara+eng --image-dpi 300 $PFILE out$COUNT.pdf &
	OUTS=$OUTS" out$COUNT.pdf"

	echo "`tput setaf 1`file $COUNT outof $FNUM`tput sgr0`"

	COUNT=$(expr $COUNT + 1)

	#limit the number of sub-proccesses to 6
	while [ $(jobs | wc -l) -ge 6 ] ; do sleep 1 ; done
done
wait

mkdir out
pdfmerge -o out/bigout$(expr $COUNT - 1).pdf $OUTS
