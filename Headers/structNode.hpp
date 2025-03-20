#pragma once
#include <iostream>
#include <fstream>
using namespace std;
// structure that defines a singly/circular linked list
template <class T>
struct Lnode{
    T id;
    Lnode<T>* next;
};
// structure that defines a doubly/circular linked list
template <class T>
struct Bnode{
    T id;
    Bnode<T>* prev;
    Bnode<T>* next;
};
// displays a single singly linked list node on an output stream (cout by default)
template <class T>
void displayS(T* Node, ostream& os = cout){
    if(Node){
        os << " ========================================\n";
        os << " have node: " << Node << "\n";
        os << " with id: " << Node -> id << "\n pointing to (next): ";
        if(Node->next)os << Node->next;
        else os << "NULL";
        os << "\n ========================================\n";
    }
    else{
        os << " ========================================\n";
        os << " have node: NULL\n";
        os << " ========================================\n";
    }
}
// displays a single doubly linked list node on an output stream (cout by default)
template <class T>
void displayD(T* Node, ostream& os = cout){
    if(Node){
        os << " ========================================\n";
        os << " have node: " << Node << "\n";
        os << " with id: " << Node->id << "\n pointing to (prev, next): ";
        if(Node->prev)os << Node->prev;
        else os << "NULL";
        os << ", ";
        if(Node->next)os << Node->next << endl;
        else os << "NULL\n";
        os << " ========================================\n";
    }
    else{
        os << " ========================================\n";
        os << " have node: NULL\n";
        os << " ========================================\n";
    }
}
// displays only the node pointers
// displays all nodes of a doubly/circular linked list
template <class T>
void DisplayD(T* Node, ostream& os = cout){
    T* temp = Node;
    int counter = 0;
    while(true){
        os << " display[" << counter<< "]:\n";
        displayD(temp);
        counter++;
        if(!temp){
            os << " !!TAIL-REACHED!!\n";
            break; // avoids traversing beyond NULL/Tail node
        }
        else if(temp == temp->next){
            os << " !!SELF-REFERING-NODE!!\n";
            break; // avoids infinite loops caused by a self referring node
        }
        else if(temp->next == Node){
            os << " !!TAIL-REACHED!!\n";
            break; // avoids infinite loops caused by a tail node pointing to the head node
        }
        temp = temp->next;
    }
}
// displays all nodes of a singly/circular linked list
template <class T>
void DisplayS(T* Node, ostream& os = cout){
    T* temp = Node;
    int counter = 0;
    while(true){
        os << " display[" << counter<< "]:\n";
        displayS(temp);
        counter++;
        if(!temp){
            os << " !!TAIL-REACHED!!\n";
            break; // avoids traversing beyond NULL/Tail node
        }
        else if(temp == temp->next){
            os << " !!SELF-REFERING-NODE!!\n";
            break; // avoids infinite loops caused by a self referring node
        }
        else if(temp->next == Node){
            os << " !!TAIL-REACHED!!\n";
            break; // avoids infinite loops caused by a tail node pointing to the head node
        }
        temp = temp->next;
    }
}
// returns an alias to the ith node in the linked list by forward traversal (makes editing the linked list easier)
template<class T>
T*& nextNode(T*& curr, int index = 0){
    return (index > 0 ? nextNode(curr->next, index - 1) : curr);
}
// returns an alias to the ith node in the linked list by backward traversal (makes editing the linked list easier)
template<class T>
T*& prevNode(T*& curr, int index = 0){
    return (index > 0 ? prevNode(curr->prev, index - 1) : curr);
}
// setting the current node to the next node (simplifies traversal by avoiding multiple traversals)
template<class T>
void setNextNode(T*& curr){
    curr = curr->next;
}
template <class T>
void setPrevNode(T*& curr){
    curr = curr->prev;
}
// singly linked list insertion at a location (before the ith node)
template <class T>
void insertSnode(T*& head, T* ins, int index = 0){
    if(index < 0){cout << " negative index error in deletion\a\n"; return;}
    T* curr = head; // traversing pointer
    int size = 0; // size of the list
    for(int i = 0; i < index; i++){
        if(!curr && !i){ // checks if list is empty
            if(!index)break; // if adding on an empty list, index must be 0 only
            cout << " insertion out of bounds\a\n"; // else it quits
            return;
        }
        if(curr){ // checks if the current node is not NULL
            // sets size to current location + 1 to avoid traversing beyond the tail
            if(curr->next == NULL)size = i + 1; 
            else size = i;
        }
        else if(i == size){ // if this is reached then the insertion is out of bounds
            cout << " insertion out of bounds\n\a";
            return;
        }
        curr = curr->next; // forward traversing
    }
    // the next pointer of the inserted node is the current node
    ins->next = curr; 
    // the current pointer will point to the inserted node
    curr = ins;
    // traverses to the exact node to be changed and returns it's alias.
    // this is done since the head pointer must be passed by reference
    // for the insertion to work outside the function scope.
    nextNode(head, index) = curr;
}
// singly linked list deletion at a location
template <class T>
void deleteSnode(T*& head, int index = 0){
    if(index < 0){cout << " negative index error in deletion\a\n"; return;}
    T* curr = head; // traversing pointer
    int size = 0; // size of the list
    for(int i = 0; i <= index; i++){
        if(!curr && !index){cout << " Linked list is already empty\a\n"; return;} // can't delete an empty list
        if(curr){
            if(curr->next == NULL)size = i + 1; // setting the size to avoid traversal beyond tail
            else size = i;
        }
        else if(i == size){ // if this is reached, deletion is out of bounds
            cout << " deletion out of bounds\n\a";
            return;
        }
        // traverses only if the index is not pointing the current node
        // this avoids traversal beyond Tail.
        if(i != index)curr = curr->next; 
    }
    T* temp = curr; // holding the memory location to be deleted.
    // setting the current node to the next node and applying changes to the actual head pointer parameter
    setNextNode(nextNode(head, index));
    delete temp; // freeing memory
}
// simple searching for singly/doubly/circular linked list (forward traversal only)
template <class T>
T* search(T* head, string id){
    T* curr = head;
    if(!curr){cout << " linked list is empty\a\n";return NULL;}
    while(true){
        if(!curr)break; // for non-circular linked lists 
        else if(curr->id == id)return curr; // checks match for id and returns or not
        else if(curr->next == head)break; // for circular linked lists
        else curr = curr->next; // traversing
    }
    cout << " couldn't find id: " << id << "\a\n";
    return NULL;
}
// insertion for a doubly linked list at a location
template <class T>
void insertDnode(T*& head, T* ins, int ind = 0){
    if(ind < 0){
        cout << " negative index error\n\a";
        return;
    }
    T* curr = head;
    int size = 0;
    for(int i = 0; i < ind; i++){
        if(!curr && !i){ // checks if list is empty
            if(!ind)break; // insertion allowed on empty list only if index is 0
            cout << " insertion out of bounds\a\n"; // else it quits
            return;
        }
        if(curr){ // checks if current node is not NULL
            if(!curr->next){ // if next node is NULL
                size = i + 1; // sets size to avoid traversal beyond tail
                if(size == ind){ // if the node is to be inserted at the tail (next node of the tail which is NULL)
                    ins->next = NULL; // setting next of inserted node to NULL
                    ins->prev = curr; // setting prev of inserted node to the current node
                    nextNode(head, ind) = ins; // applying changes to the actual head node
                    return;
                }
            }
            else size = i;
        }
        else if(i == size){ // out of bound condition
            cout << " insertion out of bounds\a\n";
            return;
        }
        curr = curr->next; // traversing
    }
    // setting next of inserted node to current node
    ins->next = curr;
    // setting prev of inserted node to the prev of current node if it exists, else to NULL
    ins->prev = (curr ? curr->prev : NULL);
    // if current is not NULL (to avoid program termination since NULL nodes don't have prev nodes)
    if(curr)curr->prev = ins; // setting prev of current node to inserted node;
    nextNode(head, ind) = ins; // applying changes to the actual head node
}
// deletion for a doubly linked list at a location
template <class T>
void deleteDnode(T*& head, int ind = 0){
    if(ind < 0){
        cout << " negative index error\n\a";
        return;
    }
    T* curr = head; // traversing pointer
    int size = 0; // size of list
    for(int i = 0; i <= ind; i++){
        if(!curr && !i){cout << " linked list is already empty\a\n"; return;}
        if(curr){
            if(!curr->next)size = i + 1;
            else size = i;
        }
        else if(i == size){
            cout << " deletion out of bounds\a\n";
            return;
        }
        // traverses only if the index is not pointing the current node
        // this avoids traversal beyond Tail.
        if(i != ind)curr = curr->next;
    }
    T* temp = curr;
    if(curr->next == NULL && curr->prev == NULL)head = NULL; // if the list has only one node
    else{
        // traverses to and holds alias to the current node of the actual head
        T*& thisNode = nextNode(head, ind); 
        // if the current node has a next node 
        // (to avoid program termination since NULL nodes don't have prev nor next nodes)
        // sets the prev of the it's next node to it's prev
        if(thisNode->next)thisNode->next->prev = thisNode->prev; 
        // setting current node to it's next (affects actual head since it's an alias)
        thisNode = thisNode->next; 
    }
    delete temp; // frees memory
}
// returns the tail of a circular linked list
template <class T>
T*& Tail(T*& head){
    T* curr = head;
    int index = 0;
    while(curr->next != head){
        curr = curr->next;
        index++;
    }
    return nextNode(head, index);
}
// insertion for a singly/circular linked list at a location
template <class T>
void insertCnode(T*& head, T* ins, int ind = 0){
    if(ind < 0){cout << " negative index error\n"; return;}
    T* curr = head;
    int size = 0;
    for(int i = 0; i < ind; i++){
        if(!curr && !i){
            if(!ind)break;
            cout << " insertion out of bounds\a\n";
            return;
        }
        if(curr){
            // checks if next node is head instead of NULL, since the list is circular
            // size is set accordingly so as not to traverse beyond tail
            if(curr->next == head)size = i + 1;
            else size = i;
        }
        else if(i == size){
            cout << " insertion out of bounds\a\n";
            return;
        }
        curr = curr->next; // traversing
    }
    // next of inserted node is set to current node if current node exists else to itself
    // this is because circular linked lists of one node point to themselves
    ins->next = (curr ? curr : ins); 
    // if current node is not NULL (to avoid program termination while attempting to access next node)
    // sets current node's next node to inserted node if it was a single node before (refering to itself)
    // else to itself, which is another node
    if(curr)curr->next = (curr->next == curr ? ins : curr->next);
    curr = ins; // current node is set to inserted node
    nextNode(head, ind) = curr; // applying changes to the actual head pointer
}
// deletion for a singly/circular linked list at a location
template <class T>
void deleteCnode(T*& head, int ind = 0){
    if(ind < 0){cout << " negative index error\n"; return;}
    T* curr = head;
    int size = 0;
    bool sizefound = false; // used to avoid jumps to the head since the list is circular
    for(int i = 0; i <= ind; i++){
        if(!curr && !i){cout << " linked list already empty\a\n"; return;}
        if(sizefound){
            cout << " deletion out of bounds\n";
            return;
        }
        if(curr){
            if(curr->next == head){
                size = i + 1;
                sizefound = true; // avoids invalid traversals (traversing from tail to head again)s
            }
            else size = i;
        }
        else if(i == size){
            cout << " deletion out of bounds\a\n";
            return;
        }
        if(i != ind && !sizefound)curr = curr->next;
    }
    T* temp = curr; // holding the memory location of the current node
    if(curr->next == curr)head = NULL; // if list is a single node 
    else{
        // the node before the current node is needed since the list is circular
        // if the current node is the head, the prev node is the tail
        // otherwise it's forward traversed until the current node - 1
        // an alias to the prevNode is used to affect the actual head parameter directly
        T*& prevNode = (ind ? nextNode(head, ind - 1) : Tail(head));
        // the next of the previous node is the next of the current node
        prevNode->next = curr->next;
        // used if the head node is deleted
        // since the head node couldn't be affected by the alias for some reason
        if(!ind)head = head->next;
    }
    delete temp; // frees memory
}
// insertion for a doubly/circular linked list at a location
template <class T>
void insertCDnode(T*& head, T* ins, int ind = 0){
    if(ind < 0){cout << " negative index error\n"; return;}
    T* curr = head;
    int size = 0;
    for(int i = 0; i < ind; i++){
        if(!curr && !i){
            if(!ind)break;
            cout << " insertion out of bounds\a\n";
            return;
        }
        if(curr){
            // next node of the current node can't be NULL only the head itself
            // this condition is used to find the size
            if(curr->next == head){
                size = i + 1;
                // if the inserted node is to be added after the tail (it will become the tail)
                if(size == ind){ 
                    ins->next = head; // next of the inserted node is the head (since list is circular)
                    ins->prev = curr; // prev of the inserted node is the current node
                    head->prev = ins; // the prev of the head node is the inserted node (since list is circular)
                    nextNode(head, ind) = ins; // applying changes to the actual head parameter
                    return;
                }
            }
            else size = i;
        }
        else if(i == size){
            cout << " insertion out of bounds\a\n";
            return;
        }
        curr = curr->next; // traversing
    }
    // prev of inserted node is prev of current node if current node exists
    // else it's itself (added to empty node)
    ins->prev = (curr ? curr->prev : ins);
    // next of inserted node is next of current node if current node exists
    // else it's itself (added to empty node)
    ins->next = (curr ? curr : ins);
    // if current node exists (to avoid program termination caused by accessing NULL)
    if(curr){
        curr->prev = ins; // previous of the current node is the inserted node
        // alias to the prev node of the current node (needed since it's doubly and circular linked list)
        // if current node is head node, the prev node is tail
        // else it's forward traversed to current node - 1
        T*& prevNode = (ind ? nextNode(head, ind - 1) : Tail(head));
        // setting next of the prev node of the current node to the inserted node.
        prevNode->next = ins; // directly affects the actual head pointer since it's an alias
    }
    nextNode(head, ind) = ins; // applying changes to the actual head pointer
}
// deletion of a doubly/circular linked list at a location
template <class T>
void deleteCDnode(T*& head, int ind = 0){
    if(ind < 0){cout << " negative index error\n"; return;}
    T* curr = head;
    int size = 0;
    bool sizefound = false; // used to avoid jumping back from tail to head node
    for(int i = 0; i <= ind; i++){
        if(!curr && !i){cout << " linked list already empty\a\n"; return;}
        if(sizefound){
            cout << " deletion out of bounds\n";
            return;
        }
        if(curr){
            if(curr->next == head){
                size = i + 1;
                sizefound = true;
            }
            else size = i;
        }
        // used to avoid jumps
        if(i != ind && !sizefound)curr = curr->next;
    }
    T* temp = curr; // holding memory location to the current node
    if(head->prev == head && head->next == head)head = NULL; // if the list has one node
    else{
        // holding alias to the current node
        T*& thisNode = nextNode(head, ind);
        // holding alias to the current node's prev
        T*& prevNode = thisNode->prev;
        // holding alias to the current node's next
        T*& nextNode = thisNode->next;
        prevNode->next = curr->next; // setting the next of the prev node to the next of the current node
        nextNode->prev = curr->prev; // setting the prev of the next node to the prev of the current node
        // setting current node to the next node
        thisNode = nextNode; // changes are applied directly to the acutal head pointer
    }
    delete temp; // freeing memory
}
template <class T>
int getSize(T* node){
    int size = 0;
    while(nextNode(node, size))size++;
    return size;
}
