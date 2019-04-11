#!/usr/bin/env bash
DIR="$PWD/$1"
COMMAND=$2
echo "" > "$DIR/logfile.lg"

for file in $DIR/*; do
	echo "Executing $COMMAND on $file"
	execution=$("$COMMAND $file")
	eval $execution
	if [[ $? -eq 0 ]]; then
		echo "Execution of $COMMAND on $file succesful" >> "$DIR/logfile.lg"
	else
		echo "Execution of $COMMAND on $file failed" >> "$DIR/logfile.lg"
	fi
done
