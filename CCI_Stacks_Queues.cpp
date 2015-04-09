#include <iostream>
#include <cassert>
#include <vector>
#include <stack>

using namespace std;

class Stack {
private:
	typedef struct _node_ {
		int value;
		_node_ * next;
	} node;

	node * top;
	vector<int> * minStack;

	node * createNode (int value) {
		try {
			node * newNode = new node;
			newNode->value = value;
			newNode->next = NULL;

			return newNode;
		} catch (bad_alloc & e) {
			cout << "Exception: Stack cannot create node. No more memory" << endl;
		}
	}

	int pushMin (int value) {
		if (this->minStack->empty () == true)
			this->minStack->push_back (value);
		else {
			if (value < this->minStack->back ())
				this->minStack->push_back (value);
		}

		return this->minStack->back ();
	}

	int popMin (int value) {
		if (value == this->minStack->back ())
			this->minStack->pop_back ();

		return this->minStack->back ();
	}

public:
	Stack () {
		this->top = NULL;
		try {
			this->minStack = new vector<int>;	
		} catch (bad_alloc & e) {
			cout << "Exception: Cannot create vector. Not enough memory" << endl;
		}
		
	}

	void push (int value) {
		if (this->top == NULL) {
			this->top = this->createNode (value);
		} else {
			node * newNode = this->createNode (value);
			newNode->next = this->top;
			this->top = newNode;
		}

		this->pushMin (value);
	}

	void pop (void) {
		if (this->top != NULL) {
			node * temp = this->top;
			this->top = this->top->next;
			int popValue = temp->value;
			delete temp;

			this->popMin (popValue);
		}
	}

	int peek (void) {
		if (this->top == NULL) throw string ("Exception: Cannot peek. Stack is empty");
		else {
			return this->top->value;
		}
	}

	void printStack (void) {
		node * traveler = this->top;
		while (traveler != NULL) {
			cout << traveler->value << " ";
			traveler = traveler->next;
		}
		cout << endl;
	}

/* --------------------------------------------------------------------------
 * Question 3.2
 * --------------------------------------------------------------------------
 * How would you design a stack which, in addition to push and pop, also has 
 * a function min which returns the minimum element? Push, pop and min should 
 * all operate in O(1) time.
 */

 /* Solution One - Use a vector to keep track of new values as they come
  * 			   through onto the stack. If a new value is < the current
  * 			   min, then minStack with the new value as the new min.
  * 			   Otherwise don't do anything.
  * 			 - If a value is taken off the stack, the popped value
  * 			   is compared with the current min. If the value == current
  * 			   min then pop the value from minStack, if > then current
  * 			   min then don't do anything. 
  */
	int min (void) {
		if (this->minStack->empty ()) throw string ("Exception: Cannot get min value from stack. Stack does not exist");
		else {
			return this->minStack->back ();
		}	
	}
};

class Queue {
private:
	typedef struct _node_ {
		int value;
		_node_ * next;
	} node;

	node * top;
	node * tail;

	node * createNode (int value) {
		try {
			node * newNode = new node;
			newNode->value = value;
			newNode->next = NULL;

			return newNode;
		} catch (bad_alloc & e) {
			cout << "Exception: Queue cannot create node. No more memory left!" << endl;
		}
	}


public:

	Queue () {
		this->top = NULL;
		this->tail = NULL;
	}

	void push (int value) {
		if (this->top == NULL && this->tail == NULL) {
			this->top = this->tail = this->createNode (value);
		} else {
			this->tail->next = this->createNode (value);
			this->tail = this->tail->next;
		}
	}

	void pop (void) {
		if (this->top == NULL || this->tail == NULL) return;
		else {
			node * temp = this->top;
			this->top = this->top->next;
			delete temp;
		}
	}

	int peek (void) {
		if (this->top == NULL || this->tail == NULL) throw string ("Exception: Cannot peek. Queue is empty!");
		else {
			return this->top->value;
		}
	}

	void printQueue (void) {
		node * traveler = this->top;
		while (traveler != NULL) {
			cout << traveler->value << " ";
			traveler = traveler->next;
		}
		cout << endl;
	}

};

/* --------------------------------------------------------------------------
 * Question 3.3
 * --------------------------------------------------------------------------
 * Imagine a (literal) stack of plates. If the stack gets too high, it might 
 * topple. Therefore, in real life, we would likely start a new stack when the 
 * previous stack exceeds some threshold. Implement a data structure SetOfStacks 
 * that mimics this. SetOfStacks should be composed of several stacks, and should 
 * create a new stack once the previous one exceeds capacity. SetOfStacks.push() 
 * and SetOfStacks.pop() should behave identically to a single stack 
 * (that is, pop() should return the same values as it would if there were just a single stack).
 * 
 * FOLLOW UP
 * Implement a function popAt(int index) which performs a pop operation on a specific sub-stack.
 */

 /* Solution One - Keep track of each stack within a base stack. Push and pop functions
  *				   will operate in the same fashion but also takes into account what is the
  * 			   current stack in use.
  */

 class SetOfStacks {
 private:
 	int threshold;
 	int totalItems;
 	int stackCount;
 	stack<stack<int> *> * baseStack;

 public:
 	SetOfStacks (int k) {
 		try {
 			if (k <= 0) throw string ("Exception: Threshold must be greater than zero");
 			this->threshold = k;
 			this->totalItems = 0;
 			this->stackCount = 0;
 			this->baseStack = new stack<stack<int> *> ();
 		} catch (bad_alloc & e) {
 			cout << "Exception: Cannot create base stack. Not enough memory" << endl;
 		}
 	}

 	void push (int value) {
 		int pos = (this->totalItems) % this->threshold;

 		if (pos == 0)
 			this->baseStack->push (new stack<int>);

		stack<int> * currentStack = this->baseStack->top ();
 		currentStack->push (value);
 		this->totalItems++;
 	}

 	void pop (void) {
 		if (this->baseStack->empty() == true) throw string ("Exception: Cannot pop. Stack is empty");
 		else {
 			stack<int> * currentStack = this->baseStack->top ();
 			if (currentStack->empty() == false) currentStack->pop ();
 			if (this->baseStack->top()->empty() == true) this->baseStack->pop();
 		}
 	}

 	int peek (void) {
 		if (this->baseStack->top()->empty()) throw string ("Exception: Cannot peek. Stack is empty!");
 		else {
 			return this->baseStack->top()->top();
 		}
 	}
 };

/* --------------------------------------------------------------------------
 * Question 3.4
 * --------------------------------------------------------------------------
 * In the classic problem of the Towers of Hanoi, you have 3 rods and N disks 
 * of different sizes which can slide onto any tower. The puzzle starts with 
 * disks sorted in ascending order of size from top to bottom (e.g., each disk 
 * sits on top of an even larger one). You have the following constraints:
 * 
 * (A) Only one disk can be moved at a time.
 * (B) A disk is slid off the top of one rod onto the next rod.
 * (C) A disk can only be placed on top of a larger disk.
 *
 * Write a program to move the disks from the first rod to the last using Stacks.
 */

 /* Solution One - Keep track of each stack within a base stack. Push and pop functions
  *				   will operate in the same fashion but also takes into account what is the
  * 			   current stack in use.
  */


/* --------------------------------------------------------------------------
 * Question 3.5
 * --------------------------------------------------------------------------
 * Implement a MyQueue class which implements a queue using two stacks.
 */

 /* Solution One - Keep track of two seperate stacks - Stack One / Stack Two.
  *				 - If a pop action is performed then check if stack two is empty,
  *				   if it is, then pop all values from stack one into stack two. 
  * 			 - Similar action for peek. 
  *			   	 - Push action simply pushes an item into stack one.
  * 			 - Stack one buffers up all the pushed values. 
  */

class MyQueue {
private:
	stack<int> stackOne;
	stack<int> stackTwo;

public:
	void push (int value) {
		this->stackOne.push (value);
	}

	void pop (void) {
		if (this->stackOne.empty () == true && this->stackTwo.empty () == true) throw string ("Exception: Cannot pop. Queue is empty!");
		else {
			if (this->stackTwo.empty () == true) {
				while (this->stackOne.empty () == false) {
					this->stackTwo.push (this->stackOne.top());
					this->stackOne.pop ();
				}
			}
			this->stackTwo.pop ();
		}
	}

	int peek (void) {
		if (this->stackOne.empty () == true && this->stackTwo.empty () == true) throw string ("Exception: Cannot peek. Queue is empty!");
		else {
			if (this->stackTwo.empty () == true) {
				while (this->stackOne.empty () == false) {
					this->stackTwo.push (this->stackOne.top ());
					this->stackOne.pop ();
				}
			}
			return this->stackTwo.top ();			
		}
	}
};

/* --------------------------------------------------------------------------
 * Question 3.6
 * --------------------------------------------------------------------------
 * Write a program to sort a stack in ascending order. You should not make 
 * any assumptions about how the stack is implemented. The following are the 
 * only functions that should be used to write this program: push | pop | top | empty.
 */

 /* Solution One - Create a seperate stack and use this as a means of storing the
  *				   items in ascending order. A comparison is made between the current
  *				   stack value and the current temp stack value. 
  * 			   If the current < temp current, then push the temp stack values
  * 			   greater back into the orginal stack such that the smaller value and
  * 			   be pushed onto the temp stack. Repeat process until the orginal stack is
  * 			   empty. When empty, push all items from temp onto the original stack.
  */

 void solutionOne_3_6 (stack<int> & stk) {
 	stack<int> tempStack;

 	while (stk.empty () == false) {
 		int value = stk.top ();
 		stk.pop ();

 		if (tempStack.empty () == true)
 			tempStack.push (value);
 		else {
 			while (tempStack.empty () == false && value < tempStack.top ()) {
 				stk.push (tempStack.top ());
 				tempStack.pop ();
 			}
 			tempStack.push (value);
 		}
 	}

 	while (tempStack.empty () == false) {
 		stk.push (tempStack.top ());
 		tempStack.pop ();
 	}
 }

int main (void) {

	// STACK
	Stack * stk = new Stack ();
	stk->push (10);
	stk->push (5);
	stk->push (20);
	stk->push (30);
	stk->push (40);
	stk->push (50);
	stk->push (1);
	
	stk->printStack ();
	stk->pop ();
	stk->printStack ();

	/* Unit Test - 3.2 */
	assert (stk->min () == 5);

	/* Unit Test - 3.3 */
	int threshold = 4;
	SetOfStacks * sos = new SetOfStacks (threshold);
	sos->push (10);
	sos->push (20);
	sos->push (30);
	sos->push (40);
	
	sos->pop ();

	cout << sos->peek () << endl;

	// QUEUE
	Queue * q = new Queue ();
	q->push (100);
	q->push (200);
	q->push (300);
	q->push (400);
	q->push (500);

	q->printQueue ();
	q->pop ();
	q->printQueue ();

	/* Unit Test - 3.5 */
	MyQueue * mq = new MyQueue ();
	mq->push (10);
	mq->push (20);
	mq->push (30);
	mq->push (40);
	mq->push (50);
	mq->peek ();
	cout << "MyQueue Top Value = " << mq->peek () << endl;

	/* Unit Test - 3.6 */
	stack<int> stk_3_6;
	stk_3_6.push (4);
	stk_3_6.push (2);
	stk_3_6.push (1);
	stk_3_6.push (3);

	solutionOne_3_6 (stk_3_6);
	cout << "Soln 3.6 Top value = " << stk_3_6.top () << endl;
	stk_3_6.pop ();
	cout << "Soln 3.6 Top value = " << stk_3_6.top () << endl;


	return 0;
}