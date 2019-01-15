#coding:utf8

def convert_url_to_string(url):
	"""
	change http://bj.lianjia.com/xiaoqu/changping/pg24/
	to bj.lianjia.com_xiaoqu_changping_pg24
	"""
	s = url
	s = s.replace("http://", "")
	while s.endswith("/"):
		s = s[:-1]
	s = s.replace("/", "_")
	return s

def get_filename_xiaoqu(area, xiaoqu_url):
	"""
	like http://bj.lianjia.com/xiaoqu/changping/pg24/
	saves in data/changping/bj.lianjia.com_xiaoqu_changping_pg24.dat
	"""
	url_str = convert_url_to_string(xiaoqu_url)
	return "data/xiaoqu/%s/%s.dat" %(area, url_str)

def get_filename_area(area):
	"""
	like http://bj.lianjia.com/xiaoqu/dongcheng/
	save in data/area/dongcheng.dat
	"""
	return "data/area/%s.dat" % area
