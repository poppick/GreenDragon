#ifndef __LIST_H__
#define __LIST_H__

namespace mycode{
struct List
{
	int v;
	List* next;
};

class MyList
{
	public:
		MyList()
		:_head(NULL), _tail(NULL)
		{}
		~MyList()
		{
			List* p = _head;
			List* tmp;
			while(p != NULL)
			{
				tmp = p;
				p=p->next;
				//free(tmp);
			}
			_head = NULL;
			_tail = NULL;
		}
		void push_back(int a)
		{
			List* node = (List*)malloc(sizeof(List));
			if(node == NULL)
			{
				fprintf(stderr, "malloc List node failed\n");
				return;
			}
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
		void print()
		{
			List* p = _head;
			while(p)
			{
				printf("%d", p->v);
				if(p == _head)
				{
					printf("(head)");
				}
				if(p == _tail)
				{
					printf("(tail)");
				}
				printf("->");
				p=p->next;
			}
			printf("NULL\n");
			return;
		}
		void revert()
		{
			if(_head == NULL || _head->next == NULL)
			{
				return;
			}
			_tail = _head;
			List *pre, *p, *post;
			pre = NULL;
			p = _head;
			post = _head->next;

			while(post != NULL)
			{
				p->next = pre;
				pre = p;
				p = post;
				post = post->next;
			}
			p->next = pre;
			_head = p;
			return;
		}
		//移除第一个等于a的结点, 如果找不到则不做任何操作
		void remove(int a)
		{
			if(_head == NULL)
			{
				return;
			}
			List *tmp, *p;
			if(_head->v == a)
			{
				tmp = _head;
				_head = _head->next;
				if(_head == NULL)
				{
					_tail = NULL;
				}
				free(tmp);
				return;
			}
			p = _head;
			while(p->next && p->next->v != a)
			{
				p = p->next;
			}
			if(p->next == NULL) //没找到
			{
				//do nothing
			}else{
				tmp = p->next;
				if(tmp == _tail)
				{
					_tail = p;
				}
				p->next = tmp->next;
				free(tmp);
			}
			return;
		}
		void clear()
		{
			List *p, *tmp;
			p = _head;
			while(p)
			{
				tmp = p;
				p = p->next;
				free(tmp);
			}
			_head = NULL;
			_tail = NULL;

		}
	protected:
		List* _head;
		List* _tail;

};

}
#endif
