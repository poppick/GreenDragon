#include<stdio.h>
#include <stdlib.h>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <errno.h>
#include <vector>
#include <string.h>
#include "data.h"
using namespace std;
using namespace mycode;

int main()
{
	gen_nums(20);
	printf("gen nums done\n");

	vector<int> data_vec;
	load_nums("nums.data", data_vec);

	printf("data_vec load %d nums, first=%d\n", data_vec.size(), data_vec.empty()?-1:data_vec[0]);

	return 0;
}
