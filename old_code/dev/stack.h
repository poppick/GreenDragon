#ifndef __STACK_H__
#define __STACK_H__

#include<vector>
#include<stdlib.h>
#include "linear_container.h"

namespace mycode
{
	class MyStack : public LinearContainer
	{
		public:
			void push(int a)
			{
				_vec.push_back(a);
			}
			void pop()
			{
				_vec.pop_back();
			}
			int top()
			{
				return _vec[_vec.size()-1];
			}
			bool empty()
			{
				return _vec.empty();
			}
			string name()
			{
				return "MyStack";

			}
			void print()
			{
				printf("%s:", name().c_str());
				
				for(int i = 0; i <_vec.size(); i++)
				{
					printf("%d, ", _vec[i]);
				}
				printf("(top)\n");
			}
			void clear()
			{
				_vec.clear();
			}
			int size()
			{
				return _vec.size();
			}
		private:
			std::vector<int> _vec;
	};
}


#endif
