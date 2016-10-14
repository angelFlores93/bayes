#ifndef LIST_H
#define LIST_H


#include <cassert>
#include <iostream>
#include "state.h"

using namespace std;

template <class T>
class Node {
    private:
        T value;
        Node<T> *next;

    public:
        Node(T);
        Node(T, Node<T>*);
        void setValue(T);
        void setNext(Node<T>*);
        Node<T>* getNext();
        T        getValue();
};

template <class T>
Node<T>::Node(T val)
    : value(val) {
}

template <class T>
Node<T>::Node(T val, Node<T> *nxt)
    : value(val), next(nxt) {
}

template <class T>
void Node<T>::setNext(Node<T> *nxt) {
    next = nxt;
}

template <class T>
void Node<T>::setValue(T val) {
    value = val;
}

template <class T>
Node<T>* Node<T>::getNext() {
    return next;
}

template <class T>
T Node<T>::getValue() {
    return value;
}

template <class T>
class List {
    private:
        Node<T> *head;
        Node<T> *tail;
        int size;


        void     setHead(Node<T> *);


        void     setTail(Node<T> *);
        void     setSize(int);


    public:
        List();
        ~List();
        int  getSize();
        bool isEmpty();
        bool contains(T);
        void display();
        void addFirst(T);
        void addLast(T);
        void add(T, int);
        T removeFirst();
        T removeLast();
        T removeAt(int);
        void removeAll();
        void removeAll2();
        T get(int);
        void set(int, T);
        Node<T>* getHead();
        Node<T>* getTail();
};

template <class T>
List<T>::List() {
    head = 0;
    tail = 0;
    size = 0;
}

template <class T>
List<T>::~List() {
    removeAll2();
}

template <class T>
Node<T>* List<T>::getHead() {
    return head;
}

template <class T>
void List<T>::setHead(Node<T> *h) {
    head = h;
}
template <class T>
Node<T>* List<T>::getTail() {
    return tail;
}

template <class T>
void List<T>::setTail(Node<T> *t) {
    tail = t;
}

template <class T>
int List<T>::getSize() {
    return size;
}

template <class T>
void List<T>::setSize(int s) {
    size = s;
}

template <class T>
bool List<T>::isEmpty() {
    bool aux = false;
    if (getHead() == 0 && getTail() == 0){
        aux = true;
    }
    return (aux);
}

template <class T>
bool List<T>::contains(T val) {
    Node<T> *p;
    p = head;
    while (p != 0) {
        if(p->getValue() == val){
            return true;
        
        }
        p = p->getNext();
    }
    return false;
}

template <class T>
void List<T>::display() {
    Node<T> *p;

    //std::cout << "length : " << size << " elements: ";
    p = head;
    while (p != 0) {
        print_state(p->getValue());
        //if (p->getNext() != 0) {
            //std::cout << ", ";
        //}
        p = p->getNext();
    }
    std::cout << std::endl;
}

template <class T>
void List<T>::addFirst(T val) {
    Node<T> *n;
    /* PASO 1 */
    n = new Node<T>(val);
    assert(n != 0);
    /* PASO 2 */
    n->setNext(getHead());
    /* PASO 3 */
    setHead(n);
    setTail(n);
    setSize(getSize() + 1);
}

template <class T>
void List<T>::addLast(T val) {
    if (isEmpty()) {
        addFirst(val);
    } else {
        Node<T> *p, *n;

        p = getTail();
        n = new Node<T>(val);
		assert(n != 0);
        n->setNext(p->getNext());
        p->setNext(n);
        setTail(n);
        setSize(getSize() + 1);
    }
}

template <class T>
void List<T>::add(T val, int pos) {
    Node<T> *n, *p, *q;
    if (pos == 0){
        addFirst(val);
    }else{
        assert (pos < getSize()+1);
        p = getHead();
        q = 0;
        for (int i=0; i<pos; i++){
            q = p;
            p = p->getNext();
        }
        n = new Node<T>(val);
        assert (n!=0);
        n->setNext(p);
        q->setNext(n);
        setSize(getSize()+1);
    }


}

template <class T>
T List<T>::removeFirst() {
    Node<T> *p;
    T val;
    if (getSize() == 1){
        val  = getHead()->getValue();
        setHead(0);
        setTail(0);
    }else{
        assert( !isEmpty() );
        p = getHead();
        /* PASO 1 */
        setHead( p->getNext() );
        /* PASO 2 */
        p->setNext(0);
        /* PASO 3 */
        val = p->getValue();
        /* PASO 4 */
    }

    delete p;
    setSize(getSize() - 1);
    return val;
}

template <class T>
T List<T>::removeLast() {
    Node<T> *p, *q;
    T val;

    assert( !isEmpty() );
    p = getHead();
    q = 0;
    /* BUSCAMOS EL ULTIMO ELEMENTO */
    while (p->getNext() != 0) {
        q = p;
        p = p->getNext();
    }

    if (q == 0) { /* SOLO HAY UNO */
        /* PASO 1 */
        setHead( p->getNext() );
    } else { /* HAY MAS DE UNO*/
        /* PASO 1 */
        q->setNext( p->getNext() );
    }
     /* PASO 2 */
    p->setNext(0);
    /* PASO 3 */
    val = p->getValue();
    /* PASO 4 */
    delete p;
    setSize(getSize() - 1);
    return val;
}

template <class T>
T List<T>::removeAt(int pos) {
    Node<T> *p, *q;
    T val;
    assert (!isEmpty());
    if (pos == 0){
        removeFirst();
    }
    else if (pos == getSize()-1){
        removeLast();
    }else{
        assert (pos < getSize());
        p = getHead();
        q = 0;
        for (int i=0; i<pos; i++){
            q = p;
            p = p->getNext();
        }
        q->setNext(p->getNext());
        p->setNext(0);
        val = p->getValue();
        delete (p);
        setSize(getSize()-1);
        return val;
    }
}

template <class T>
void List<T>::removeAll() {
    Node<T> *p, *q;

    p = getHead();
    q = 0;
    while (p != 0) {

        free_state(p->getValue());
        q = p->getNext();
        
        p->setNext(0);

        delete p;
        p = q;
    }
    setHead(0);
    setTail(0);
    setSize(0);
}
template <class T>
void List<T>::removeAll2() {
    Node<T> *p, *q;

    p = getHead();
    q = 0;
    while (p != 0) {
        q = p->getNext();
        p->setNext(0);
        delete p;
        p = q;
    }
    setHead(0);
    setTail(0);
    setSize(0);
}

template <class T>
T List<T>::get(int pos) {
    T aux;
    Node <T> *p;
    assert (!isEmpty());
    if (pos == 0){
        p = getHead();
        aux = p->getValue();
    }else{
        p = getHead();
        for (int i=0; i<pos; i++){
            p = p->getNext();
        }
        aux = p->getValue();

    }
        return aux;
}

template <class T>
void List<T>::set(int pos, T val ) {
    Node<T> *p;
    assert (!isEmpty());
    if (pos == 0){
        p = getHead();
        p->setValue (val);
    }else{
        assert (pos<getSize());
        p = getHead();
        for (int i=0; i<pos; i++){
            p = p->getNext();
        }
        p->setValue(val);
    }
}

#endif
