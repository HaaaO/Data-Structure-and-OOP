#ifndef ROTATEBST_H
#define ROTATEBST_H

#include  "bst.h"

#include <vector>

template<typename Key, typename Value>
class rotateBST : public BinarySearchTree<Key, Value>
{
protected:
	void leftRotate(Node<Key, Value>* r);
	void rightRotate(Node<Key, Value>* r);

public: 
	bool sameKeys(const rotateBST& t2) const;
	void transform(rotateBST& t2) const;
private:
	void get(Node<Key, Value>* node, std::vector<Key> &k) const;
	void update(Node<Key, Value>* node) ;
	void transform_right(Node<Key, Value>* node,rotateBST& t2);
	Node<Key, Value>* leftRotate_helper(Node<Key, Value>* r);
	Node<Key, Value>* rightRotate_helper(Node<Key, Value>* r);
	void check_height(Node<Key,Value>* node);
	void final_transform(Node<Key, Value>* node, Node<Key, Value>* r_node, rotateBST& t2);
	
};

template<typename Key, typename Value>
void rotateBST<Key, Value>::leftRotate(Node<Key, Value>* r){
	if(r->getRight() == NULL){
		return;
	}
	else{
		Node<Key, Value>* parent = r->getParent();
		Node<Key, Value>* z_node = r;
		Node<Key, Value>* y_node = r->getRight();
		Node<Key, Value>* t1 = y_node->getLeft();

		if(parent == NULL){
			this->mRoot= y_node;
		}

		y_node->setParent(parent);

		if(parent !=NULL){
			if(parent->getLeft() == z_node){
				parent->setLeft(y_node);
			}
			else{
				parent->setRight(y_node);
			}
		}

		z_node->setRight(t1);
		if(t1 != NULL){
			t1->setParent(z_node);
		}
		

		y_node->setLeft(z_node);
		z_node->setParent(y_node);

	}

}
template<typename Key, typename Value>
Node<Key, Value>* rotateBST<Key, Value>::leftRotate_helper(Node<Key, Value>* r){
if(r->getRight() == NULL){
		return r;
	}
	else{
		Node<Key, Value>* parent = r->getParent();
		Node<Key, Value>* z_node = r;
		Node<Key, Value>* y_node = r->getRight();
		Node<Key, Value>* t1 = y_node->getLeft();

		if(parent == NULL){
			this->mRoot= y_node;
		}

		y_node->setParent(parent);

		if(parent !=NULL){
			if(parent->getLeft() == z_node){
				parent->setLeft(y_node);
			}
			else{
				parent->setRight(y_node);
			}
		}

		z_node->setRight(t1);
		if(t1 != NULL){
			t1->setParent(z_node);
		}
		

		y_node->setLeft(z_node);
		z_node->setParent(y_node);

		return y_node;

	}


}

template<typename Key, typename Value>
void rotateBST<Key, Value>::rightRotate(Node<Key, Value>* r){
	if(r->getLeft() == NULL){
		return;
	}
	else {
		Node<Key, Value>* parent = r->getParent();
		Node<Key, Value>* z_node = r;
		Node<Key, Value>* y_node = r->getLeft();
		Node<Key, Value>* t2 = y_node->getRight();

		if(parent == NULL){
			this->mRoot = y_node;
		}

		y_node->setParent(parent);

		if(parent !=NULL){
			if(parent->getLeft() == z_node){
				parent->setLeft(y_node);
			}
			else{
				parent->setRight(y_node);
			}
		}

		z_node->setLeft(t2);
		if(t2 !=NULL){
			t2->setParent(z_node);
		}

		y_node->setRight(z_node);
		z_node->setParent(y_node);



	}


}

template<typename Key, typename Value>
Node<Key, Value>* rotateBST<Key, Value>::rightRotate_helper(Node<Key, Value>* r){
if(r->getLeft() == NULL){
		return r;
	}
	else {
		Node<Key, Value>* parent = r->getParent();
		Node<Key, Value>* z_node = r;
		Node<Key, Value>* y_node = r->getLeft();
		Node<Key, Value>* t2 = y_node->getRight();

		if(parent == NULL){
			this->mRoot = y_node;
		}

		y_node->setParent(parent);

		if(parent !=NULL){
			if(parent->getLeft() == z_node){
				parent->setLeft(y_node);
			}
			else{
				parent->setRight(y_node);
			}
		}

		z_node->setLeft(t2);
		if(t2 !=NULL){
			t2->setParent(z_node);
		}

		y_node->setRight(z_node);
		z_node->setParent(y_node);

		return y_node;



	}


}


template<typename Key, typename Value>
void rotateBST<Key, Value>::check_height(Node<Key,Value>* node){
	int height_left = 1;
	int height_right = 1;
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
	
}

template<typename Key, typename Value>
void rotateBST<Key, Value>::get( Node<Key, Value>* node,  std::vector<Key> &vec) const{
	if(node->getLeft() != NULL) {
        get(node->getLeft(),vec);
    }
    vec.push_back(node->getKey());
    if(node->getRight() != NULL) {
        get(node->getRight(),vec);
    }
}





template<typename Key, typename Value>
bool rotateBST<Key, Value>::sameKeys(const rotateBST& t2) const{
	std::vector<Key> vec_t1;
	std::vector<Key> vec_t2;
	Node<Key, Value>* node_t1 = this->mRoot;
	Node<Key, Value>* node_t2 = t2.mRoot;
	bool result = true;
	if(node_t1 == NULL && node_t2!=NULL){
		result = false;
	}
	else if (node_t2 == NULL && node_t1!=NULL){
		result = false;
	}


	if(node_t1 !=NULL && node_t2 !=NULL){

		get(node_t1,vec_t1);
		get(node_t2,vec_t2);

	

		if(vec_t1.size() != vec_t2.size()){
			return false;
		}

		for(unsigned int i = 0; i < vec_t1.size(); i++){

		if(vec_t1[i] != vec_t2[i]){
			result = false;
		}
		}
	}	
	return result;
}



template<typename Key, typename Value>
void rotateBST<Key, Value>::update(Node<Key, Value>* node){
	if(node->getLeft() != NULL) {
        update(node->getLeft());
    }
    if(node->getRight() != NULL) {
        update(node->getRight());
    }
   check_height(node);

}


template<typename Key, typename Value> 
void rotateBST<Key, Value>::transform_right(Node<Key, Value>* node,rotateBST& t2){
	if(node->getLeft() == NULL && node->getRight() ==NULL){
		return;
	}

	while(node->getLeft() != NULL){
		node = t2.rightRotate_helper(node);
	}

	transform_right(node->getRight(),t2);


}

template<typename Key, typename Value> 
void rotateBST<Key, Value>::final_transform(Node<Key, Value>* node, Node<Key, Value>* r_node, rotateBST& t2){
	if(node == NULL){
		return;
	}

	if(node->getKey() > r_node->getKey()){
		while(node->getKey() != r_node->getKey()){

			node = t2.rightRotate_helper(node);

		}
	}

	if(node->getKey() < r_node->getKey()){
		while(node->getKey() != r_node->getKey()){
			node = t2.leftRotate_helper(node);

		}

	}

	final_transform(node->getLeft(),r_node->getLeft(),t2);
	final_transform(node->getRight(),r_node->getRight(),t2);

}

template<typename Key, typename Value>
void rotateBST<Key, Value>::transform(rotateBST& t2) const{
	if(t2.mRoot == NULL && this->mRoot == NULL){
		return;
	}

	if(sameKeys(t2)){

			t2.transform_right(t2.mRoot,t2);
			t2.update(t2.mRoot);
			t2.update(t2.mRoot);
			t2.final_transform(t2.mRoot,this->mRoot,t2);
			t2.update(t2.mRoot);
	}

}


#endif