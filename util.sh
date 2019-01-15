usr_input()
{
	while [ 1 ] 
	do
		read -p "请输入y/n:" choose
		
		if [ $choose != "y" ] && [ $choose != "n" ]; then
			echo "输入错误"
			continue
		fi

		if [ $choose != "y" ]; then 
			exit 1
		fi
		break
	done

}
