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

// Uncomment the line below to run as an Arduino library from
// the Arduino IDE, and commend out the COMPILE directive below
// for command line testing
#define COMPILE_FOR_ARDUINO

// Uncomment the lines below to compile the Dev_test main()
// Also comment out the Arduino lines above
// #define COMPILE_FOR_CMD_LINE_TEST

#ifdef COMPILE_FOR_ARDUINO
	#include "Arduino.h"
#endif

#ifdef COMPILE_FOR_CMD_LINE_TEST
	#include <cstdio>	//for access to NULL
	#include <iostream>	//for debug access to cout
#endif

//*******************************************************************
//*                         Node and FIFO_list
//*  Filters use a linked list data structure to hold their historical
//*  values.
//*******************************************************************
// declaring a list node structure
struct Node {
  int data;     // data field
  Node* next;   // link field
};

// declare the list header structure
struct FIFO_list {
	int cnt;
	Node* head;
	Node* tail;
	
	//constructor
	FIFO_list(): cnt(0), head(NULL), tail(NULL) {}
	//destructor
	~FIFO_list();

	// len returns the number of elements in L
	int len( ) { return cnt; }

	// add elt to the end of L
	void append(int elem);
	
	void inline remove_node(Node* p);
	
	//return sum of elements
	int sum();
	
	//add the new data to the FIFO List, pushing out oldest data
	void add(int new_data);
	
#ifdef COMPILE_FOR_CMD_LINE_TEST
	//show the elements
	void print();
#endif

	
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
	
	FIFO_list data;	//points to first data element
	

public:
	//CONSTRUCTOR
	//default data for the history is optional, but recommended
	//when filtering write positions for servos.  I like to use the
	//servo default position (usually 90) as the default data
	//for this filter 
	Moving_average(int length, int default_data=0);
	
	const int length() { return len;} 
	
	/*
		TODO Consider adding the set_length function below to allow
		users to change the length of filtered data.  I don't need
		this function now, so I'm leaving it for future work should
		a need arise.
	*/
	//void set_length(const int length);
	
  //return the current value of the average
  int current();
	
	//add a new data point and return the filtered result
	int filter(int new_data);	

};

#endif