#coding:utf8

def gen_url_area_info(area):
	"""
	http://bj.lianjia.com/xiaoqu/changping
	用途:获取区域基本信息, 如有多少个小区
	"""
	return "http://bj.lianjia.com/xiaoqu/" + area
def gen_url_xiaoqu(area, page_num):
	"""
	http://bj.lianjia.com/xiaoqu/changping/pg1/
	用于抓取小区
	"""
	return "http://bj.lianjia.com/xiaoqu/%s/pg%d/" %(area, page_num)
