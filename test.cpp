/*
	test program to develop filter classes
*/ 

#include <iostream>
#include "Filter.h"

using namespace std;

void test_append() {
	List L;
	cout<<"Length of L: "<<L.len()<<endl;
	L.append(1);
	cout<<"Length of L: "<<L.len()<<endl;
	
}

int main (int argc, char const *argv[])
{
	test_append();
	return 0;
}