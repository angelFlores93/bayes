#ifndef QUEUELIST_H
#define QUEUELIST_H
#include "list.h"
#include "state.h"


template <class T>
class QueueList{
    private:
        List<struct State> my_list;
    public:
        QueueList();
        bool isEmpty();
        void enqueue(T);
        T front();
        T dequeue();
        void clear();
        void display();
        bool contains(T val);
};

template <class T>
QueueList<T>::QueueList(){
}

template <class T>
bool QueueList<T>::isEmpty(){
    bool aux = false;
    if (my_list.getHead() == 0 && my_list.getTail () == 0){
        aux = true;
    }
    return (aux);
}

template <class T>
void QueueList<T>::enqueue(T val){
    if (my_list.isEmpty()){
        my_list.addFirst(val);
    }else{
        int i = 0;
        int flag = 0;
        Node<T> *aux = my_list.getHead();
        while (aux != NULL){
            if (val.cost < aux->getValue().cost){
                my_list.add(val, i);
                flag = 1; 
                break;
            }
            i++;
            aux = aux->getNext();
        }
        if (flag == 0){
            my_list.addLast(val);
        }
    }
}

template <class T>
T QueueList<T>::front(){
    return (my_list.getHead()->getValue());
}

template <class T>
T QueueList<T>::dequeue(){
    return (my_list.removeFirst());
}

template <class T>
void QueueList<T>::clear(){
    my_list.removeAll();
}

template <class T>
void QueueList<T>::display(){
    my_list.display();

}
template <class T>
bool QueueList<T>::contains(T val){
    Node<T> *p;
    p = my_list.getHead();
    while (p != 0) {
        struct State aux = p->getValue();
        if (compare(&aux, &val) == 1) {
            return true;
        }
        p = p->getNext();
    }
    return false;

}
#endif
