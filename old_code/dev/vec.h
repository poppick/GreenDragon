#ifndef __VEC_H__
#define __VEC_H__

namespace mycode
{
	class MyVector
	{
		public:
			MyVector()
			:_data(NULL), _size(0),_cap(0)
			{}
			~MyVector()
			{
				if(_data != NULL)
				{
					free(_data);
					_size = 0;
					_cap = 0;
				}
			}
			void push_back(int a)
			{
				if(_size == _cap)
				{
					int new_cap = _cap*2 +8;
					int *new_data = (int*)malloc(new_cap * sizeof(int));
					if(NULL  == new_data)
					{
						fprintf(stderr, "myVector malloc failed!\n");
						return;
					}
					memcpy(new_data, _data, _size * sizeof(int));
					_cap = new_cap;
					int* tmp = _data;
					_data = new_data;
					free(tmp);
				}

				_data[_size++] = a;
			}

			void clear()
			{
				_size = 0;
			}
			int size()
			{
				return _size;
			}
			int operator[](int a)
			{
				return _data[a];
			}
			int cap(){return _cap;}
			void print()
			{
				printf("[");
				for(int i = 0; i < _size; i++)
				{
					printf("%d, ", _data[i]);
				}
				printf("]\n");
			}





		private:
		private:
			int* _data;
			int _size;
			int _cap;
	};
}


#endif
