#coding:utf8
import sys

#default
args_mode = "from_file"
args_target = "changping"

def parse_args():
	global args_mode, args_target
	if "--update" in sys.argv:
		args_mode = "from_net"
	
	if sys.argv.count("-t") != 0:
		index = sys.argv.index("-t") + 1
		target = sys.argv[index]

parse_args()
