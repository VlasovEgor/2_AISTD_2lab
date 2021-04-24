#include "Queue.h"
#include <iostream>
using namespace std;

template <class T>
void Priority<T>::push_el(T add, int prior) // add element to end
{
	if (size == 0) //if list is empty
	{
		head = new Node(add, prior); //create head
		tail = head;
	}
	else
	{
		Node* newNod = new Node(add, prior);
		Node* cur = head;
		while ((newNod->Pr < cur->Pr) && (cur->next != NULL)) //top priority in the head
		{
			cur = cur->next;
		}
		if ((newNod->Pr <= cur->Pr) && (cur->next == NULL)) {
			newNod->before = cur;
			newNod->next = NULL;
			cur->next = newNod;
			tail = newNod;
		}
		else if ((newNod->Pr >= cur->Pr) && (cur->before == NULL))
		{
			newNod->before = NULL;
			newNod->next = cur;
			cur->before = newNod;
			head = newNod;
		}
		else {
			newNod->next = cur;
			newNod->before = cur->before;
			cur->before->next = newNod;
			cur->before = newNod;

		}
	}
	size++;
}
template <class T>
T Priority<T>::pop() // delete first element
{
	T ct;
	if (size == 1)
	{
		size = 0;
		ct = head->content;  
		head = NULL;
		tail = NULL;
	}
	else if (size > 1) //if list is not empty
	{
		ct = tail->content;
		tail = tail->before; //set new tail
		delete tail->next;
		tail->next = NULL;
		size--;
	}
	return ct;
}
template <class T>
void Priority<T>::clear() // clear list
{
	if (head != NULL)
	{
		while (head->next != NULL)  //delete all elements
		{
			head = head->next;
			delete head->before;
		}
		size = 0;
		head = NULL;
		tail = NULL;
	}
}
template <class T>
size_t Priority<T>::Size() // get list size
{
	return size;
}
template <class T>
int Priority<T>::tail_prior() {
	return tail->Pr;
}
template <class T>
bool Priority<T>::isEmpty() // test for emptiness
{
	if (head == NULL)
		return true;
	return false;
}