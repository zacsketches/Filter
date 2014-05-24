#include "Filter.h"

//*******************************************************************
//*                         LIST DEFINITIONS
//*******************************************************************

//Destructor
List::~List() { 
	Node* p = head;
	Node* q;
	while (p != NULL){
		q = p;
		p = p->next;
		delete q;
		std::cout<<"destroying node"<<std::endl;
	}
}

// add elem to the end of L
void List::append(int elem) {
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
void List::print() {
	Node* p = head;
	while (p != NULL){
		std::cout<<"\t"<<p->data<<std::endl;
		p = p->next;
	}
}

// return sum of Nodes in the list
int List::sum(){
	Node* p = head;
	int sum = 0;
	while(p != 0){
		sum += p->data;
		p = p->next;
	}
	return sum;
}