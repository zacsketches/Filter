/*
	test program to develop filter classes
*/ 

#include <iostream>
#include "Filter.h"

using namespace std;

void test_append() {
	FIFO_list L;
	cout<<"Testing append and print:\n";
	cout<<"Length of L: "<<L.len()<<endl;
	L.append(1);
	L.append(2);
	L.append(3);
	L.append(4);
	L.append(5);
	cout<<"Length of L: "<<L.len()<<endl;
	
	cout<<"FIFO_list contains: "<<endl;
	L.print();
	
}

void test_sum() {
	FIFO_list L;
	L.append(1);
	L.append(2);
	L.append(3);
	L.append(4);
	L.append(5);
	cout<<"The sum of the nodes is: "<<L.sum()<<endl;
}

void test_add() {
	cout<<"\nTesting FIFO add: \n";
	FIFO_list L;
	L.append(1);
	L.append(2);
	L.append(3);
	cout<<"\tThe original List contains: \n";
	L.print();
	cout<<"\tadding 4\n";
	L.add(4);
	cout<<"\tThe changed list is: \n";
	L.print();
	
	cout<<"\nTesting FIFO add on empty list: \n";
	FIFO_list L2;
	cout<<"\tThe original List contains: \n";
	L2.print();
	cout<<"\tadding 4\n";
	L2.add(4);
	cout<<"\tThe changed list is: \n";
	L2.print();
	
}

void test_ma() {
	cout<<"\nTesting moving average\n";
	Moving_average ma(3);
	
	cout<<"\tThe length of the average is: "<<ma.length()<<endl;
	cout<<"\tfiltering 9 five times.\n";
	for(size_t i = 0; i < 5; ++i) {
		int res = ma.filter(9);
		cout<<"\t filtered return is: "<<res<<endl;
	}
	
	Moving_average ma2(6, 60);
	
	cout<<"\tThe length of the average is: "<<ma2.length()<<endl;
	cout<<"\tfiltering 45 fifteen times.\n";
	for(size_t i = 0; i < 15; ++i) {
		int res = ma2.filter(45);
		cout<<"\t filtered return is: "<<res<<endl;
	}
	
}

int main (int argc, char const *argv[])
{
	test_append();
	test_sum();
	test_add();
	
	test_ma();
	return 0;
}