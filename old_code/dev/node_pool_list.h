#ifndef __NODE_POOL_LIST_H__
#define __NODE_POOL_LIST_H__

#include "list.h"
#include <vector>


namespace mycode
{

	class NodePool
	{
		public:
			NodePool()
			{
				_nodes = (List*)malloc(sizeof(List)*count);
				_cur = 0;
			}
			List* get()
			{
				//
				//List* node = (List*)malloc(sizeof(List));



				if(_cur == count)
				{
					_nodes = (List*)malloc(sizeof(List)*count);
					_cur = 0;
				}

				_cur++;
				return &_nodes[_cur-1];
				//return node;
			}
			void back(List* l)
			{
				//free(l);
				return;
			}
		private:
			//std::vector<List*> _node_vec;
			List* _nodes;
			int _cur;
			static const int count = 1000;

	};

	class NodePoolList : public MyList 
	{
		public:
			~NodePoolList(){}
			void push_back(int a)
			{
				/*List* node = (List*)malloc(sizeof(List));
				if(node == NULL)
				{
					fprintf(stderr, "malloc List node failed\n");
					return;
				}*/

				List* node = _node_pool.get();
				node->v = a;
				node->next = NULL;
				if(_head ==NULL)
				{
					_head = node;
					_tail = node;

				}else{
					_tail->next = node;
					_tail = _tail->next;
				}
				return;
			}
		private:
			NodePool _node_pool;
	};

}


#endif
