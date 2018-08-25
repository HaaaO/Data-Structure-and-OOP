#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
* A templated class for a Node in a search tree. The getters for parent/left/right are virtual so that they
* can be overridden for future kinds of search trees, such as Red Black trees, Splay trees, and AVL trees.
*/
template <typename Key, typename Value>
class Node 
{
public:
	Node(const Key& key, const Value& value, Node<Key, Value>* parent);
	virtual ~Node();

	const std::pair<const Key, Value>& getItem() const;
	std::pair<const Key, Value>& getItem();
	const Key& getKey() const;
	const Value& getValue() const;
	Value& getValue();

	virtual Node<Key, Value>* getParent() const;
	virtual Node<Key, Value>* getLeft() const;
	virtual Node<Key, Value>* getRight() const;
	int getHeight() const;

	void setParent(Node<Key, Value>* parent);
	void setLeft(Node<Key, Value>* left);
	void setRight(Node<Key, Value>* right);
	void setValue(const Value &value);
	void setHeight(int height);

protected:
	std::pair<const Key, Value> mItem;
	Node<Key, Value>* mParent;
	Node<Key, Value>* mLeft;
	Node<Key, Value>* mRight;
	int mHeight;
};

/*
	-----------------------------------------
	Begin implementations for the Node class.
	-----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) 
	: mItem(key, value)
	, mParent(parent)
	, mLeft(NULL)
	, mRight(NULL)
	, mHeight(1)
{ 

} 

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed within the clear() helper method in the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node() 
{ 

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const 
{ 
	return mItem; 
}

/**
* A non-const getter for the item. 
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem() 
{ 
	return mItem; 
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const 
{ 
	return mItem.first; 
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const 
{ 
	return mItem.second; 
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
	return mItem.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const 
{ 
	return mParent; 
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const 
{ 
	return mLeft; 
}

/**
* An implementation of the virtual function for retreiving the right child. 
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const 
{ 
	return mRight; 
}

/**
* A const getter for the height.
*/
template<typename Key, typename Value>
int Node<Key, Value>::getHeight() const
{
	return mHeight;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent) 
{ 
	mParent = parent; 
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left) 
{ 
	mLeft = left; 
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right) 
{ 
	mRight = right; 
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value) 
{ 
	mItem.second = value; 
}

/**
* A setter for the height of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setHeight(int height) 
{ 
	mHeight = height;
}

/*
	---------------------------------------
	End implementations for the Node class.
	---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree 
{
	public:
		BinarySearchTree(); //TODO
		virtual ~BinarySearchTree(); //TODO
		int height(); //TODO 
		bool isBalanced(); //TODO 
		virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
		virtual void remove(const Key& key); //TODO
		void clear(); //TODO
		void print() const;

	public:
		/**
		* An internal iterator class for traversing the contents of the BST.
		*/
		class iterator 
		{
			public:
				iterator(Node<Key,Value>* ptr);
				iterator();

				std::pair<const Key, Value>& operator*();
				std::pair<const Key, Value>* operator->();

				bool operator==(const iterator& rhs) const;
				bool operator!=(const iterator& rhs) const;
				iterator& operator=(const iterator& rhs);

				iterator& operator++();

			protected:
				Node<Key, Value>* mCurrent;
		};

	public:
		iterator begin();
		iterator end();
		iterator find(const Key& key) const;

	protected:
		Node<Key, Value>* internalFind(const Key& key) const; //TODO
		Node<Key, Value>* getSmallestNode() const; //TODO
		void printRoot (Node<Key, Value>* root) const;

	protected:
		Node<Key, Value>* mRoot;
	private:
		void insert_helper(Node<Key,Value>* &node,const std::pair<const Key, Value>& pair);
		void update_height(Node<Key,Value>* &node);
		Node<Key, Value>* search(Node<Key,Value>* &node,const Key& key) const;
		Node<Key, Value>* get_rightmost(Node<Key,Value>* &node);
		void clear_helper(Node<Key, Value>* node);
		void remove_helper(Node<Key, Value>* node);
		bool isBalanced_helper(Node<Key, Value>* node);

};

/*
	---------------------------------------------------------------
	Begin implementations for the BinarySearchTree::iterator class.
	---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value>* ptr)
	: mCurrent(ptr)
{ 

}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::iterator::iterator()
	: mCurrent(NULL)
{ 

}

/**
* Provides access to the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& BinarySearchTree<Key, Value>::iterator::operator*() 
{ 
	return mCurrent->getItem();
}

/**
* Provides access to the address of the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>* BinarySearchTree<Key, Value>::iterator::operator->() 
{ 
	return &(mCurrent->getItem()); 
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator==(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent == rhs.mCurrent;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::iterator::operator!=(const BinarySearchTree<Key, Value>::iterator& rhs) const
{
	return this->mCurrent != rhs.mCurrent;
}

/**
* Sets one iterator equal to another iterator.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator &BinarySearchTree<Key, Value>::iterator::operator=(const BinarySearchTree<Key, Value>::iterator& rhs)
{
	this->mCurrent = rhs.mCurrent;
	return *this;
}

/**
* Advances the iterator's location using an in-order traversal.
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator& BinarySearchTree<Key, Value>::iterator::operator++()
{
	if(mCurrent->getRight() != NULL)
	{
		mCurrent = mCurrent->getRight();
		while(mCurrent->getLeft() != NULL)
		{
			mCurrent = mCurrent->getLeft();
		}
	}
	else if(mCurrent->getRight() == NULL)
	{
		Node<Key, Value>* parent = mCurrent->getParent();
		while(parent != NULL && mCurrent == parent->getRight())
		{
			mCurrent = parent;
			parent = parent->getParent();
		}
		mCurrent = parent;
	}
	return *this;
}

/*
	-------------------------------------------------------------
	End implementations for the BinarySearchTree::iterator class.
	-------------------------------------------------------------
*/

/*
	-----------------------------------------------------
	Begin implementations for the BinarySearchTree class.
	-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<typename Key, typename Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{ 
	mRoot = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree() 
{ 
	clear();
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{ 
	printRoot(mRoot);
	std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::begin()
{
	BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
	return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::end()
{
	BinarySearchTree<Key, Value>::iterator end(NULL);
	return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::iterator BinarySearchTree<Key, Value>::find(const Key& key) const 
{
	Node<Key, Value>* curr = internalFind(key);
	BinarySearchTree<Key, Value>::iterator it(curr);
	return it;
}

/**
* An method to return the height of the BST.
*/
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::height()
{
	if(mRoot != NULL){
		return mRoot->getHeight();
	}
	else{
		return 0;
	}
}



template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced_helper(Node<Key, Value>* node){
	int lhs;
	int rhs;
	if(node == NULL){
		return 1;
	}
	if(node->getLeft() !=NULL){
		lhs = node->getLeft()->getHeight();
	}
	else{
		lhs = 0;
	}

	if(node->getRight()!=NULL){
		rhs = node->getRight()->getHeight();
	}
	else{
		rhs = 0;
	}

	int result = lhs - rhs;

	if(result >= -1 && result <= 1 && isBalanced_helper(node->getLeft()) && isBalanced_helper(node->getRight())){
		return 1;
	}

	return 0;

}



/**
* An method to checks if the BST is balanced. This method returns true if and only if the BST is balanced.
*/
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced()
{
	return isBalanced_helper(mRoot);
}

/**
* An insert method to insert into a Binary Search Tree. The tree will not remain balanced when 
* inserting.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value>& keyValuePair)

{	

		

	if(mRoot == NULL){
		Node<Key,Value>* new_node = new Node<Key,Value>(keyValuePair.first,keyValuePair.second,NULL);
		mRoot = new_node;
	}
	else{
		insert_helper(mRoot,keyValuePair);
	}

	
	return;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::insert_helper(Node<Key,Value>* &node,const std::pair<const Key, Value>& pair){
	
	if(pair.first > node->getKey() && node->getRight() == NULL){
		Node<Key,Value>* new_node = new Node<Key,Value>(pair.first,pair.second,node);
		node->setRight(new_node);
		Node<Key,Value>* update_node = node->getRight();
		update_height(update_node);
		return;
	}

	if(pair.first < node->getKey() && node->getLeft() == NULL){
		Node<Key,Value>* new_node = new Node<Key,Value>(pair.first,pair.second,node);
		node->setLeft(new_node);
		Node<Key,Value>* update_node = node->getLeft();
		update_height(update_node);
		return;
	}

	if(pair.first > node->getKey()){
		Node<Key,Value>* pass_node = node->getRight();
		insert_helper(pass_node,pair);
	}

	if(pair.first < node->getKey()){
		Node<Key,Value>* pass_node = node->getLeft();
		insert_helper(pass_node,pair);
	}


}


template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::update_height(Node<Key,Value>* &node){
	int height_left = 1;
	int height_right = 1;

	while (node != NULL ){

		Node<Key,Value>* left = node->getLeft();

		Node<Key,Value>* right = node->getRight();


		if(left == NULL){
			height_left = 0;
		}
		else{
			height_left = left->getHeight();
		}

		if(right == NULL){
			height_right = 0;
		}
		else{
			height_right = right->getHeight();
		}
		
		if(height_right > height_left){
			node->setHeight(height_right+1);
		}
		else if (height_right <= height_left){
			node->setHeight(height_left+1);
		}
	
		node = node->getParent();
	}

}


template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::get_rightmost(Node<Key,Value>* &node){

	Node<Key, Value>* result;
	result = node;
	if(result == NULL){
		return result;
	}

	while(result->getRight() !=NULL){
		result = result->getRight();
	}
	return result;
}



template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove_helper(Node<Key, Value>* target){

	if(target == NULL)
	{
		return;
	}

	if(target->getHeight() == 1){
		Node<Key,Value>* parent_node = target->getParent();
		if(parent_node == NULL){
			delete target;
			mRoot = NULL;
			return;
		}

		if(parent_node->getRight() == target){
			parent_node->setRight(NULL);
			delete target;
			update_height(parent_node);
			return;
		}

		if (parent_node->getLeft() == target){
			parent_node->setLeft(NULL);
			delete target;
			update_height(parent_node);
			return;
		}
	}
	else if(target->getHeight() > 1){
		if(target->getLeft() == NULL || target->getRight() == NULL ){
			if(target->getLeft() != NULL){
				Node<Key,Value>* p_node = target->getParent();
				Node<Key,Value>* c_node = target->getLeft();
				if(p_node == NULL){
					mRoot = c_node;
					c_node->setParent(NULL);
					delete target;
					return;
				}

				if(p_node->getLeft() == target){
					p_node->setLeft(c_node);
					c_node->setParent(p_node);
					delete target;
					update_height(c_node);
					return;
				}
				else if (p_node->getRight() == target){
					p_node->setRight(c_node);
					c_node->setParent(p_node);
					delete target;
					update_height(c_node);
					return;

				}
			}
			else if (target->getRight() != NULL){
				Node<Key,Value>* p_node = target->getParent();
				Node<Key,Value>* c_node = target->getRight();
				if(p_node == NULL){
					mRoot = c_node;
					c_node->setParent(NULL);
					delete target;
					return;
				}
				if(p_node->getLeft() == target){
					p_node->setLeft(c_node);
					c_node->setParent(p_node);
					delete target;
					update_height(c_node);
					return;
				}
				else if (p_node->getRight() == target){
					p_node->setRight(c_node);
					c_node->setParent(p_node);
					delete target;
					update_height(c_node);
					return;
				}

			}

		}
		else if (target->getLeft() != NULL && target->getRight() != NULL){
			Node<Key,Value>* left_sub = target->getLeft();
			Node<Key,Value>* p_node = get_rightmost(left_sub);

			Node<Key,Value>* node = target;
			Node<Key, Value>* parent = node->getParent();
			Node<Key, Value>* left = node->getLeft();
			Node<Key, Value>* right = node->getRight();

			Node<Key, Value>* p_parent = p_node->getParent();
			Node<Key, Value>* p_left = p_node->getLeft();


			if(p_parent != node){
				if(node == mRoot){
					mRoot = p_node;
				}

				p_node->setParent(parent);
				if(parent !=NULL){
					if(parent->getLeft() == node){
						parent->setLeft(p_node);
					}
					else{
						parent->setRight(p_node);
					}
				}
				p_node->setLeft(left);
				left->setParent(p_node);
				p_node->setRight(right);
				right->setParent(p_node);
				p_parent->setRight(p_left);
				if(p_left!= NULL){
					p_left->setParent(p_parent);
				}
				delete node;
				update_height(p_parent);

			}
			else if(p_parent == node){
				if(node == mRoot){
					mRoot = p_node;
				}

				p_node->setParent(parent);
				if(parent !=NULL){
					if(parent->getLeft() == node){
						parent->setLeft(p_node);
					}
					else{
						parent->setRight(p_node);
					}
				}


				p_node->setRight(right);
				right->setParent(p_node);
				delete node;
				update_height(p_node);
			}
		}
	}	

}



/**
* An remove method to remove a specific key from a Binary Search Tree. The tree may not remain balanced after
* removal.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
	Node<Key, Value>* tar;
	tar = internalFind(key);
	remove_helper(tar);
}

/**
* A method to remove all contents of the tree and reset the values in the tree 
* for use again.
*/


template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear_helper(Node<Key, Value>* node){
	if(node == NULL){
		return;
	}
	clear_helper(node->getLeft());
	clear_helper(node->getRight());

	delete node;
}
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
	clear_helper(mRoot);
	mRoot = NULL;
}

/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::getSmallestNode() const
{
	Node<Key, Value>* result;
	result = mRoot;
	if(result == NULL){
		return result;
	}

	while(result->getLeft() !=NULL){
		result = result->getLeft();
	}
	return result;

}

template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::search(Node<Key,Value>* &node,const Key& key) const{
	if(node == NULL){
		return node;
	}

	if(node->getKey() == key){
		return node;
	}

	if(node->getKey() > key){
		Node<Key,Value>* pass_node = node->getLeft();
		return search(pass_node,key);
	}

	
		Node<Key,Value>* pass_node = node->getRight();
		return search(pass_node,key);
	
}

/**
* Helper function to find a node with given key, k and 
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const 
{
	Node<Key, Value>* result;
	Node<Key, Value>* start_node = mRoot;
	result = search(start_node,key);
	return result;
}

/**
* Helper function to print the tree's contents
*/

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::printRoot (Node<Key, Value>* root) const
{
	if (root != NULL)
	{
		std::cout << "[";
		printRoot (root->getLeft());
		std::cout << " (" << root->getKey() << ", " << root->getValue() << ") ";
		printRoot (root->getRight());
		std::cout << "]";
	}
}



/*
	---------------------------------------------------
	End implementations for the BinarySearchTree class.
	---------------------------------------------------
*/

#endif
