
yum install lrzsz.x86_64 
yum install mysql
yum install mysql-server
yum install MySQL-python.x86_64 
yum install vim-enhanced.x86_64
yum install yum install httpd
yum install php

chkconfig --levels 235 mysqld on
service mysqld start 

chkconfig --levels 235 httpd on
service httpd start

sudo yum install curl-devel expat-devel gettext-devel openssl-devel zlib-devel gcc perl-ExtUtils-MakeMaker
wget https://github.com/git/git/archive/v2.3.0.zip
unzip v2.3.0.zip
cd git-2.3.0/
make prefix=/usr/local/git all
sudo make prefix=/usr/local/git install
rm -rf /usr/bin/git 
cp git /usr/bin/
git --version

cd ~
git clone https://github.com/poppick/GreenDragon.git dragon
ssh-keygen 
echo "copy key to github!"
vi /root/.ssh/id_rsa.pub
