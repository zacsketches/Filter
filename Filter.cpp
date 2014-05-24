#include "Filter.h"

//*******************************************************************
//*                         LIST DEFINITIONS
//*******************************************************************

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

// return sum of Nodes in the list
int List::sum(){
	Node* p = head;
	int sum = 0;
	while(p != 0){
		sum += p->data;
	}
	return sum;
}