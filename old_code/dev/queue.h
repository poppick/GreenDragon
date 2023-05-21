#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <vector>
#include <stdlib.h>
#include "linear_container.h"
namespace mycode
{

	class MyQueue: public LinearContainer
	{
		public:
			MyQueue()
			{
				_data = (int*)malloc(sizeof(int) * 4);
				if(_data == NULL)
				{
					fprintf(stderr, "malloc failed\n");
					return;
				}
				_front = -1;
				_back = -1;
				_size = 0;
				_cap = 4;

			}
			~MyQueue()
			{
				free(_data);
				_size = 0;
				_cap = 0;
			}
			int front()
			{
				return _data[_front];
			}
			int back()
			{
				return _data[_back];
			}
			void push(int a)
			{
				if(_size == 0)
				{
					_data[0] = a;
					_front = 0;
					_back = 0;
					_size = 1;
					return;
				}

				if(_size == _cap)
				{
					int new_cap = _cap * 2;
					int* new_data = (int*)malloc(sizeof(int) * new_cap);
					if(new_data == NULL)
					{
						fprintf(stderr, "malloc failed\n");
						return;
					}
					if(_back > _front)
					{
						memcpy(new_data, _data, sizeof(int) * _cap);
					}else{
						memcpy(new_data, _data+_front, sizeof(int) * (_cap - _front));
						memcpy(new_data + (_cap - _front), _data, sizeof(int) *(_back+1));
						_front = 0;
						_back = _cap -1;
					}
					int* tmp = _data;
					_data = new_data;
					_cap = new_cap;
					free(tmp);

				}
				_back = (_back+1)%_cap;
				_data[_back] = a;
				_size++;
				return;
			}
			void pop()
			{
				_front = (_front + 1) %_cap;
				_size--;
			}
			std::string name()
			{
				return "MyQueue";
			}
			void print()
			{
				int idx;
				printf("MyQueue:");
				for(int i = 0; i < _size; i++)
				{
					idx = (i + _front)%_cap;
					printf("%d", _data[idx]);
					if(idx == _front)
					{
						printf("(front)");
					}
					if(idx == _back)
					{
						printf("(back)");
					}
					printf(", ");
				}
				printf("\n");
			}
			void clear()
			{
				_front = -1;
				_back = -1;
				_size = 0;
			}
			int size()
			{
				return _size;
			}
			bool empty()
			{
				return _size==0;
			}

		private:
			//std::vector<int> _vec;
			int* _data;
			int _size;
			int _cap;
			int _front;
			int _back;
	};
}


#endif
