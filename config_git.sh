#配置git
git config --global alias.st status
git config --global alias.co checkout
git config --global alias.br branch
git config --global alias.ci "commit -a"
git config --global push.default simple

echo "现在配置git的邮箱和名称"
read -p "请输入你的名字(拼音/英文):" name
git config --global user.name $name
read -p "请输入你的邮箱:" email
git config --global user.email $email
echo "配置完成! 你的名字是$name, 邮箱是$email"

