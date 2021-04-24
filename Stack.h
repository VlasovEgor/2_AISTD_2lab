#pragma once
#include <iostream>

template <class T>
class Stack
{
private:
    class Node
    {
    public:
        T content;
        Node* next;
        Node* before;
        Node(T content = 0, Node* before = NULL, Node* next = NULL)
        {
            this->content = content;
            this->before = before;
            this->next = next;
        };
        ~Node()
        {  }
    };
    Node* head; //head list
    Node* tail;  //tail list
    size_t size;  //list size
public:
    Stack(Node* head = NULL, Node* tail = NULL) {
        this->head = head;
        this->tail = tail;
        size = 0;
    };
    void push_el(T); // add element to end
    void Clear(); // clear list
    size_t Size(); // get list size
    T pop(); // delete last element
    bool isEmpty(); // test for emptiness
    ~Stack()
    {
        if (head != NULL)
        {
            while (head != NULL && head->next != NULL) //while we can go next
            {
                head = head->next;
                delete head->before;
            }
            size = 0;
            if (head != NULL)
                delete head;
        }
    };
};

