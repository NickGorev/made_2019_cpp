#!/bin/bash
application=$1
testsfile=$2
echo run tests
echo -------------------------------------------------------------------
errors=0
tests=0
while read LINE 
do 
	tests=$(($tests+1))
	IFS='|' read -ra tests_array <<< $LINE
	IFS=' '
	parameter_string=${tests_array[0]}
	true_answer=${tests_array[1]}
	true_retcode=${tests_array[2]}
	echo "command: $application \"$parameter_string\""
	answer=`$application "$parameter_string"`
	retcode=$?
	echo "answer: $answer, true answer: $true_answer"
	echo "retcode: $retcode, true retcode: $true_retcode"
	if [ "$answer" = "$true_answer" ] && [ $retcode = $true_retcode ]
	then
		echo "Test OK"
	else
		echo "Test error"
		errors=$(($errors+1))
	fi	
	echo -------------------------------------------------------------------
done < $testsfile
if [ $errors -eq 0 ]
then
	echo "All $tests tests have passed"
else
	echo "$errors errors in $tests tests"
fi


