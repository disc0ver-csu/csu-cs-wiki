if [ ! -n "$1" ]; then
	echo "未输入源文件夹路径，默认为当前文件夹"
fi

if [ ! -n "$2" ];then
	a="/tmp/ans/"
	echo "未输入目标文件夹，自动设置为" $a
fi

transfun(){
	echo $1, $2, $3, $4 $5 # 文件名 后缀 目标文件夹 文件名（去除后缀） 源文件夹
	if [ ! -d $3 ];then
		echo "文件夹"$3"不存在"
		mkdir -p $3
	fi
	if [ ! -f ""$3"/"$1"" ];then
		echo ""$3"/"$1""
		if [ ! -n "$5" ];then
			cp $1 $3
		else
			cp $5"/"$1 $3
		fi
	else
		echo "文件"$1"已存在"
		count=1
		while([ -f ""$3"/"$4"_"$count"."$2"" ])
		do
			let "count++"
		done
		
		echo ""$3"/"$4"_"$count"."$2""
		echo ""$4"_"$count"."$2""
		if [ ! -n "$5" ];then
			cp $1 ""$4"_"$count"."$2""
		else
			cp $5"/"$1 ""$4"_"$count"."$2"" # 在源文件夹下创建一个不同名字的文件
		fi
		mv ""$4"_"$count"."$2"" ""$3"/" # 移动到目标文件夹下
	fi
}

transfun1(){
	echo $1 $2 $3 # 文件夹名 目标文件夹 源文件夹
	if [ ! -d $2 ];then
		echo "文件夹"$2"不存在"
		mkdir -p $2
	fi
	if [ ! -d ""$2"/"$1"" ];then
		echo ""$2"/"$1""
		cp -r $3"/"$1 $2
	else
		echo "文件夹"$1"已存在"
		count=1
		while([ -d ""$2"/"$1"_"$count"" ])
		do
			let "count++"
		done
		
		echo ""$2"/"$1"_"$count""
		echo ""$1"_"$count""
		cp -r $3"/"$1 ""$1"_"$count"" # 在源文件夹下创建一个不同名字的文件
		mv ""$1"_"$count"" ""$2"/" # 移动到目标文件夹下
	fi
}

for filename in `ls $1`;do
	extension="${filename##*.}" # 扩展名
	name="${filename%.*}" # 文件名
	echo ${addr}
	if [ $extension != $name ];then #为文件，且有后缀
		transfun "${filename}" "${extension}" ""$a""$extension"" "${name}" $1
	else
		if [ -f $1"/"$filename ];then # 为文件 没有后缀
			transfun "${filename}" "${extension}" ""$a"file" "${name}" $1
		elif [ -d $1"/"$filename ];then # 为文件夹
			echo "$filename is a file"
			transfun1 "${filename}" ""$a"file" $1
		fi
	fi
done

