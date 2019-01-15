import MySQLdb
login_cmd = "beijing"

class MysqlClient:
	def __init__(self):
		self.db = MySQLdb.connect(host = "localhost",
				user = "root",
				passwd = "",
				db = "beijing",
				)
		self.cursor = self.db.cursor()

	def get_cursor(self):
		return self.cursor

	def execute(self, cmd):
		self.cursor.execute(cmd)
	
	def __del__(self):
		self.cursor.close()

def create_table_area():
	cmd = """
	CREATE TABLE IF NOT EXISTS `area` (
		`id` int(11) NOT NULL AUTO_INCREMENT,
		`name` varchar(100) DEFAULT NULL,
		`pinyin` varchar(100) DEFAULT NULL,
		`is_important` tinyint(4) DEFAULT '1',
		`sales_count` int(11) DEFAULT NULL,
		`avg_price` float DEFAULT NULL,
		`increase_rate_year` float DEFAULT NULL,
		`increase_rate_month` float DEFAULT NULL,
		`area_count` int(11) DEFAULT NULL,
		PRIMARY KEY (`id`)
		) ENGINE=MyISAM AUTO_INCREMENT=12 DEFAULT CHARSET=latin1
	"""
	client = MysqlClient()
	client.execute(cmd)

def create_table_xiaoqu():
	cmd = """
	CREATE TABLE IF NOT EXISTS `xiaoqu` (
		`name` varchar(100) DEFAULT NULL,
		`area` varchar(20) DEFAULT NULL
		) ENGINE=MyISAM AUTO_INCREMENT=12 DEFAULT CHARSET=latin1
	"""
	client = MysqlClient()
	client.execute(cmd)

if __name__ == "__main__":
	client = MysqlClient()
	cursor = client.get_cursor()
	cursor.execute("show tables")
	result = cursor.fetchall()
	print result
