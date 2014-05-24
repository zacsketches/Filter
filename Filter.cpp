#include "Filter.h"

//*******************************************************************
//*                         LIST DEFINITIONS
//*******************************************************************

//Destructor
FIFO_list::~FIFO_list() { 
	Node* p = head;
	Node* q;
	while (p != NULL){
		q = p;
		p = p->next;
		delete q;
		//std::cout<<"destroying node"<<std::endl;
	}
}

// add elem to the end of L
void FIFO_list::append(int elem) {
	Node* newNode = new Node;
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

//print element values to cout
void FIFO_list::print() {
	Node* p = head;
	while (p != NULL){
		std::cout<<"\t"<<p->data<<std::endl;
		p = p->next;
	}
}

// return sum of Nodes in the list
int FIFO_list::sum(){
	Node* p = head;
	int sum = 0;
	while(p != 0){
		sum += p->data;
		p = p->next;
	}
	return sum;
}

// add new data to the FIFO list
void FIFO_list::add(int new_data) {
	//append the new_data
	if(head != NULL){
		Node* p = head;
		append(new_data);
		head = head->next;
		delete p;
	}
}

//*******************************************************************
//*                         MOVING AVERAGE DEFINITIONS
//*******************************************************************

//CONSTRUCTOR
Moving_average::Moving_average(int length, int default_data) 
	:len(length), his(len-1) {
	
	for(size_t i = 0; i < his; ++i) {
		data.append(default_data);
	}	
}

//filter an incoming data point and return the filtered value
int Moving_average::filter(int new_data) {
		int result = data.sum() + new_data;
		result = result / len;
		
		//add the new data point to the history			
		data.add(new_data);
		
		return result;		
}

//change the length of filtered data
