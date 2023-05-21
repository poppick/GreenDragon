#ifndef __DATA_H__ 
#define __DATA_H__
#include<stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <errno.h>
#include <vector>
#include <string.h>
using namespace std;

namespace mycode{

	int gen_nums(int count, std::string filename = "nums.data")
	{

		int r;
		r = access(filename.c_str(), F_OK);
		if(r == 0)
		{
			//printf("文件存在\n");
			char cmd[1024];
			sprintf(cmd, "mv -f %s %s.bak", filename.c_str(), filename.c_str());
			//printf("cmd = %s\n", cmd);
			r = system(cmd);
			if(r != 0)
			{
				fprintf(stderr, "exec cmd [%s] failed!\n", cmd);
				return -1;
			}
		}else{
			//printf("文件不存在\n");

		}

		FILE* f = fopen(filename.c_str(), "w");
		if(f == NULL)
		{
			fprintf(stderr, "create file %s failed\n", filename.c_str());
			return -1;
		}

		srand(time(0));
		int rand_num;

		for (int i = 0; i < count; i++)
		{
			rand_num = (rand() % 1000000);
			r = fprintf(f, "%d\n", rand_num);
			if(r <0)
			{
				fprintf(stderr, "write data failed!\n");
				fclose(f);
				return -1;
			}
		}
		fclose(f);

		return 0;

	}

	int load_nums(const string filename, vector<int>& data_vec)
	{
		FILE* f = fopen(filename.c_str(), "r");
		if(f == NULL)
		{
			fprintf(stderr, "open file [%s] failed, errno=%d,%s\n", filename.c_str(), errno, strerror(errno));
			return -1;
		}

		int num, r;

		while(1)
		{
			r = fscanf(f, "%d", &num);
			if(r == 0)
			{
				fprintf(stderr, "read nothing, errno=%d, %s\n", errno, strerror(errno));
				fclose(f);
				return -1;
			}
			else if(r < 0)
			{
				break;
			}
			data_vec.push_back(num);
		}
		fclose(f);

		return 0;
	}
}
#endif
