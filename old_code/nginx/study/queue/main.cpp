#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <list>
#include "ngx_queue.h"
#include <assert.h>
#include <queue> 

using namespace std;

timeval start,end;

struct TestNode
{
	//char a[100];
	ngx_queue_t qEle;
	int b;
};

struct TestNode_stl
{
	//char a[100];
	int b;
};

void print_time(const char* info="")
{
	gettimeofday(&end,0);
	double cost = end.tv_sec - start.tv_sec + double(end.tv_usec - start.tv_usec)/1000000;
	printf("%s\tcost = %.4f\n",info,cost);
}

void print_nq(ngx_queue_t &nq)
{
	printf("\nprint_nq:\n");
	int i=0;
	for(ngx_queue_t* p=ngx_queue_head(&nq);
		p!=ngx_queue_sentinel(&nq);
		p=ngx_queue_next(p))
	{
		TestNode* node = ngx_queue_data(p,TestNode,qEle);
		printf("\tnode[%d]->b=%d,node=%p\n",i,node->b,node);
		i++;
	}
}

void print_sl(list<TestNode_stl*> &sl)
{
	printf("\nprint_sl:\n");
	int i=0;
	for(list<TestNode_stl*>::iterator iter = sl.begin();iter!=sl.end();iter++)
	{
		TestNode_stl* node = *iter;
		printf("\tnode[%d]->b=%d,node=%p\n",i,node->b,node);
		i++;
	}
}

int main()
{
	//push/pop性能
	int i;
	int max=300000;
	TestNode nodes[max];
	TestNode_stl snodes[max];
	ngx_queue_t * ptr;
	
	for(int j=0;j<max;j++)
	{
		nodes[j].b=j;
		snodes[j].b=j;
	}
	
	ngx_queue_t nq;
	ngx_queue_init(&nq);
	printf("nginx queue test:\n");
	gettimeofday(&start,0);
	
	i=0;	
	for(;i<max/2;i++)
	{
		ngx_queue_insert_head(&nq,&(nodes[i].qEle));
	}
	print_time("nq push head");
	for(;i<max;i++)
	{
		ngx_queue_insert_tail(&nq,&nodes[i].qEle);
	}
	print_time("nq push back");
	i=0;
	for(;i<max/2;i++)
	{
		ptr = ngx_queue_last(&nq);
		ngx_queue_remove(ptr);
	}
	print_time("nq pop back");
	for(;i<max;i++)
	{
		ptr = ngx_queue_head(&nq);
		ngx_queue_remove(ptr);
	}
	print_time("nq pop head");
	assert(ngx_queue_empty(&nq));

	printf("stl list test:\n");
	list<TestNode_stl*> sl;
	i=0;
	gettimeofday(&start,0);
	for(;i<max/2;i++)
	{
		sl.push_back(&snodes[i]);
	}
	print_time("sl push back");
	for(;i<max;i++)
	{
		sl.push_front(&snodes[i]);
	}
	print_time("sl push head");
	assert(sl.size() == max);

	i=0;
	for(;i<max/2;i++)
	{   
		sl.pop_back();
	}   
	print_time("sl pop back");
	for(;i<max;i++)
	{
		sl.pop_front();
	}   
	print_time("sl pop head");
	assert(sl.empty());

	printf("\n\nstl queue test:\n");
	queue<TestNode_stl*> sq;
	i=0;
	gettimeofday(&start,0);
	for(;i<max/2;i++)
	{
		sq.push(&snodes[i]);
	}
	print_time("sq push head");
	for(;i<max;i++)
	{
		sq.push(&snodes[i]);
	}
	print_time("sq push head");
	assert(sq.size() == max);

	i=0;
	for(;i<max/2;i++)
	{
		sq.pop();
	}
	print_time("sq pop back");
	for(;i<max;i++)
	{
		sq.pop();
	}
	print_time("sq pop back");
	assert(sq.empty());

	ngx_queue_insert_tail(&nq,&nodes[0].qEle);
	print_nq(nq);
	ngx_queue_insert_tail(&nq,&nodes[1].qEle);
	print_nq(nq);
	ngx_queue_insert_tail(&nq,&nodes[2].qEle);
	print_nq(nq);
	ngx_queue_insert_tail(&nq,&nodes[1].qEle);
	print_nq(nq);

	sl.push_back(&snodes[0]);
	print_sl(sl);
	sl.push_back(&snodes[1]);
	print_sl(sl);
	sl.push_back(&snodes[2]);
	print_sl(sl);
	sl.push_back(&snodes[1]);
	print_sl(sl);
	return 0;
}
