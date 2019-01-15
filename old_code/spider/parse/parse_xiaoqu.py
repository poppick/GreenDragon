#coding: utf8
import sys
sys.path.append("..")
import HTMLParser
import common.utils as utils

class XiaoquStringParse:
	def feed(self, page):
		self.parse_max_page(page)
	def parse_max_page(self, page):
		self.max_page = 100
		start = page.find('"totalPage":')
		if start == -1:
			return 100
		start += len('"totalPage":')
		end = page.find(",", start)
		if start == -1:
			return 100
		self.max_page = int(page[start:end])



class XiaoquParser(HTMLParser.HTMLParser):
	def __init__(self):
		HTMLParser.HTMLParser.__init__(self)
		self.indata = False
		self.indata_2 = False
		self.results = []
		
		self.max_page = 0
		self.str_parser = XiaoquStringParse()
	
	def feed(self, page):
		self.str_parser.feed(page)
		self.max_page = self.str_parser.max_page
		return HTMLParser.HTMLParser.feed(self, page)

	def handle_starttag(self, tag, attrs):
		if tag == "div":
			for name,value in attrs:
				if name == "class" and value == "title":
					self.indata = True
		if tag == "div":
			for name,value in attrs:
				if name == "class" and value == "info":
					self.indata_2 = True
	def handle_endtag(self, tag):
		if tag == "div":
			self.indata_2 = False
			self.indata = False


	def handle_data(self, data):
		if self.indata and self.indata_2:
			self.results.append(data)
			self.indata = False
			self.indata_2 = False
	def output(self):
		return self.results
	def clear(self):
		self.results = []




if __name__ == "__main__":
	for line in open("../data/xiaoqu.pages"):
		page = line
		break

	parser = XiaoquParser()
	parser.feed(page)
