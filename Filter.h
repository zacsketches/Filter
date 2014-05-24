/*
 *	I'd like to have a library I can call for basic filtering operations.
 *	
 *	Most sensors in small scale robotics are noisy.  For example as a
 *	mobile robot approaches a wall, an atached ulrasonic sensor should
 *	give readings in cm similar to the list below
 *
 *	11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, ...bump!
 *
 *	but all too often the data will come back like this
 *
 *  11, 10, 6, 8, 7, 3, 5, 4, 1, 2, 1, ..bump!
 *
 *  By filtering the raw data, via a moving average or other more 
 *	specialized filter we can use the noisy data as an input to our
 *	filter and then the processed data will give us a better linear
 *	output.  This linear output still doesn't match the exact distance
 *  to the wall, but it is a much closer approximation than the noisy
 *	data and provides a better set of data for the robot to make 
 *	control decisions from.
 *
 *	Since this filter library is designed to support Arduino applications
 *  I'm limiting it to only work on integer data.  I might add templating
 *  for arbitrary numeric types, but most Arduino users don't know how
 *  to instantiate a templated class, so it might not every get used.
 *
 */

#ifndef FILTER_h
#define FILTER_h 

//#define NULL 0

#include <cstdio>	//for access to NULL
#include <iostream>	//for debug access to cout
#include "Filter.h"

//*******************************************************************
//*                         Node and List
//*  Filters use a linked list data structure to hold their historical
//*  values.
//*******************************************************************
// declaring a list node structure
struct Node {
  int data;     // data field
  Node* next;   // link field
};

// declare the list header structure
struct List {
	int cnt;
	Node* head;
	Node* tail;
	
	//constructor
	List(): cnt(0), head(NULL), tail(NULL) {}
	//destructor
	~List();

	// len returns the number of elements in L
	int len( ) { return cnt; }

	// add elt to the end of L
	void append(int elem);
	
	//return sum of elements
	int sum();
	
	//show the elements
	void print();
	
};

//*******************************************************************
//*                         MOVING AVERAGE
//*******************************************************************
class Moving_average{
	int len;	//length of historical data to smooth.
						//For example, to average the last three data points
						//plus the current data, len would be 4.
						
	int his;	//length of historical data to store.  If len is 4
						//then his is 3.
	
	List data;	//points to first data element
	

public: 
	Moving_average(int length, int default_data) 
		:len(length), his(len-1) {
		
		//build a list of length his, with data of default_data
	}
	
	
	
	// int filter(int new_data){
	// 	//add a new data point and return the filtered result
	// 	int result = sum() + new_data;
	// 	result = result / len;
	// 	
	// 	//shift the historical data
	// 	for(size_t i = 0; i < his; ++i) {
	// 		data[2] = data[1];
	// 		data[1] = data[0];
	// 		data[0] = new_data;
	// 	}
	// 	
	// 	shift(data, data[1], 2)
	// 	
	// }
	// 
	// void shift(int* array, int elem, int index){
	// 	if(index >= 0){	
	// 		array[index] = data;
	// 		--index;
	// 		data = array[index];
	// 	}		
	// }
	
};


#endif