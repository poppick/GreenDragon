
echo "建立备份目录"
rm -rf bak.bak
mv bak bak.bak
mkdir bak
echo -n "配置vim和shell环境?"

tar xvf env.tar
if [ -d "~/.vimrc" ]; then
	mv ~/.vimrc bak
fi
if [ -d "~/.vim" ]; then
	mv ~/.vim bak
fi
if [ -d "~/.bashrc" ]; then
	mv ~/.bashrc bak
fi
if [ -d "~/.profile" ]; then
	mv ~/.profile bak
fi

cp -r ./.vimrc ~
cp -r ./.vim ~
cp -r ./.bashrc ~
cp -r ./.bash_profile ~
echo "vim和shell环境配置完成"



