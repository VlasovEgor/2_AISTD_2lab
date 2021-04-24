#pragma once
#include <iostream>
template <class T>
class Priority
{
private:
    class Node
    {
    public:
        Node(T content, int Pr = 0, Node* before = NULL, Node* next = NULL)
        {
            this->Pr = Pr;
            this->next = next;
            this->before = before;
            this->content = content;
        };
        ~Node()
        {  }
        int Pr;
        Node* next;
        Node* before;
        T content;
    };

    Node* head; //head list
    Node* tail;  //tail list
    size_t size;  //list size

public:
    Priority(Node* head = NULL, Node* tail = NULL) 
    {
        this->head = head;
        this->tail = tail;
        size = 0;
    };
    void push_el(T, int); // add element to end
    T pop(); // delete first element
    size_t Size(); // get list size
    void clear(); // clear list
    bool isEmpty(); // test for emptiness
    int tail_prior();
    ~Priority()
    {
        while ((head != NULL) && (head->next != NULL)) 
        {
            head = head->next;
            delete head->before;
        }
        size = 0;
        delete head;
    };
};
