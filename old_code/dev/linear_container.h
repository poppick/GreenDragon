#ifndef __LINEAR_CONTAINER_H__
#define __LINEAR_CONTAINER_H__

#include <string>

namespace mycode
{
	class LinearContainer
	{
		public:
			virtual void push(int a) = 0;
			virtual void pop() = 0;
			virtual int size() = 0;
			virtual bool empty() = 0;
			virtual void clear() = 0;

			virtual std::string name() = 0;
			virtual void print() = 0;
	};
}


#endif
