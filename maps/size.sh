for file in maps/*.fdf; do
	cols=$(cat $file | wc -l)
	rows=$(head -n 1 $file | tr ' ' '\n' | wc -l)
	echo "$file:" >> map_sizes.txt
	echo "$cols * $rows" | bc >> map_sizes.txt
	echo "" >> map_sizes.txt
done
