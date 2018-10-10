echo "Enter line: "
read line
while [[ "$line" = "$1" ]]; do
 	echo "Lines are same, enter another line"
 	read line
done
if test ${#line} = $2
then
	echo "Lengths are equal, you entered: $line"
else
	echo "Lengths aren't equal"
fi
