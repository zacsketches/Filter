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
// the Arduino IDE, and comment out the COMPILE directive below
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
template <typename T>
struct Node {
  T data;     // data field
  Node* next;   // link field
};

// declare the list header structure
template <typename T>
struct FIFO_list {
	int cnt;
	Node<T>* head;
	Node<T>* tail;
	
	//constructor
	FIFO_list(): cnt(0), head(NULL), tail(NULL) {}
	//destructor
	~FIFO_list();

	// len returns the number of elements in L
	int len( ) { return cnt; }

	// add elt to the end of L
	void append(T elem);
	
	void inline remove_node(Node<T>* p);
	
	//return sum of elements
	T sum();
	
	//add the new data to the FIFO List, pushing out oldest data
	void add(T new_data);
	
#ifdef COMPILE_FOR_CMD_LINE_TEST
	//show the elements
	void print();
#endif

	
};

//*******************************************************************
//*                         MOVING AVERAGE
//*******************************************************************
template <typename T>
class Moving_average{
	int len;	//length of historical data to smooth.
						//For example, to average the last three data points
						//plus the current data, len would be 4.
						
	int his;	//length of historical data to store.  If len is 4
						//then his is 3.
	
	FIFO_list<T> data;	//points to first data element
	T ca;			//current average
	

public:
	//CONSTRUCTOR
	//default data for the history is optional, but recommended
	//when filtering write positions for servos.  I like to use the
	//servo default position (usually 90) as the default data
	//for this filter 
	Moving_average(int length, T default_data=0);
	
	const int length() { return len;} 
	
	/*
		TODO Consider adding the set_length function below to allow
		users to change the length of filtered data.  I don't need
		this function now, so I'm leaving it for future work should
		a need arise.
	*/
	//void set_length(const int length);
	
    //get and set the current average
    T current() {return ca;}
	void set_current(const T val) {ca = val;}
	
	//add a new data point and return the filtered result.  filter() also
	//sets current
	T filter(T new_data);	

};

#endif

//*******************************************************************
//*                         LIST DEFINITIONS
//*******************************************************************

//Destructor
template <typename T>
FIFO_list<T>::~FIFO_list() { 
	Node<T>* p = head;
	Node<T>* q;
	while (p != NULL){
		q = p;
		p = p->next;
		delete q;
		
		#ifdef COMPILE_FOR_CMD_LINE_TEST
			std::cout<<"destroying node"<<std::endl;
		#endif
	}
}

// remove an element
template <typename T>
void inline FIFO_list<T>::remove_node(Node<T>* p){
	--cnt;
	delete p;
}

// add elem to the end of L
template <typename T>
void FIFO_list<T>::append(T elem) {
	Node<T>* newNode = new Node<T>;
	newNode->data = elem;
	newNode->next = 0;

	if (cnt == 0) {
		head = tail = newNode;
	}
	else {
		tail->next = newNode;
		tail = newNode;
	}
	cnt++;
}

// return sum of Nodes in the list
template <typename T>
T FIFO_list<T>::sum(){
	Node<T>* p = head;
	T sum = 0;
	while(p != 0){
		sum += p->data;
		p = p->next;
	}
	return sum;
}

// add new data to the FIFO list
template <typename T>
void FIFO_list<T>::add(T new_data) {
	//append the new_data
	if(head != NULL){
		Node<T>* p = head;
		append(new_data);
		head = head->next;
		remove_node(p);
	}
}

#ifdef COMPILE_FOR_CMD_LINE_TEST
	//print element values to cout
	template <typename T>
	void FIFO_list<T>::print() {
		Node<T>* p = head;
		while (p != NULL){
			std::cout<<"\t"<<p->data<<std::endl;
			p = p->next;
		}
	}
#endif


//*******************************************************************
//*                         MOVING AVERAGE DEFINITIONS
//*******************************************************************

//CONSTRUCTOR
template <typename T>
Moving_average<T>::Moving_average(int length, T default_data) 
	:len(length), his(len-1) {
	
	for(size_t i = 0; i < his; ++i) {
		data.append(default_data);
	}	
}


//filter an incoming data point and return the filtered value
template <typename T>
T Moving_average<T>::filter(T new_data) {
		T result = data.sum() + new_data;
		result = result / (T)len;
		
		//add the new data point to the history			
		data.add(new_data);
		
		//update the current average
		set_current(result);
		
		return result;		
}
