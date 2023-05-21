#ifndef __TIMER_H__
#define __TIMER_H__
#include <stdlib.h>
#include <sys/time.h>

namespace mycode
{
	class Timer
	{
		public:
			void start()
			{
				int a = gettimeofday(&_start, NULL);
				if(a != 0)
				{
					fprintf(stderr, "gettimeofday err\n");
					return;
				}
			}
			void end()
			{
				int a = gettimeofday(&_end, NULL);
				if(a != 0)
				{
					fprintf(stderr, "gettimeofday err\n");
					return;
				}
			}
			double cost()
			{
				return (_end.tv_sec - _start.tv_sec)*1000 + double(_end.tv_usec - _start.tv_usec) / 1000;
			}
		private:
			timeval _start;
			timeval _end;
	};
}


#endif

