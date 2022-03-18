fib=(1 1)

for((i=2;i<11;i++))
do
	#fib[$i]=$((${fib[$i-1]} + ${fib[$i-2]}))
	fib[$i]=`expr ${fib[$i-1]} + ${fib[$i-2]}`
done

for i in ${fib[@]}
do 
	echo $i
done

for i in ${fib[*]}
do 
	echo $i
done

for i in "${fib[@]}"
do 
	echo $i
done

echo "----------------------"

carr=(a b "c d" e f)

for i in "${carr[@]}"
do
	echo $i
done

echo "----------------------"

for i in ${carr[@]}
do
	echo $i
done

echo "----------------------"

for i in ${carr[*]}
do
	echo $i
done

echo "number of elements"

echo "${#carr[@]}"
echo ${#carr[@]}
echo ${#carr[*]}

for((i=0;i<${#fib[*]};i++))
do
	echo ${fib[$i]}
done



echo "----------------"

for i in $*
do
	echo $i
done

echo "----------------"

for i in "$@"
do
	echo $i
done



#$var	#without single quote
#$*	$#	${n}	"$@"
#$(command)	#function
#$((expression))
#${arr[$index]} 	${arr[index]}
#"${arr[*/@]}"	 ${#arr[*/@]}

