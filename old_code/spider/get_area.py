#coding:utf8
import common.utils as utils
import parse.parse_xiaoqu as parse_xiaoqu
import common.mysql as mysql
import sys
from common.args import *

areas = ["dongcheng", "xicheng", "haidian", "chaoyang", "changping"]

def spider_area():
	client = mysql.MysqlClient()
	cursor = client.get_cursor()
	t = [
			("昌平", "changping"),
			("朝阳", "chaoyang"),
			("海淀", "haidian"),
			("西城", "xicheng"),
			("东城", "dongcheng"),
			]
	cmd = "delete from area"
	cursor.execute(cmd)
	for name, pinyin in t:
		cmd = "insert into area (name, pinyin) values ('%s', '%s')" %(name, pinyin)
		print cmd
		cursor.execute(cmd)
def spider_and_save():
	mysql.create_table_area()
	spider_area()

def fetch_area():
	area_list = []
	cmd = "select pinyin from area"
	client = mysql.MysqlClient()
	cursor = client.get_cursor()
	cursor.execute(cmd)
	for item in  cursor.fetchall():
		area_list.append(item[0])
	return area_list

def run():
	if args_mode == "from_net":
		spider_and_save()
	area_list = fetch_area()
	print area_list
	return area_list

if __name__ == "__main__":
	run()
