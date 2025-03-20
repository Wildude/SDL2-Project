// queue implementation header
#include "structNode.hpp"
// an abstract singluar array queue
template <class T>
class arrayqueueS{
    const unsigned int maxsize;
    int front = -1;
    int rear = -1;
    T* array = NULL;
    // used to shift all elements to the left
    // helpful to push into queue when rear reached queue capacity but front didn't reach 0
    // avoids the problem where item's can't be pushed even when there is space
    // private function to avoid getting tampered with
    void maintain(){ 
        for(int i = 0; i + front <= rear; i++){
            array[i] = array[i + front];
        }
        rear -= front;
        front = 0;
    }
    public:
    arrayqueueS(unsigned int maxSize) : maxsize(maxSize) {
        array = new T[maxsize];
    }
    void insert(T item){
        if(rear == maxsize - 1){
            if(!front){
                cout << " Queue Overflow\a\n";
                return;
            }
            else maintain();
        }
        array[++rear] = item;
        if(front < 0)front++;
    }
    T remove(){
        if(front < 0 && rear < 0){
            cout << " Queue Underflow\a\n";
            T num;
            return num;
        }
        front++;
        if(front > rear){
            int temp = rear;
            front = -1;
            rear = -1;
            return array[temp];
        }
        return array[front - 1];
    }
    T peekR(){
        if(rear < 0){
            cout << " Queue Empty\a\n";
            T num;
            return num;
        }
        return array[rear];
    }
    T peekF(){
        if(front < 0){
            cout << " Queue Empty\a\n";
            T num;
            return num;
        }
        return array[front];
    }
    int size(){
        return (front < 0 ? 0 : ((rear - front) + 1));
    }
    int maxSize(){
        return maxsize;
    }
    bool isFull(){
        return (!front && rear == maxsize - 1);
    }
    bool isEmpty(){
        return (front < 0 && rear < 0);
    }
};
template <class T>
class arrayqueueC{
    const unsigned int maxsize;
    int front = -1;
    int rear = -1;
    T* array = NULL;  
    int queuesize = 0;
    public:
    arrayqueueC(unsigned int maxSize) : maxsize(maxSize) {
        array = new T[maxsize];
    }
    void insert(T item){
        if(queuesize == maxsize){
            cout << " Queue Overflow\a\n";
            return;
        }
        queuesize++;
        if(rear == maxsize - 1)rear = -1;
        array[++rear] = item;
        if(front < 0)front++;
    }
    T remove(){
        if(!queuesize){
            cout << " Queue Underflow\n\a";
            T num;
            return num;
        }
        queuesize--;
        front++;
        if(front == maxsize){
            int temp = front - 1;
            front = 0;
            return array[temp];
        }
        return array[front - 1];
    }
    T peekR(){
        if(!queuesize){
            cout << " empty queue\a\n";
            T num;
            return num; 
        }
        else return array[rear];
    }
    T peekF(){
        if(!queuesize){
            cout << " empty queue\a\n";
            T num;
            return num; 
        }
        else return array[front];
    }
    int size(){
        return queuesize;
    }
    int maxSize(){
        return maxsize;
    }
    bool isEmpty(){
        return !queuesize;
    }
    bool isFull(){
        return queuesize == maxsize;
    }
};
template <class T>
class nodequeue{
    Lnode<T>* head = NULL;
    Lnode<T>* front = NULL;
    Lnode<T>* rear = NULL;
    public:
    void insert(T data){
        Lnode<T>* temp = new Lnode<T>({data, NULL});
        Lnode<T>* tailnode = head; 
        int counter = 0;
        while(tailnode){
            tailnode = tailnode->next;
            counter++;
        }
        nextNode(head, counter) = temp;
        rear = temp;
        if(!front)front = temp;
    }
    void insert(Lnode<T>* node){
        Lnode<T>* temp = new Lnode<T>({node->id, NULL});
        Lnode<T>* tailnode = head; 
        int counter = 0;
        while(tailnode){
            tailnode = tailnode->next;
            counter++;
        }
        nextNode(head, counter) = temp;
        rear = temp;
        if(!front)front = temp;
    }
    Lnode<T>* remove(){
        if(!front){
            cout << " Queue Underflow\a\n";
            return NULL;
        }
        Lnode<T>* removed = new Lnode<T>({front->id, front->next});
        //delete removed;
        //removed = new Lnode<T>({front->id, front->next});
        deleteSnode(front);
        if(!front)rear = NULL;
        return removed;
    }
    Lnode<T>* peekR() const{
        if(!rear){
            cout << " empty queue\a\n";
            return NULL;
        }
        return rear;
    }
    Lnode<T>* peekF() const{
        if(!front){
            cout << " empty queue\a\n";
            return NULL;
        }
        return front;
    }
    int size(){
        return getSize(front);
    }
    bool isEmpty(){
        return (!front && !rear);
    }
};
template <class T>
class dequeS{
    const unsigned int maxsize;
    int front = -1;
    int rear = -1;
    T* array = NULL;
    void maintainF(){
        for(int i = 0; i + front <= rear; i++){
            array[i] = array[i + front];
        }
        rear -= front;
        front = 0;
    }
    void maintainR(){
        for(int i = 0; rear - i >= 0; i++){
            array[maxsize - 1 - i] = array[rear - i];
        }
        front += maxsize - 1 - rear;
        rear = maxsize - 1;
    }
    public:
    dequeS(unsigned int maxSize) : maxsize(maxSize){
        array = new T[maxsize];      
    }
    void insertF(T item){
        if(front < 0){
            array[++front] = item;
            if(rear < 0)rear++;
            return;
        }
        if(!front){
            if(rear == maxsize - 1){
                cout << " Deque Overflow\a\n";
                return;
            }
            else{
                maintainR();
            }
        }
        array[--front] = item;
    }
    void insertR(T item){
        if(rear == maxsize - 1){
            if(!front){
                cout << " Deque Overflow\a\n";
                return;
            }
            else{
                maintainF();
            }
        }
        array[++rear] = item;
        if(front < 0)front++;
    }
    T removeF(){
        if(front < 0){
            cout << " Deque Underflow\a\n";
            T num;
            return num;
        }
        front++;
        if(front > rear){
            int temp = front - 1;
            front = -1;
            rear = -1;
            return array[temp];
        }
        return array[front - 1];
    }
    T removeR(){
        if(rear < 0){
            cout << " Deque Underflow\a\n";
            T num;
            return num;
        }
        rear--;
        if(rear < front){
            int temp = rear + 1;
            rear = -1;
            front = -1;
            return array[temp];
        }
        return array[rear + 1];
    }
    T peekF(){
        if(front < 0){
            cout << " Deque Empty\a\n";
            T num;
            return num;
        }
        return array[front];
    }
    T peekR(){
        if(rear < 0){
            cout << " Deque Empty\a\n";
            T num;
            return num;
        }
        return array[rear];
    }
    int size(){
        return (front < 0 ? 0 : (rear - front) + 1);
    }
    int maxSize(){
        return maxsize;
    }
    bool isFull(){
        return rear == maxsize - 1 && !front;
    }
    bool isEmpty(){
        return front < 0 && rear < 0;
    }
};
template <class T>
class dequeC{
    const unsigned int maxsize;
    int front = -1;
    int rear = -1;
    int dequesize = 0;
    T* array = NULL;
    public:
    dequeC(unsigned int maxSize) : maxsize(maxSize){
        array = new T[maxsize];      
    }
    void insertF(T item){
        if(dequesize == maxsize){
            cout << " Deque Overflow\a\n";
            return;
        }
        if(front < 0){
            array[++front] = item;
            if(rear < 0)rear++;
            dequesize++;
            return;
        }
        if(!front){
            front = maxsize - 1;
            array[front] = item;
            dequesize++;
            return;
        }
        array[--front] = item;
        dequesize++;
    }
    void insertR(T item){
        if(dequesize == maxsize){
            cout << " Deque Overflow\a\n";
            return;
        }
        if(rear == maxsize - 1){
            rear = 0;
            array[rear] = item;
            dequesize++;
            return;
        }
        array[++rear] = item;
        if(front < 0)front++;
        dequesize++;
    }
    T removeF(){
        if(!dequesize){
            cout << " Deque Underflow\n\a";
            T num;
            return num;
        }
        front++;
        if(front == maxsize){
            int temp = front - 1;
            front = 0;
            dequesize--;
            return array[temp];
        }
        dequesize--;
        return array[front - 1];
    }
    T removeR(){
        if(!dequesize){
            cout << " Deque Underflow\n\a";
            T num;
            return num;
        }
        rear--;
        if(rear < 0){
            int temp = rear + 1;
            rear = maxsize - 1;
            dequesize--;
            return array[temp];
        }
        return array[rear + 1];
    }
    T peekF(){
        if(!dequesize){
            cout << " Deque Empty\a\n";
            T num;
            return num;
        }
        return array[front];
    }
    T peekR(){
        if(!dequesize){
            cout << " Deque Empty\a\n";
            T num;
            return num;
        }
        return array[rear];
    }
    int size(){
        return dequesize;
    }
    int maxSize(){
        return maxsize;
    }
    bool isFull(){
        return dequesize == maxsize;
    }
    bool isEmpty(){
        return !dequesize;
    }
};
template <class T>
class nodedeque{
    Bnode<T>* head = NULL;
    Bnode<T>* front = NULL;
    Bnode<T>* rear = NULL;
    public:
    void insertF(Bnode<T>* node){
        insertDnode(head, node);
        front = head;
        if(!rear)rear = front;
    }
    void insertR(Bnode<T>* node){
        Bnode<T>* tail = head;
        int counter = 0;
        while(tail){
            tail = tail->next;
            counter++;
        }
        insertDnode(head, node, counter);
        rear = node;
        if(!front)front = rear;
    }
    Bnode<T>* removeF(){
        if(!front){
            cout << " Deque Underflow\a\n";
            return NULL;
        }
        static Bnode<T>* removedF = new Bnode<T>();
        delete removedF;
        removedF = new Bnode<T>({front->id, front->prev, front->next});
        if(head->next == NULL && head->prev == NULL){
            Bnode<T>* temp = head;
            head = NULL;
            delete temp;
            front = head;
            rear = front;
            return removedF;
        }
        else deleteDnode(head);
        front = head;
        return removedF;
    }
    Bnode<T>* removeR(){
        if(!rear){
            cout << " Deque Underflow\n\a";
            return NULL;
        }
        static Bnode<T>* removedR = new Bnode<T>();
        delete removedR;
        removedR = new Bnode<T>({rear->id, rear->prev, rear->next});
        if(head->next == NULL && head->prev == NULL){
            Bnode<T>* temp = head;
            head = NULL;
            delete temp;
            rear = head;
            front = rear;
            return removedR;
        }
        deleteDnode(head, getSize(head) - 1);
        Bnode<T>* tail = head;
        int counter = 0;
        if(tail)
        while(tail->next){
            tail = tail->next;
        }
        rear = tail;
        return removedR;
    }
    Bnode<T>* peekF(){
        if(!front){
            cout << " Deque Empty\a\n";
            return NULL;
        }
        return front;
    }
    Bnode<T>* peekR(){
        if(!rear){
            cout << " Deque Empty\a\n";
            return NULL;
        }
        return rear;
    }
    int size(){
        return getSize(head);
    }
    int isEmpty(){
        return !front && !rear;
    }
};