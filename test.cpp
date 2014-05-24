/*
	test program to develop filter classes
*/ 

#include <iostream>
#include "Filter.h"

using namespace std;

void test_append() {
	List L;
	cout<<"Testing append and print:\n";
	cout<<"Length of L: "<<L.len()<<endl;
	L.append(1);
	L.append(2);
	L.append(3);
	L.append(4);
	L.append(5);
	cout<<"Length of L: "<<L.len()<<endl;
	
	cout<<"List contains: "<<endl;
	L.print();
	
}

void test_sum() {
	List L;
	L.append(1);
	L.append(2);
	L.append(3);
	L.append(4);
	L.append(5);
	cout<<"The sum of the nodes is: "<<L.sum()<<endl;
}

int main (int argc, char const *argv[])
{
	test_append();
	test_sum();
	return 0;
}