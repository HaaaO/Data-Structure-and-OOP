#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include "rotateBST.h"


template<typename Key, typename Value>
class SplayTree : public rotateBST<Key, Value>
{
public:
	SplayTree();
	void insert(const std::pair<const Key, Value>& keyValuePair);
	void remove(const Key& key);
	typename SplayTree<Key, Value>::iterator find(const Key& key);
	typename SplayTree<Key, Value>::iterator findMin();
	typename SplayTree<Key, Value>::iterator findMax();
	void deleteMinLeaf();
	void deleteMaxLeaf();




protected:
	void splay(Node<Key, Value> *r);

private: 
	Node<Key, Value>* last_visit( Node<Key, Value> * node,Node<Key, Value> * p_node,const Key& key);
	Node<Key, Value>* findMin_helper( Node<Key, Value> * node,Node<Key, Value> * p_node);
	Node<Key, Value>* findMax_helper( Node<Key, Value> * node,Node<Key, Value> * p_node);
	Node<Key, Value>* get_pred(Node<Key,Value>* &node);
	Node<Key,Value>* deleteMinLeaf_helper(Node<Key, Value> * root);
	Node<Key, Value>* deleteMaxLeaf_helper(Node<Key, Value>* root);
	void splay_helper(Node<Key, Value> *r);

	
};

template<typename Key, typename Value>
SplayTree<Key, Value>::SplayTree(){


}

template<typename Key, typename Value>
void SplayTree<Key, Value>::splay(Node<Key, Value> *r){
	while (r != this->mRoot){
		splay_helper(r);
	}
}


template<typename Key, typename Value>
void SplayTree<Key, Value>::splay_helper(Node<Key, Value> *r){
	if(r == this->mRoot){
		return;
	}
	else{
		Node<Key, Value> * parent = r->getParent();
		Node<Key, Value> * grandparent;
		if(parent == this->mRoot){
			if(parent->getLeft() == r){
				rotateBST<Key,Value>::rightRotate(parent);
			
			}
			else{
				rotateBST<Key,Value>::leftRotate(parent);

			}
		}
		else{
			grandparent = parent->getParent();
			if(grandparent->getLeft() == parent){
				if(parent->getLeft()== r){
					rotateBST<Key,Value>::rightRotate(grandparent);

					rotateBST<Key,Value>::rightRotate(parent);
	
				}
				else{
					rotateBST<Key,Value>::leftRotate(parent);
	
					rotateBST<Key,Value>::rightRotate(grandparent);
			
				}
			}
			else{
				if(parent->getRight() == r){
					rotateBST<Key,Value>::leftRotate(grandparent);

					rotateBST<Key,Value>::leftRotate(parent);

				}
				else{
					rotateBST<Key,Value>::rightRotate(parent);

					rotateBST<Key,Value>::leftRotate(grandparent);

				}
			}
		}
	}
}

template<typename Key, typename Value>
void SplayTree<Key, Value>::insert(const std::pair<const Key, Value>& keyValuePair){
	BinarySearchTree<Key, Value>::insert(keyValuePair);

	Node<Key, Value>* new_node = BinarySearchTree<Key, Value>::internalFind(keyValuePair.first);
	splay(new_node);

	
}

template<typename Key, typename Value>
Node<Key, Value>* SplayTree<Key, Value>::get_pred(Node<Key,Value>* &node){

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
void SplayTree<Key, Value>::remove(const Key& key){
	Node<Key, Value>* node = BinarySearchTree<Key, Value>::internalFind(key);

	if(node == NULL){
		Node<Key, Value>* root = this->mRoot;
		if(root != NULL){
			Node<Key, Value>* p_root = root->getParent();
			Node<Key, Value>* result_root = last_visit(root, p_root, key);
			splay(result_root);
	

		}	

	}
	else{

		if(node->getLeft() == NULL || node->getRight() == NULL){
			Node<Key, Value>* splay_node = node->getParent();
			if(splay_node == NULL){
				BinarySearchTree<Key, Value>::remove(key);
			}
			else{
				BinarySearchTree<Key, Value>::remove(key);
				splay(splay_node);	
	
			}

		}
		else{
			Node<Key, Value>* splay_node;
			Node<Key,Value>* left_sub = node->getLeft();
			Node<Key,Value>* p_node = get_pred(left_sub);
			
			if(p_node->getParent() == node){
				splay_node = p_node;
			}
			else{
				splay_node = p_node->getParent();
			}
			BinarySearchTree<Key, Value>::remove(key);
			splay(splay_node);		
			

		}


	}

}

template<typename Key, typename Value>
Node<Key, Value>* SplayTree<Key, Value>::last_visit( Node<Key, Value> * node,Node<Key, Value> * p_node,const Key& key){
	if(node == NULL){
		return p_node;
	}

	if(node->getKey() == key){
		return node;
	}

	if(node->getKey() > key){
		Node<Key,Value>* pass_node = node->getLeft();
		return last_visit(pass_node,node,key);
	}

	
	Node<Key,Value>* pass_node = node->getRight();
	return last_visit(pass_node,node,key);


}




template<typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::find(const Key& key){
	Node<Key, Value>* root = this->mRoot;

	if(root == NULL)
	{	
		return BinarySearchTree<Key, Value>::end();
	}
	else{
		Node<Key, Value>* new_node = BinarySearchTree<Key, Value>::internalFind(key);

		if(new_node!=NULL){
		
			splay(new_node);
			     
		

			typename BinarySearchTree<Key, Value>::iterator it(new_node);

			return it;
		}
		else{
			Node<Key, Value>* p_root = root->getParent();
			Node<Key, Value>* result_root = last_visit(root, p_root, key);
			
			
			splay(result_root);
			     

			return BinarySearchTree<Key, Value>::end();
		}
	}
}


template<typename Key, typename Value>
Node<Key, Value>* SplayTree<Key, Value>::findMin_helper( Node<Key, Value> * node,Node<Key, Value> * p_node){
	if(node == NULL){
		return p_node;
	}

	Node<Key,Value>* pass_node = node->getLeft();
	return findMin_helper(pass_node,node);
	

}



template<typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::findMin(){
	Node<Key, Value>* root = this->mRoot;

	if(root == NULL){
		return BinarySearchTree<Key, Value>::end();
	}
	else{
		Node<Key, Value>* p_root = root->getParent();

		Node<Key, Value>* target = findMin_helper(root,p_root);


		
			
		splay(target);


		typename BinarySearchTree<Key, Value>::iterator it(target);

		return it;		
	}

}


template<typename Key, typename Value>
Node<Key, Value>* SplayTree<Key, Value>::findMax_helper( Node<Key, Value> * node,Node<Key, Value> * p_node){
	if(node == NULL){
		return p_node;
	}

	Node<Key,Value>* pass_node = node->getRight();
	return findMax_helper(pass_node,node);
	

}



template<typename Key, typename Value>
typename SplayTree<Key, Value>::iterator SplayTree<Key, Value>::findMax(){
	Node<Key, Value>* root = this->mRoot;

	if(root == NULL){
		return BinarySearchTree<Key, Value>::end();
	}
	else{
		Node<Key, Value>* p_root = root->getParent();

		Node<Key, Value>* target = findMax_helper(root,p_root);


		
			
		splay(target);
			
		typename BinarySearchTree<Key, Value>::iterator it(target);

		return it;		
	}

}


template<typename Key, typename Value>
Node<Key, Value>* SplayTree<Key, Value>::deleteMinLeaf_helper(Node<Key, Value>* root){

	if(root == NULL ){
		return root;
	}

	if(root->getLeft() != NULL ){
		return deleteMinLeaf_helper(root->getLeft());
	}
	else{
		if(root->getRight() !=NULL){
			return deleteMinLeaf_helper(root->getRight());
		}
		else{
			return root;
		}
	}
}


template<typename Key, typename Value>
void SplayTree<Key, Value>::deleteMinLeaf(){

	Node<Key, Value>* root = this->mRoot;

	Node<Key, Value>* target_node = deleteMinLeaf_helper(root);

	if(target_node != NULL){
		remove(target_node->getKey());
	}
}


template<typename Key, typename Value>
Node<Key, Value>* SplayTree<Key, Value>::deleteMaxLeaf_helper(Node<Key, Value>* root){

	if(root == NULL ){
		return root;
	}

	if(root->getRight() != NULL ){
		return deleteMaxLeaf_helper(root->getRight());
	}
	else{
		if(root->getLeft() !=NULL){
			return deleteMaxLeaf_helper(root->getLeft());
		}
		else{
			return root;
		}
	}
}


template<typename Key, typename Value>
void SplayTree<Key, Value>::deleteMaxLeaf(){

	Node<Key, Value>* root = this->mRoot;

	Node<Key, Value>* target_node = deleteMaxLeaf_helper(root);

	if(target_node != NULL){
		remove(target_node->getKey());
	}
}

#endif