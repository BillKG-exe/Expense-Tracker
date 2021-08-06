#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>

using namespace std;

class LinkedList {
	 private:
		  struct Node {
				string key;
				double val;
				Node* next;
		  };

		  Node* head;
		  int listSize;

	 public:
		  LinkedList() { 
				head = NULL;
				listSize = 0;
		  }

		  //Used to append data in the linked list
		  void append(string k, double v) {
				Node* nodePtr;
				Node* newNode;

				newNode = new Node;
				newNode->key = k;
				newNode->val = v;
				newNode->next = nullptr;

				if (!head)
					 head = newNode;
				else {
					 nodePtr = head;

					 while (nodePtr->next)
						  nodePtr = nodePtr->next;

					 nodePtr->next = newNode;
				}

				listSize++;
		  }

		  void print() {
				Node* nodePtr = head;

				while (nodePtr) {
					 cout << nodePtr->key << " -> " << nodePtr->val << endl;
					 nodePtr = nodePtr->next;
				}
		  }

		  //Return a vector of double version of the list
		  vector<double> convert() {
				vector<double> data;
				Node* nodePtr = head;

				while (nodePtr) {
					 data.push_back(nodePtr->val);
					 nodePtr = nodePtr->next;
				}

				return data;
		  }

		  //Change the value of a specific key
		  void changeVal(string k, double v) {
				Node* nodePtr;

				if (!head)
					 cout << "List is empty." << endl;
				else {
					 nodePtr = head;
					 while (nodePtr) {
						  if (nodePtr->key == k) {
								nodePtr->val = v;
								break;
						  }
						  nodePtr = nodePtr->next;
					 }
				}
		  }

		  //Get the value of a key
		  //Return value of key
		  double getVal(string k) {
				Node* nodePtr;

				if (!head)
					 cout << "List is empty." << endl;
				else {
					 nodePtr = head;
					 while (nodePtr) {
						  if (nodePtr->key == k) {
								return nodePtr->val;
								break;
						  }
								
						  nodePtr = nodePtr->next;
					 }
				}
				return 0;
		  }

		  //Used to delete the nodes after use
		  void deleteNodes() {
				Node* nodePtr;
				Node* nextNode;

				nodePtr = head;

				while (nodePtr != nullptr)
				{
					 nextNode = nodePtr->next;
					 delete nodePtr;
					 nodePtr = nextNode;
				}
		  }

		  bool empty() { return listSize == 0 ; }
		  int size() { return this->listSize; }
};

#endif
