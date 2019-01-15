#coding:utf8
import common.utils as utils
import parse.parse_xiaoqu as parse_xiaoqu
import sys
import get_area
from common.args import *
import common.filenames as filenames
import common.urls as urls
import common.mysql as mysql

def spider_and_save_area_page(area):
	url = urls.gen_url_area_info(area)
	filename = filenames.get_filename_area(area)
	saver = utils.DataSaver(filename)
	page = utils.fetch_page(url)
	saver.save(page)
	return page

def process_area_page(area):
	"""
	根据area页面:
	1, 取得area页面
	2, 解析出基本信息, 如max_page等
	3, 生成待抓取url
	4, 根据参数, 抓取url, 将页面存放在文件中, 或直接从文件中读取
	5, 解析页面, 获得数据
	6, 存入mysql
	"""
	#1, 取得area页面
	if args_mode == "from_net":
		page = spider_and_save_area_page(area)
	else:		
		filename = filenames.get_filename_area(area)
		page = utils.read_file(filename)

	#2, 解析出基本信息, 如max_page等
	parser = parse_xiaoqu.XiaoquParser()
	parser.feed(page)
	max_page = parser.max_page

	result_list = []
	mclient = mysql.MysqlClient()
	mysql.create_table_xiaoqu()
	for i, page_num in enumerate(range(max_page)):
		#3, 生成待抓取url
		xiaoqu_url = urls.gen_url_xiaoqu(area, page_num+1)

		#4, 根据参数, 抓取url, 将页面存放在文件中, 或直接从文件中读取
		filename = filenames.get_filename_xiaoqu(area, xiaoqu_url)
		if args_mode == "from_net":
			page = utils.fetch_page(xiaoqu_url)
			saver = utils.DataSaver(filename)
			saver.save(page)
		page = utils.read_file(filename)
		
		#5, 解析页面, 获得数据
		parser = parse_xiaoqu.XiaoquParser()
		parser.feed(page)
		result_list += parser.output()
		for result in result_list:
			print "get xiaoqu:",result

			#6, 存入mysql
			cmd = "delete from xiaoqu where name = '%s'" %(result)
			mclient.execute(cmd)
			cmd = "insert into xiaoqu (name, area) values ('%s', '%s')" % (result, area)
			#print cmd
			mclient.execute(cmd)

		if i == 2:
			break
			pass

def run():
	#获取区域列表
	area_list = []
	if args_target == "all" or args_target == "*":
		area_list = get_area.run()
	else:
		area_list.append(args_target)

	for area in area_list:
		process_area_page(area)

if __name__ == "__main__":
	#run()
	process_area_page("changping")
