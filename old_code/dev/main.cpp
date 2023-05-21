#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "timer.h"
#include <unistd.h>
#include "data.h"
#include "vec.h"
#include <list>
#include "stack.h"
#include "queue.h"
#include <stack>
#include <queue>
#include "linear_container.h"
#include "node_pool_list.h"
using namespace mycode;


void performance_test(int count)
{
	vector<int> data_vec;
	Timer timer;

	gen_nums(count, "list_data.txt");
	load_nums("list_data.txt", data_vec);
	printf("测试插入性能: 插入%d个int\n", count);




	MyList list;
	timer.start();
	for(int i=0; i< data_vec.size(); i++)
	{
		list.push_back(data_vec[i]);
	}
	timer.end();
	printf("MyList push_back %d nums cost %.2fms\n", count, timer.cost());


	NodePoolList node_pool_list;
	timer.start();
	for(int i=0; i< data_vec.size(); i++)
	{
		node_pool_list.push_back(data_vec[i]);
	}
	timer.end();
	printf("node_pool_list push_back %d nums cost %.2fms\n", count, timer.cost());

	return;

	std::list<int> stl_list;
	timer.start();
	for(int i=0; i< data_vec.size(); i++)
	{
		stl_list.push_back(data_vec[i]);
	}
	timer.end();
	printf("STL list push_back %d nums cost %.2fms\n", count, timer.cost());
	stl_list.clear();



	MyVector my_vec2;
	timer.start();
	for(int i=0; i< data_vec.size(); i++)
	{
		my_vec2.push_back(data_vec[i]);
	}
	timer.end();
	printf("MyVector push_back %d nums cost %.2fms\n", count, timer.cost());
	my_vec2.clear();

	
	vector<int> stl_vec;
	timer.start();
	for(int i=0; i< data_vec.size(); i++)
	{
		stl_vec.push_back(data_vec[i]);
	}
	timer.end();
	printf("STL vector push_back %d nums cost %.2fms\n", count, timer.cost());
	stl_vec.clear();


	MyStack my_stack;
	timer.start();
	for(int i=0; i< data_vec.size(); i++)
	{
		my_stack.push(data_vec[i]);
	}
	for(int i=0; i< data_vec.size(); i++)
	{
		my_stack.pop();
	}
	timer.end();
	printf("MyStack push and pop %d nums cost %.2fms\n", count, timer.cost());
	my_stack.clear();
	
	std::stack<int> stl_stack;
	timer.start();
	for(int i=0; i< data_vec.size(); i++)
	{
		stl_stack.push(data_vec[i]);
	}
	for(int i=0; i< data_vec.size(); i++)
	{
		stl_stack.pop();
	}
	timer.end();
	printf("STL Stack push and pop %d nums cost %.2fms\n", count, timer.cost());
	//stl_stack.clear();

	MyQueue my_queue;
	timer.start();
	for(int i=0; i< data_vec.size(); i++)
	{
		my_queue.push(data_vec[i]);
	}
	for(int i=0; i< data_vec.size(); i++)
	{
		my_queue.pop();
	}
	timer.end();
	printf("MyQueue push and pop %d nums cost %.2fms\n", count, timer.cost());
	my_queue.clear();
	
	std::queue<int> stl_queue;
	timer.start();
	for(int i=0; i< data_vec.size(); i++)
	{
		stl_queue.push(data_vec[i]);
	}
	for(int i=0; i< data_vec.size(); i++)
	{
		stl_queue.pop();
	}
	timer.end();
	printf("STL Queue push and pop %d nums cost %.2fms\n", count, timer.cost());
	//stl_queue.clear();




}

void performance_my_container(LinearContainer* container, int count)
{
	vector<int> data_vec;
	Timer timer;

	gen_nums(count, "data/container_data.txt");
	load_nums("data/container_data.txt", data_vec);
	printf("\n测试线性容器%s的插入性能: 插入%d个int\n", container->name().c_str(), count);

	timer.start();
	for(int i=0; i< data_vec.size(); i++)
	{
		container->push(data_vec[i]);
	}
	for(int i=0; i< data_vec.size(); i++)
	{
		container->pop();
	}
	timer.end();
	printf("%s push and pop %d nums cost %.2fms\n", container->name().c_str(), count, timer.cost());
	return;
}


int main()
{
	mycode::MyList list;
	Timer timer;
	timer.start();
	list.push_back(1);
	list.print();
	list.push_back(2);
	list.push_back(3);
	list.push_back(4);
	list.push_back(5);
	list.push_back(6);
	list.print();
	list.revert();
	list.print();
	
	list.push_back(9);
	list.print();
	list.revert();
	list.print();

	list.remove(9);
	list.print();
	list.remove(5);
	list.remove(3);
	list.remove(1);
	list.remove(3);
	list.remove(4);
	list.remove(2);
	list.remove(6);
	list.print();

	list.remove(5);
	list.remove(3);
	list.remove(1);
	list.remove(3);
	list.print();
	//sleep(5);
	timer.end();
	printf("cost %.2fms\n", timer.cost());
	list.clear();

	
	MyVector my_vec;
	
	my_vec.push_back(1);
	my_vec.push_back(3);
	my_vec.push_back(4);
	my_vec.push_back(5);

	my_vec.push_back(1);
	my_vec.push_back(3);
	my_vec.push_back(4);
	my_vec.push_back(5);
	my_vec.push_back(1);
	my_vec.push_back(3);
	my_vec.push_back(4);
	my_vec.push_back(5);
	my_vec.print();
	printf("my_vec size=%d, cap=%d, my_vec[6]=%d\n", my_vec.size(), my_vec.cap(), my_vec[6]);
	my_vec.clear();
	printf("my_vec size=%d, cap=%d, my_vec[6]=%d\n", my_vec.size(), my_vec.cap(), my_vec[6]);
	
	
	MyStack my_stack;
	my_stack.push(1);
	my_stack.push(2);
	my_stack.push(3);
	my_stack.pop();
	my_stack.push(4);
	my_stack.print();
	

	MyQueue my_queue;
	my_queue.print();
	my_queue.push(1);
	my_queue.print();
	my_queue.push(2);
	my_queue.print();
	my_queue.push(3);
	my_queue.print();
	my_queue.push(4);
	my_queue.print();

	my_queue.pop();
	my_queue.print();
	my_queue.pop();
	my_queue.print();
	my_queue.pop();
	my_queue.print();
	my_queue.pop();
	my_queue.print();



	my_queue.push(5);
	my_queue.print();
	my_queue.push(6);
	my_queue.print();
	my_queue.push(7);
	my_queue.print();
	my_queue.push(8);
	my_queue.print();
	my_queue.push(9);
	my_queue.print();
	my_queue.push(10);
	my_queue.print();




	performance_test(5000000);
	
	MyStack my_stack2;
	int count = 5000000;
	//performance_my_container(&my_stack2, count);

	MyQueue my_queue2;
	//performance_my_container(&my_queue2, count);



	return 0;
}
