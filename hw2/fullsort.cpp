struct Node {
    int value;
    struct Node* next;
};


// Find out the minimum value and the address of this
// value
void func_min(Node* in, int &min, Node* &ptr)
{
// trigger the base case when it reach the end of list
    if (in == nullptr) return;
    // compare the value with min and recursive call
    // the next element
    if (in->value < min)
    {
        min = in->value;
        ptr = in;
        func_min(in->next, min, ptr);
    }
    else 
    {
        func_min(in->next, min, ptr);
    }
}

//selection sort find the minimum value in the list and 
//put it in the head, and then head = head ->next, and 
// do the same to the shortened new list, until the 
//list is empty

void sort (Node* &pre_head)
{
    // trigger the base case when there is only one element
    // in the list
    if(pre_head -> next== nullptr) return;

    //initialise the min and min_p for fun_mim()
    int min = pre_head -> value;
    Node* min_p;

    // find the minimum value and address
    func_min(pre_head, min, min_p);

    // swap the value with the head of the list
    int temp = pre_head -> value;
    pre_head -> value = min;
    min_p -> value = temp;
    // do the tail recurion
    sort(pre_head -> next);
}


Node* fullsort(Node* in){
    //keep track of the head
    Node* f = in;
    sort(in);
    return f;
}
 
