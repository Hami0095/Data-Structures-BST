#include<iostream>
using namespace std;


template<class T>
class Tree {
	struct Node {
		int data;
		Node* lchild;
		Node* rchild;
		Node* parent;

		Node() {
			data = 0;
			lchild = rchild = parent = nullptr;
		}
		Node(int o, Node* a = nullptr, Node* b = nullptr) {
			data = o;
			lchild = a;
			rchild = b;

		}
		Node(const Node& n) {
			data = n.obj;
			lchild = n.lchild;
			rchild = n.rchild;
			parent = n.parent;
		}
	};
	Node* root;
	
	
	// Helper Functions : 

	
	Node* insert(Node* node, T val) {
		if (root == nullptr) {
			node = new Node(val);
			root = node;
		}
		if (node == nullptr) {
			node = new Node(val);
		}
		else if (node->data < val) {
			node->rchild = insert(node->rchild, val);
			node->rchild->parent = node->rchild;
			
		}
		else if (node->data > val) {
			node->lchild = insert(node->lchild, val);
			node->lchild->parent = node->lchild;
			
		}
		return node;
	}

	Node* search(Node* node, T val) {
		if (node == NULL)
			return NULL;
		
		else if (node->data == val)
			return node;

		else if (node->data < val)
			return search(node->rchild, val);
		
		else
			return search(node->lchild, val);
	}

	bool search(int key)
	{
		// Invoking Search() operation
		// and passing root node
		Node* res = search(root, key);
		// If key is found, returns TRUE
		// otherwise returns FALSE
		return res == NULL ? false : true;
	}

	bool isValPresent(T val) {
		Node* curr = root;
		while (curr != nullptr) {
			if (curr->data == val) {
				return true;
			}
			else if (curr->data < val) {
				curr = curr->rchild;
			}
			else if (curr->data > val) {
				curr = curr->lchild;
			}
		}
		return false;
	}
	// this function helps us to know k val parri hui ha ya nai and plus hmary parent main leaf node jo best ha us 
	// val k lye wo rkh de gaa

	bool getAccess(T val, Node*& par) {

		par = nullptr;
		Node* curr = root;
		while (curr != nullptr) {
			par = curr;
			if (val == curr->data) {
				return true;
			}
			else if (val < curr->data)
				curr = curr->lchild;
			else if (val > curr->data)
				curr = curr->rchild;
		}

		return false;
	}

	void _printInOrder(Node* curr) {
		if (curr != nullptr) {
			//LNR
			_printInOrder(curr->lchild);
			cout << (curr->data) << " ";
			_printInOrder(curr->rchild);
		}
	}

	bool isTreeEmpty() {
		return (root == nullptr) ? 1 : 0;
	}

	int findMin(Node* node) 
	{
		if (node == nullptr)
			return -1;
		else if (node->lchild == nullptr)
			return node->data;
		else
			return findMin(node->lchild);
	}
	int findMax(Node* node)
	{
		if (node == nullptr)
			return -1;
		else if (node->rchild == nullptr)
			return node->data;
		else
			return findMax(node->rchild);
	}


	// successor : algo :
	//case 1: 
	//	if node has rchild, then minimum of the rchild is the successor of the node
	//case 2:
	//	if node->data is the maximum data in the bst, then no successor
	//case 3:
	//	if node has no rchild, then the node whose lchild is the parent of the curr node, is the successor

	T successor(Node* node) {
		if (node->rchild != nullptr) {
			return findMin(node->rchild);
		}
		else if (node->data == findMax()) {
			return node->data;
		}
		else {
			Node* par = node->parent;
			Node* curr = node;
			// keep moving up : 
			while ((node->parent != nullptr)
				&& (curr == par->rchild))
			{
				curr = par;
				par = curr->parent;
			}

			return par == nullptr ? 1 : par->data;
		}
	}

	//predecssor : algo :
	//case 1:
	//	if node has left child, then the max of the node->lchild is the predecssor
	//case 2:
	//	if move to the parents and the first value less than node->data, is the predecssor;
	//case 3:
	//	if node->data is the minimum, then it has no predecssor;

	T predecessor(Node* node) {
		if (node->lchild != nullptr) {  // case 1
			return findMax(node->lchild);
		}
		else if (node->data == findMin()) {  // case 3
			return node->data;
		}
		else {	// case 2
			Node* par = node->parent;
			Node* curr = node;
			// If currentNode is not root and
			// currentNode is its left children
			// continue moving up

			while ((par != NULL) &&
				(curr == par->lchild))
			{
				curr = par;
				par = curr->parent;
			}

			// If parentNode is not NULL
			// then the key of parentNode is
			// the predecessor of node
			return par == NULL ? -1 : par->data;
		}
	}

	// remove : algo :
	//case 1:
	//	if the node to remove is the leaf node, then just simply remove it
	//case 2:
	//	if the node has one child (either l || r), we have to connect the child with the node->par, and remove 
	//		node
	//case 3:
	//	if the node has two children, then replace the node with it's predecessor or successor.

	Node* remove(Node* node, T val) {

		if (node == nullptr) {
			return nullptr;
		}
		if (node->data == val) {
			if (node->lchild == nullptr && node->rchild == nullptr) {
				node = nullptr;
			}
			else if (node->lchild == nullptr && node->rchild != nullptr) {
				node->rchild->parent = node->parent;
				node = node->rchild;
			}
			else if (node->rchild == nullptr && node->lchild != nullptr) {
				node->lchild->parent = node->parent;
				node = node->lchild;
			}

			else { // two children :1
				T successorVal = successor(val);
				// Replace node's key with successor's key
				node->data = successorVal;

				// Delete the old successor's key
				node->rchild = remove(node->rchild, successorVal);

			}
		}
		// The node's data is smaller than
		// the given data then search to right
		else if (node->data < val)
			node->rchild = remove(node->rchild, val);
		// Target node's key is greater than
		// the given key then search to left
		else
		node->lchild = remove(node->lchild, val);

		
		return node;

	}

	T findHeight(Node* node) {
		if (node == nullptr) {
			return 0;
		}
		else {
			T l = findHeight(node->lchild);
			T r = findHeight(node->rchild);
			return max(l, r) + 1;
		}
	}

	T findDepth(Node* node) {
		if (node == nullptr) {
			return 0;
		}
		else {
			T l = findDepth(node->lchild);
			T r = findDepth(node->rchild);
			return max(l, r) + 1;
		}
	}
	
	

	/* Returns true if binary tree
with root as root is height-balanced */
	bool isBalanced(Node* root) {
		int lh; /* for height of left subtree */
		int rh; /* for height of right subtree */

		/* If tree is empty then return true */
		if (root == NULL)
			return 1;

		/* Get the height of left and right sub trees */
		lh = findHeight(root->lchild);
		rh = findHeight(root->rchild);

		if (abs(lh - rh) <= 1 && isBalanced(root->lchild) && isBalanced(root->rchild))
			return 1;

		/* If we reach here then
		tree is not height-balanced */
		return 0;
	}

	void insertSortedArray(T sortedArray[], int source, int destination) {
		if (source > destination) return;

		if (source == destination) {
			this->insert(sortedArray[source]);
			return;
		}
		int mid = (source + destination) / 2;
		insertSortedArray(sortedArray, source, mid);
		insertSortedArray(sortedArray, mid + 1, destination);
	}

	int getMaxWidth(Node* root)
	{
		int maxWidth = 0;
		int width;
		int h = findHeight(root);

		/* Get width of each level and compare
			the width with maximum width so far */
		for (int i = 1; i <= h; i++) {
			width = getWidth(root, i);
			if (width > maxWidth)
				maxWidth = width;
		}

		return maxWidth;
	}

	int getWidth(Node* root, int level)
	{

		if (root == NULL)
			return 0;

		if (level == 1)
			return 1;

		else if (level > 1)
			return getWidth(root->lchild, level - 1) + getWidth(root->rchild, level - 1);
	}

	bool compare_helper(Node* node, Node* node1)
	{
		if (node1 == nullptr) return true;

		if (node == nullptr && node1 != nullptr) return false;


		if (node->data != node1->data) return false;

		bool leftSubtree = compare_helper(node->lchild,   node1->lchild);
		bool righttSubtree = compare_helper(node->rchild, node1->rchild);

		return (leftSubtree && righttSubtree);
	}

	
	
public:
	
	Tree() {
		root = nullptr;
	}

	Tree(T sortedData[], int size) {			
	
		root = NULL;

		insertSortedArray(sortedData, 0, size - 1);
	
	}

	T findMin() {
		return findMin(root);
	}

	T findMax() {
		return findMax(root);
	}

	void insert(T val) {
		root = insert(root, val);
		
	}

	T successor(T val) {		
		
		Node* node = search(root, val);
		
		return node == nullptr ? -1 : successor(node);
	}

	T predecessor(T val) {
		Node* node = search(root, val);

		return node == nullptr ? -1 : predecessor(node);
	}
	
	void remove(T val) {
		root = remove(root, val);
	}

	void printInOrder() {
		_printInOrder(root);
	}

	T findHeight(T val) {
		if (isValPresent(val) == false) {
			return -1;
		}
		Node* node = search(root,val);

		return findHeight(node);

	}

	T findDepth(T val) {
		if (isValPresent(val) == false) {
			return -1;
		}
		Node* node = search(root, val);

		return findDepth(node);

	}

	bool isBalanced() {
		return isBalanced(root);
	}
	
	bool isBalanced(T val) {
		Node* node = search(root, val);
		return isBalanced(node);
	}

	int getWidth(T val) {
		Node* node = search(root, val);
		return getMaxWidth(node);
	}

	int getWidth() {
		return getMaxWidth(root);
	}
	
	void Daalo(T val) {
		if (root == nullptr) {
			root = new Node(val);
			return;
		}
		Node* curr = root;
		while (curr != nullptr)
		{
			if (val < curr->data) {
				curr->parent = curr;
				curr = curr->lchild;
			}
			else {
				curr->parent = curr;
				curr = curr->rchild;
			}
				
		}
		curr = new Node(val);		
	}

	
	
	bool operator==(Tree & obj)
	{
		Node* temp = this->root;
		Node* temp1 = obj.root;

		return (compare_helper(temp, temp1));
	}

	bool isSubTree(Tree& obj) {
		if (!isValPresent(obj.root->data))
			return false;
		Node* curr = root;
		
		while (curr != nullptr) {
			if (compare_helper(curr, obj.root) 
				|| compare_helper(curr->lchild, obj.root) 
				|| compare_helper(curr->lchild, obj.root))
				return true;
			if (obj.root->data < curr->data) {
				curr = curr.lchild;
			}
			else {
				curr = curr->rchild;
			}
		}

	}

	Tree& addPreorderly(Node* node, Node* oNode) {
		Tree bst;
		if (node == nullptr && oNode == nullptr) {
			return;
		}
		if (node != nullptr && oNode != nullptr) {
			bst.insert(node->data + oNode->data);
			addPreorderly(node->lchild, oNode->lchild);
			addPreorderly(node->rchild, oNode->rchild);
		}
		if (node == nullptr && oNode != nullptr) {
			bst.insert(oNode->data);
			addPreorderly(nullptr, oNode->lchild);
			addPreorderly(nullptr, oNode->rchild);
		}
		if (node != nullptr && oNode == nullptr) {
			bst.insert(node->data);
			addPreorderly(node->lchild, nullptr);
			addPreorderly(node->rchild, nullptr);
		}
		return bst;
	}

	Tree operator+(Tree& bst) {
		return addPreorderly(root, bst->root);
	}

};
