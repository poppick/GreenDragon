#coding:utf8
import sys
sys.path.append("..")
from conf.conf import *
import datetime
import logging
import logging.handlers
import os
import time
import thread

#读取配置
log_path = conf_log_path

#生成日志文件前缀
def get_logfile_prefix():
	script_name = sys.argv[0]
	#assert(script_name.endswith(".py"))
	script_name = script_name[:-3]
	date_str = datetime.datetime.now().strftime('%Y%m%d');
	pid = os.getpid().__str__()
	return "%s_%s_%s" %(script_name, date_str, pid)

def gen_info_handler():
	filename = "%s/%s.%s" % (log_path, get_logfile_prefix(), "info")
	handler = logging.FileHandler(filename)
	#handler.setLevel(logging.INFO)

	log_fmt = '%(asctime)s %(filename)s:%(lineno)s [%(levelname)s]: %(message)s'
	date_fmt = "%Y%m%d %H:%M:%S"
	formatter = logging.Formatter(log_fmt)
	handler.setFormatter(formatter)
	return handler

def gen_debug_handler():
	filename = "%s/%s.%s" % (log_path, get_logfile_prefix(), "debug")
	handler = logging.FileHandler(filename)
	#handler.setLevel(logging.DEBUG)

	log_fmt = '%(asctime)s %(filename)s:%(lineno)s [%(levelname)s]: %(message)s'
	date_fmt = "%Y%m%d %H:%M:%S"
	formatter = logging.Formatter(log_fmt)
	handler.setFormatter(formatter)
	return handler

	pass
def gen_console_handler():
	global console
	console = logging.StreamHandler()
	console.setLevel(logging.DEBUG)

	log_fmt = '%(asctime)s %(filename)s:%(lineno)s [%(levelname)s]: %(message)s'
	date_fmt = "%H:%M:%S"	
	formatter = logging.Formatter(log_fmt, date_fmt)
	console.setFormatter(formatter)

	return console

def create_links():
	"""
	在日志目录下建立软连接
	"""
	prefix = get_logfile_prefix()
	script_name = sys.argv[0]
	script_name = script_name[:-3]

	cmd = "cd %s; rm -rf %s.info %s.debug" %(log_path, script_name, script_name)	
	os.system(cmd)
	cmd = "cd %s; ln -s %s.info %s.info" % (log_path, prefix, script_name)
	os.system(cmd)
	cmd = "cd %s; ln -s %s.debug %s.debug" % (log_path, prefix, script_name)
	os.system(cmd)

def init():
	global console_logger, info_logger, debug_logger
	print "log initing...."
	#auto_clear_logfiles()

	console_handler = gen_console_handler()
	logging.basicConfig(level=logging.DEBUG,
		format = '%(asctime)s %(filename)s:%(lineno)s [%(levelname)s]: %(message)s',
		datefmt = '%H:%M:%S',
		#filename='myapp.log',
		filemode='w',
		#stream = console_handler
		)

	console_logger.addHandler(console_handler)
	#info_logger.addHandler(gen_info_handler())
	#debug_logger.addHandler(gen_debug_handler())

	create_links()

def log_info(s):
	console_logger.info(s)
	#info_logger.info(s)
	#debug_logger.info(s)
def log_debug(s):
	console_logger.debug(s)
	#info_logger.debug(s)
	#debug_logger.debug(s)
def log_error(s):
	console_logger.error(s)
	#info_logger.error(s)
	#debug_logger.error(s)

#初始化
console_logger = logging.getLogger('')
#info_logger = logging.getLogger('info_logs')
#debug_logger = logging.getLogger('debug_logs')
init()
#console_logger.info("sfsfsfs")
#console_logger.error("aaa")

log_info("sfsfsfs")
error_info("aaa")

def auto_clear_logfiles():
	"""
	当启动程序时自动清理过期的debug日志文件
	起一个独立线程处理, 启动时和每24小时清理一次
	"""

	def is_log_file(filename):
		if not (filename.endswith(".info") or filename.endswith(".debug")):
			return False
		l = filename.split(".")
		if len(l) != 2:
			return False
		filename = l[0]
		l = filename.split("_")
		if len(l) < 3:
			return False
		if not l[-1].isdigit():
			return False
		if not l[-2].isdigit():
			return False
		if not l[-2].__len__() == 8:
			return False
		return True
	def is_bad_link(filename):
		full_filename = "%s/%s" %(log_path, filename)
		try:
			linked_name = os.readlink(full_filename)
			full_linked_name = "%s/%s"%(log_path, filename)
			
			if not os.path.exists(full_linked_name):
				return True
			else:
				return False
		except OSError:
			return False
	def is_out_of_date(filename):
		pid_str = filename.split(".")[-2].split("_")[-1]
		if pid_str == os.getpid().__str__():
			return False	#当前进程产生的日志不删
		data_str = filename.split(".")[-2].split("_")[-2]
		today_str = datetime.datetime.now().strftime('%Y%m%d')
		if data_str == today_str:
			return False	#当天的数据不删
		return True 	
	def is_debug_file(filename):
		return filename.endswith(".debug")

	while 1:
		log_info("auto clear logfiles ...")
		for rt, dirs, files in os.walk(log_path):
			for filename in files:
				#print filename
				if not is_log_file(filename):
					continue
				if is_debug_file(filename):
					if is_out_of_date(filename):
						log_info("[AUTO_RM_LOG]remove out date files %s" % filename)
						os.remove(filename)
		for rt, dirs, files in os.walk(log_path):
			for filename in files:
				if is_bad_link(filename):
					full_filename = "%s/%s" %(log_path, filename)
					log_info("[AUTO_RM_LOG]remove bad links %s" % full_filename)
					os.remove(full_filename)
		time.sleep(5)

#auto_clear_logfiles()
#thread.start_new_thread(auto_clear_logfiles, ())

if __name__ == "__main__":
	#auto_clear_logfiles()
	#log_debug("66666")
	#log_info("4555")
	#log_error("5555")
	#time.sleep(600)
	pass
