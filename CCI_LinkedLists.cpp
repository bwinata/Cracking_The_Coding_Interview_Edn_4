#include <iostream>
#include <list>
#include <set>
#include <map>

using namespace std;

class LinkedList {
private:
	typedef struct _node_ {
		int value;
		_node_ * next;
	} node;

	node * head;
	node * tail;

	node * createNode (int value) {
		try {
			node * newNode = new node;
			newNode->value = value;
			newNode->next = NULL;

			return newNode;
		} catch (bad_alloc & e) {
			cout << "Exception: Cannot create node. Not enough memory" << endl;
		}
	}

/* --------------------------------------------------------------------------
 * Question 2.3
 * --------------------------------------------------------------------------
 * Implement an algorithm to delete a node in the middle of a single linked 
 * list, given only access to that node.
 * 
 * EXAMPLE
 * Input: the node ‘c’ from the linked list a->b->c->d->e
 * Result: nothing is returned, but the new linked list looks like a->b->d->e
 */
 	void solutionOne_2_3 (node * x) {
 		// Check that next node is not null i.e. Not the tail
 		if (x == NULL || x->next == NULL) throw new string ("Exception: Cannot delete node");
 		else {
 			// Swap contents between both nodes.
 			int tmp = x->value;
 			node * tmpNode = x->next;
 			x->value = x->next->value;
 			x->next->value = tmp;

 			x->next = x->next->next;
 			delete tmpNode;
 		}	
 	}

public:
	LinkedList () {
		this->head = this->tail = NULL;
	}

	void push_back (int value) {
		if (this->head == NULL && this->tail == NULL) {
			this->head = this->tail = this->createNode (value);
		} else {
			this->tail->next = this->createNode (value);
			tail = this->tail->next;
		}
	}

	void push_front (int value) {
		if (this->head == NULL && this->tail == NULL) {
			this->head = this->tail = this->createNode (value);
		} else {
			node * temp = this->createNode (value);
			temp->next = this->head;
			this->head = temp;
		}
	}

	void printList (void) {
		node * traveler = this->head;

		while (traveler != NULL) {
			cout << traveler->value << " ";
			traveler = traveler->next;
		}
		cout << endl;
	}

/* --------------------------------------------------------------------------
 * Question 2.1
 * --------------------------------------------------------------------------
 * Write code to remove duplicates from an unsorted linked list.
 * 
 * FOLLOW UP
 * How would you solve this problem if a temporary buffer is not allowed?
 */

/* Solution One - No temporary buffer is required. Utilises a dummy node
 * 				  which keeps track of the previous node. 
 * 				  T(n) = O(n^2)
 */

	void solutionOne_2_1 (void) {
		if (this->head == NULL || this->tail == NULL) return;
		else {
			node * traveler = this->head;
			while (traveler != NULL) {
				node * checker = traveler->next;
				node * prev = traveler;
				while (checker != NULL) {
					if (traveler->value == checker->value) {
						node * temp = checker;
						prev->next = checker->next;
						checker = prev->next;
						delete temp;
					} else {
						prev = checker;
						checker = checker->next;	
					}
				}
				traveler = traveler->next;
			}
		}
	}

	/* Question - 2.3 caller function
	 * NB: The handler function is made private because for this list
	 * the node data structure is also made private
	 */
	void solutionOne_2_3_caller (void) {
		try {
			solutionOne_2_3	(this->head->next);
		} catch (string * e) {
			cout << *e << endl;
		}
	}


/* --------------------------------------------------------------------------
 * Question 2.5
 * --------------------------------------------------------------------------
 * Given a circular linked list, implement an algorithm which returns node at
 * the beginning of the loop.
 * DEFINITION
 * Circular linked list: A (corrupt) linked list in which a node’s next 
 * pointer points to an earlier node, so as to make a loop in the linked list.
 * 
 * EXAMPLE
 * input: A -> B -> C -> D -> E -> C [the same C as earlier]
 * output: C
 */

 /* Solution One - Place each entry into a set and check if the next
  * 			   entry is already available. If so, the that node is 
  * 			   the start of the loop 
  */ 
 	int solutionOne_2_5 (void) {
 		// First make circular
 		if (this->head == NULL || this->tail == NULL) throw string ("Exception: List is empty. Cannot make circular");
 		else {
 			// Just for simplicity - We'll link the tail to the next node of the head of the list
 			// This is temporary, after the value has been found, the linked list is reverted back.
 			this->tail->next = this->head->next;

 			// We assume that the list is circular
 			set<node *> mySet;
 			node * traveler = this->head;
 			while (traveler != NULL) {
 				if (mySet.find (traveler) != mySet.end ()) {
 					// Revert list back to normal
 					this->tail->next = NULL;
 					// Node of loop has been found. Return value.
 					return traveler->value;
 				}
 				mySet.insert (traveler);
 				traveler = traveler->next;
 			}
 		}
 	} 	
};

/* --------------------------------------------------------------------------
 * Question 2.4
 * --------------------------------------------------------------------------
 * You have two numbers represented by a linked list, where each node 
 * contains a single digit. The digits are stored in reverse order, such that 
 * the 1’s digit is at the head of the list. Write a function that adds the 
 * two numbers and returns the sum as a linked list.
 * 
 * EXAMPLE
 * Input: (3 -> 1 -> 5) + (5 -> 9 -> 2)
 * Output: 8 -> 0 -> 8
 */

/* Solution One - Keep track of total sum in 32-bit integer 
 *				- Not the best solution because this sum variable can 
 * 				  potentially overflow if the lists are too large
 */

list<int> * solutionOne_2_4 (list<int> listOne, list<int> listTwo) {
	int sumOne = 0, sumTwo = 0, totalSum = 0;
	int factor = 1;

	list<int> * summedList = new list<int> ();

	for (list<int>::iterator it = listOne.begin (); it != listOne.end (); it++) {
		sumOne += (*it) * factor;
		factor *= 10;
	}

	factor = 1;
	for (list<int>::iterator it = listTwo.begin (); it != listTwo.end (); it++) {
		sumTwo += (*it) * factor;
		factor *= 10;	
	}
	
	totalSum = sumOne + sumTwo;

	while (totalSum != 0) {
		int digit = totalSum % 10;
		totalSum /= 10;

		summedList->push_front (digit);
	}

	return summedList;
}

/* Solution Two - Sum both nodes and add to newly summed list on the fly.
 * 				- Prevents sum overflow and newly summed list can be as long as permitted by memory availability
 */

list<int> * solutionTwo_2_4 (list<int> listOne, list<int> listTwo) {
	list<int> * summedList = new list<int> ();

	list<int>::iterator it_one = listOne.begin ();
	list<int>::iterator it_two = listTwo.begin ();

	int sum = 0;

	if (listOne.size () == 0 && listTwo.size () == 0) return NULL;
	else {
		while (it_one != listOne.end () || it_two != listTwo.end ()) {
			if (it_one != listOne.end () && it_two != listTwo.end ()) {
				sum += *it_one + *it_two;
				it_one++;
				it_two++;
			} else if (it_one == listOne.end ()) {
				sum += *it_two;
				it_two++;
			} else {
				sum += *it_one;
				it_one++;
			}

			summedList->push_front (sum % 10);
			sum /= 10;
		}

		while (sum != 0) {
			summedList->push_front (sum % 10);
			sum /= 10;
		}
	}

	return summedList;
}


int main (void) {
	LinkedList * myList = new LinkedList ();

	myList->push_back (10);
	myList->push_back (20);
	myList->push_back (30);
	myList->push_back (40);
	myList->push_back (40);
	myList->push_back (40);
	myList->push_back (50);
	myList->push_back (50);
	myList->push_back (10);

	myList->push_front (100);

	/* Unit Test - 2.1 */
	myList->printList ();
	myList->solutionOne_2_1 ();
	myList->printList ();

	/* Unit Test - 2.3 */
	myList->solutionOne_2_3_caller ();
	myList->printList ();

	/* Unit Test - 2.4 */
	list<int> listOne;
	list<int> listTwo;
	// Creating list one
	listOne.push_back (4);
	listOne.push_back (2);
	listOne.push_back (3);
	// Creating list two
	listTwo.push_back (9);
	listTwo.push_back (0);
	listTwo.push_back (7);
	// Summing lists...
	list<int> * summedList = solutionTwo_2_4 (listOne, listTwo);
	// Printing summed list
	for (list<int>::iterator it = summedList->begin (); it != summedList->end (); it++)
		cout << *it << " ";
	cout << endl;

	/* Unit Test - 2.5 */
	LinkedList * list_2_5 = new LinkedList ();
	list_2_5->push_back (10);
	list_2_5->push_back (200);
	list_2_5->push_back (3);
	list_2_5->push_back (4);
	list_2_5->push_back (5);
	cout << "Start of Loop = " << list_2_5->solutionOne_2_5 () << endl;

	return 0;
}