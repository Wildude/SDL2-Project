#include "structNode.hpp"
// array implementation of stacks
// template class used for flexibility and encapsulation of crucial members (maxsize, top and array)
template <class T>
class arraystack{
    // private visibility is default on class definitions
    const unsigned int maxsize;
    int top = -1;
    T* array = NULL;
    // public members here
    public:
    // default class initiaizer
    // stack can't be initialized
    arraystack(unsigned int maxSize) : maxsize(maxSize) {
        array = new T[maxsize]; // allocating the array
    }
    void push(T item){
        // condition for stack overflow
        if(top == maxsize - 1){
            cout << " Stack Overflow\n\a";
            return;
        }
        array[++top] = item; // appending item
    }
    T pop(){
        // condition for stack underflow
        if(top == -1){
            cout << " Stack Underflow\a\n";
            T num;
            return num;
        }
        return array[top--]; // removing item (from visibility/access at least)
    }
    T peek(){
        if(top < 0){
            cout << " Stack Empty\a\n";
            T num;
            return num;
        }
        return array[top]; // returns item at top
    }
    int size(){
        return top + 1; // returns current size of the stack
    }
    int maxSize(){
        return maxsize; // returns capacity of the stack
    }
    bool isEmpty(){
        return (top < 0); // checks if stack is empty
    }
    bool isFull(){
        return (top == maxsize - 1); // checks if stack is full
    }
    ~arraystack(){
        delete array;
    }
};
template <class T>
class nodestack{
    Lnode<T>* head = NULL;
    Lnode<T>* top = NULL;
    public:
    void push(T data){
        Lnode<T>* temp = new Lnode<T>({data, NULL});
        insertSnode(head, temp);
        top = head;
    }
    void push(Lnode<T>* node){
        Lnode<T>* temp = new Lnode<T>({node->id, NULL});
        insertSnode(head, temp);
        top = head;
    }
    Lnode<T>* pop(){
        if(!top){
            cout << " Stack Underflow\a\n";
            return NULL;
        }
        Lnode<T>* popped = new Lnode<T>({head->id, head->next});
        //delete popped;
        //popped = new Lnode<T>({head->id, head->next});
        deleteSnode(head);
        top = head;
        return popped;
    }
    Lnode<T>* peek() const{  // accessor function: so as to not affect the top node using this function
        return top;
    }
    int size(){
        return getSize(top);
    }
    bool isEmpty(){
        return !top;
    }
    ~nodestack(){
        while(top)pop();
    }
};