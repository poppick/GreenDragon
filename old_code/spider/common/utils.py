#coding:utf8
import urllib
import time
import os

fetch_ok_count = 0
fetch_failed_count = 0
fetch_retry_ok_count = 0

min_fetch_interval = 1 #抓取最小间隔, 单位秒
last_fetch_time = time.time()
total_time = 0.0
total_sleep_time = 0.0

def fetch_page(url, retry_times = 3):
	global fetch_ok_count, fetch_failed_count, fetch_retry_ok_count
	global last_fetch_time, total_time,  total_sleep_time

	print "spidering %s ..." % url
	start_time = time.time()
	s = ""
	retry_count = 0
	while retry_count < retry_times:
		try:
			t = time.time()
			if t - last_fetch_time < min_fetch_interval:
				sleep_time = min_fetch_interval - (t - last_fetch_time)
				time.sleep(sleep_time)
				total_sleep_time += sleep_time
			last_fetch_time = t

			f = urllib.urlopen(url)
			s = f.read()
			#s = s.replace("\n", "")

			fetch_ok_count += 1
			if retry_count != 0:
				fetch_retry_ok_count += 1
			break
		except:
			fetch_retry_ok_count 
		retry_count += 1
	if s == "":
		fetch_failed_count += 1
	end_time = time.time()
	total_time += end_time - start_time
	return s

class DataSaver:
	def __init__(self, filename):
		self.make_dir_if_not_exits(filename)
		self.f = open(filename, "w")
	def save(self, data):
		self.f.write(data)
		self.f.write("\n")
		self.f.flush()
		self.f.close()
	def make_dir_if_not_exits(self, filename):
		pos = filename.rfind("/")
		if pos == -1:
			return
		prefix = filename[:pos]
		if os.path.exists(prefix):
			return
		cmd = "mkdir -p %s" %prefix
		print cmd
		os.system(cmd)

def read_file(filename):
	f = open(filename)
	s = f.read()
	f.close()
	print "read data from file: %s" %filename
	return s

def fetch_info():
	global fetch_ok_count, fetch_failed_count, fetch_retry_ok_count
	total = fetch_ok_count + fetch_failed_count
	d = {
			"total" : total,
			"fetch_ok_count" : fetch_ok_count,
			"fetch_failed_count" : fetch_failed_count,
			"fetch_retry_ok_count" : fetch_retry_ok_count,

			"total_time" : total_time,
			"total_sleep_time" : total_sleep_time,
			}
	return d

if __name__ == "__main__":
	url = "http://bj.lianjia.com/xiaoqu/changping/"

	content = fetch_page(url)
	print fetch_info()
