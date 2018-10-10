echo "Enter line: "
read line
IFS=' ' read -r -a array <<< "$line"
if test i > ${#array[@]}
then
	echo "Exception: index out of bounds"
else
	echo "${array[$1 - 1]}"
fi
