#include <iostream>
#include <queue>
#include <cassert>

using namespace std;

class BST {
private:
	typedef struct _node_ {
		int value;
		_node_ * left;
		_node_ * right;
	} node;

	node * root;

	node * createNode (int value) {
		try {
			node * newNode = new node;
			newNode->value = value;
			newNode->left = NULL;
			newNode->right = NULL;

			return newNode;
		} catch (bad_alloc & e) {
			cout << "Exception: Cannot create node. Not enough memory" << endl;
		}
	}

	int maxDepth (node * myNode) {
		if (myNode == NULL) return 0;
		else {
			int leftHeight = this->maxDepth (myNode->left);
			int rightHeight = this->maxDepth (myNode->right);

			if (leftHeight < rightHeight)
				return 1 + rightHeight;
			else 
				return 1 + leftHeight;
		}
	}

	int minDepth (node * myNode) {
		if (myNode == NULL) return 0;
		else {
			int leftHeight = this->minDepth (myNode->left);
			int rightHeight = this->minDepth (myNode->right);

			if (leftHeight < rightHeight)
				return 1 + leftHeight;
			else
				return 1 + rightHeight;
		}
	}

/* --------------------------------------------------------------------------
 * Question 4.4
 * --------------------------------------------------------------------------
 * Given a binary search tree, design an algorithm which creates a linked list 
 * of all the nodes at each depth (i.e., if you have a tree with depth D, you’ll 
 * have D linked lists).
 */

 /* Solution One - Create a queue of queues.		   
  */

  	void solutionOne_4_4 (node * myNode) {
  		if (myNode == NULL) throw string ("Exception: Cannot execute solutionOne_4_3. Tree is empty!");
  		else {
	  		queue<queue<node *> *> q;

  			queue<node *> * row = new queue<node *> ();
  			row->push (myNode);  			

  			q.push (row);

  			while (q.empty () == false && q.front()->empty() == false) {
  				queue<node *> * current = q.front ();
  				q.pop ();

  				queue<node *> * newQ = new queue<node *> ();
  				while (current->empty () == false) {
  					node * item = current->front ();
  					current->pop ();

  					cout << item->value << " ";
  					if (item->left != NULL) newQ->push (item->left);
  					if (item->right != NULL) newQ->push (item->right);
  				}
  				q.push (newQ);
  				cout << endl;
  			}
  		}
  	}	

public:
	BST () {
		this->root = NULL;
	}

	void insert (int value) {
		if (this->root == NULL) {
			this->root = this->createNode (value);
		} else {
			node ** traveler = &this->root;
			while (*traveler != NULL) {
				if (value < (*traveler)->value)
					traveler = &(*traveler)->left;
				else if (value > (*traveler)->value)
					traveler = &(*traveler)->right;
				else if (value == (*traveler)->value) 
					throw string ("Exception: BST already contains value. Cannot insert!");
			}

			*traveler = this->createNode (value);
		}
	}

	void erase (int value) {

	}

	bool search (int value) {
		if (this->root == NULL) throw string ("Exception: Cannot search for value. Tree is empty!");
		else {
			node * traveler = this->root;
			while (traveler != NULL) {
				if (value == traveler->value) return true;
				else if (value < traveler->value)
					traveler = traveler->left;
				else 
					traveler = traveler->right;
			}
			return false;
		}
	}

	void printTree_BFS (void) {
		queue<node *> * q = new queue<node *> ();

		if (this->root != NULL) {
			q->push (this->root);

			while (q->empty () == false) {
				node * current = q->front ();
				q->pop ();

				cout << current->value << " ";

				if (current->left != NULL) q->push (current->left);
				if (current->right != NULL) q->push (current->right);
			}
			cout << endl;
		}
	}

	void printTree_DFS (void) {

	}

	int getMaxDepth (void) {
		return this->maxDepth (this->root);
	}

	int getMinDepth (void) {
		return this->minDepth (this->root);
	}

/* --------------------------------------------------------------------------
 * Question 4.1
 * --------------------------------------------------------------------------
 * Implement a function to check if a tree is balanced. For the purposes of 
 * this question, a balanced tree is defined to be a tree such that no two leaf 
 * nodes differ in distance from the root by more than one.
 */

 /* Solution One - Find diff between max / min depth. If diff is greather than one
  * 			   then tree is balanced. 
  */

 	bool isBalanced (void) {
 		if (this->root == NULL) throw string ("Exception: Cannot check balance. Tree is empty!");
 		else {
 			int min = this->getMinDepth ();
 			int max = this->getMaxDepth ();

 			if (max - min <= 1) return true;
 			else return false;
 		}
 	}

 	void solutionOne_4_4_caller (void) {
 		this->solutionOne_4_4 (this->root);
 	}

};

/* --------------------------------------------------------------------------
 * Question 4.3
 * --------------------------------------------------------------------------
 * Given a sorted (increasing order) array, write an algorithm to create a 
 * binary tree with minimal height.
 */

 /* Solution One - 
  */

 void solutionOne_4_3 (vector<int> & vec, BST & tree, int left, int right) {
 	if (left <= right) {
 		int mid = (left + right) / 2;
 		tree.insert (vec[mid]);
 		solutionOne_4_3 (vec, tree, left, mid - 1);
 		solutionOne_4_3 (vec, tree, mid + 1, right);
 	}
 }

int main (void) {

	BST * tree = new BST ();
	tree->insert (10);
	tree->insert (5);
	tree->insert (15);
	tree->insert (1);
	tree->insert (20);
	tree->insert (7);
	tree->insert (12);
	tree->insert (9);
	tree->insert (25);

	tree->printTree_BFS ();

	assert (tree->search (12) == true);

	cout << "Max Depth = " << tree->getMaxDepth () << endl;
	cout << "Min Depth = " << tree->getMinDepth () << endl;

	/* Unit Test - 4.1 */
	assert (tree->isBalanced () == true);

	/* Unit Test - 4.3 */
	BST tree_4_3;
	int array [] = {2, 4, 6, 8, 10, 12, 14, 16, 18};
	vector<int> vec (array, array + sizeof (array) / sizeof (array[0]));
	solutionOne_4_3 (vec, tree_4_3, 0, vec.size () - 1);
	tree_4_3.printTree_BFS ();

	/* Unit Test - 4.4 */
	BST tree_4_4 = tree_4_3;
	tree_4_4.solutionOne_4_4_caller ();


	return 0;
}