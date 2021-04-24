#pragma once
#include"Stack.h"
#include "Stack.cpp"
using namespace std;

template <class Key, class Value>
class RBTree
{
private:
	class Node
	{
	public:

		Node* parent;
		Node* left;
		Node* right;
		Key key;
		Value value;
		bool color; //black=true , red=false
		Node(Key key, Value value, Node* left = nullptr, Node* right = nullptr, Node* parent = nullptr, bool color = 0) {
			this->key = key;
			this->value = value;
			this->left = left;
			this->right = right;
			this->parent = parent;
			this->color = color;
		}
		~Node() {};
	};
	class DFT_Iterator // depth-first traverse
	{
	private:
		Stack<Node*> stack;
		Node* Itcurrent;
		Node* zero;
	public:
		DFT_Iterator(Node* Current, Node* nill)
		{
			Itcurrent = Current;
			zero = nill;
		};
		Node* next() {
			Node* temp = Itcurrent;
			if (Itcurrent->right != zero) //add right tree to stack
				stack.push_el(Itcurrent->right);
			if (Itcurrent->left != zero) //go left
			{
				Itcurrent = Itcurrent->left;
			}
			else {
				if (!stack.isEmpty()) // if can't
					Itcurrent = stack.pop();
				else Itcurrent = zero;
			}
			return temp;
		};
		bool Next()
		{
			if (Itcurrent != zero)
				return true;
			return false;
		};
		~DFT_Iterator() {}
	};

	Node* root;
	Node* zero;
	int size;
	void Left_Rotate(Node*); //movement on the left side
	void Right_Rotate(Node*); // movement on the right side
	void Recovery(Node*); //recovery after input

public:

	Key* Get_Keys(); //return all keys
	Value* Get_Values(); //return values
	Value Find_Element(Key); //find element by key
	void Insert(Key, Value); //add element with key and value
	void Remove(Key); //remove element by key
	void Clear(); //clear all
	void Print(); //print in console
	bool Get_Color(Key);
	RBTree()
	{
		size = 0;
		zero = new Node(0, 0, nullptr, nullptr, nullptr, 1);
		root = zero;
	}
	~RBTree()
	{
		Clear();
		delete root;
	}
	int Size()
	{
		return size;
	}
};
template<typename Key, typename Value>
void insert(Key insKey, Value insValue) // add element with key and value
{
	if (count == 0) // add root
	{
		root = new Node(insKey, insValue, false, nil, nil, nil);
	}
	else {
		Node* newNode = new Node(insKey, insValue, true, nil, nil, nil); // new red element with key and value
		Node* parent = root;
		Node* leaf = parent;
		while (parent != nil)  //looking for a sheet
		{
			leaf = parent;
			if (parent->key < newNode->key)
				parent = parent->right;
			else
				parent = parent->left;
		}
		newNode->parent = leaf; // add new element 
		if (leaf->key < newNode->key)
			leaf->right = newNode;
		else
			leaf->left = newNode;
	}
	count++;
};
template<typename Key, typename Value>
void find(Key finKey) // item search by key
{
	Node* node = root;
	while (node->key != finKey)// find key
	{
		if ((node == nil) || (node == nullptr))
		{
			throw out_of_range("Element not found");
		}
		if (node->key < finKey)
			node = node->right;
		else
			node = node->left;
	}
	return node->value;
};
template<typename Key, typename Value>
void RBTree<Key, Value>::Recovery(Node* newNode) {
	Node* parent, * Grand_Parent;
	while (newNode->parent->color == 0)
	{
		parent = newNode->parent;
		Grand_Parent = parent->parent;
		if (Grand_Parent->left == parent)
		{
			if (Grand_Parent->right->color == 0)
			{
				Grand_Parent->right->color = 1;
				Grand_Parent->left->color = 1;
				Grand_Parent->color = 0;
				newNode = Grand_Parent;
			}
			else
			{
				if (parent->right == newNode)
				{
					newNode = parent;
					Left_Rotate(newNode);
				}
				newNode->parent->color = 1;
				newNode->parent->parent->color = 0;
				Right_Rotate(newNode->parent->parent);
			}
		}
		else
		{
			if (Grand_Parent->left->color == 0)
			{
				Grand_Parent->right->color = 1;
				Grand_Parent->left->color = 1;
				Grand_Parent->color = 0;
				newNode = Grand_Parent;
			}
			else
			{
				if (parent->left == newNode)
				{
					newNode = parent;
					Right_Rotate(newNode);
				}
				newNode->parent->color = 1;
				newNode->parent->parent->color = 0;
				Left_Rotate(newNode->parent->parent);
			}
		}
	}
	root->color = 1;
}
template<typename Key, typename Value>
void RBTree<Key, Value>::Insert(Key key, Value value)
{
	Node* current = root, * parent;
	bool Right_Move;
	size++;
	if (root == zero)//Tree is empty 
	{
		root = new Node(key, value, zero, zero, zero, 1);
		return;
	}
	parent = current;
	while (current != zero)
	{
		parent = current;
		if (key > current->key) //right
		{
			current = current->right; Right_Move = true;
		} //
		else {//left
			current = current->left; Right_Move = false;
		}
	}
	if (Right_Move)
	{
		parent->right = new Node(key, value, zero, zero, parent, 0);
		Recovery(parent->right);
	}
	else {
		parent->left = new Node(key, value, zero, zero, parent, 0);
		Recovery(parent->left);
	}
}

template<typename Key, typename Value>
void RBTree<Key, Value>::Left_Rotate(Node* CurX) {
	Node* CurY = CurX->right;
	if (CurX->right == zero)
		return;
	if (CurY->left != zero)
	{
		CurX->right = CurY->left;
		CurY->left->parent = CurX;
	}
	else CurX->right = zero;

	if (CurY != zero)
		CurY->parent = CurX->parent;
	if (CurX->parent != zero)
	{
		if (CurX == CurX->parent->left)
			CurX->parent->left = CurY;
		else
			CurX->parent->right = CurY;
	}
	else
	{
		CurY->parent = zero;
		root = CurY;
	}
	CurY->left = CurX;
	if (CurX != zero)
		CurX->parent = CurY;
}
template<typename Key, typename Value>
void RBTree<Key, Value>::Right_Rotate(Node* CurX) {
	Node* CurY = CurX->left;
	CurX->left = CurY->right;
	if (CurY->right != zero)
		CurY->right->parent = CurX;
	if (CurY != zero)
		CurY->parent = CurX->parent;
	if (CurX->parent != zero) {
		if (CurX == CurX->parent->right)
			CurX->parent->right = CurY;
		else
			CurX->parent->left = CurY;
	}
	else
	{
		root = CurY;
	}
	CurY->right = CurX;
	if (CurX != zero)
		CurX->parent = CurY;
}

template<typename Key, typename Value>
void RBTree<Key, Value>::Remove(Key key)
{
	if (root == zero)
		cout << "Tree is empty";
	Node* Node_To_Delete = root;
	Node* x, * min;
	bool Color = Node_To_Delete->color;
	while (Node_To_Delete->key != key)
	{
		if (key > Node_To_Delete->key)
			Node_To_Delete = Node_To_Delete->right;
		else Node_To_Delete = Node_To_Delete->left;
		if (Node_To_Delete == zero)
			cout << "No such element";
	}
	if (Node_To_Delete->left == zero)
	{
		x = Node_To_Delete->right;
		if (Node_To_Delete->parent == zero)
			root = x;
		else if (Node_To_Delete->parent->left == Node_To_Delete)
			Node_To_Delete->parent->left = x;
		else Node_To_Delete->parent->right = x;
		x->parent = Node_To_Delete->parent;
	}
	else
		if (Node_To_Delete->right == zero)
		{
			x = Node_To_Delete->left;
			if (Node_To_Delete->parent == zero) root = x;
			else
				if (Node_To_Delete->parent->left == Node_To_Delete)
					Node_To_Delete->parent->left = x;
				else Node_To_Delete->parent->right = x;
			x->parent = Node_To_Delete->parent;
		}
		else
		{
			Node* temp = Node_To_Delete;
			min = Node_To_Delete->right;
			while (min->left != zero)
				min = min->left;
			Color = min->color;
			Node_To_Delete = min;
			x = Node_To_Delete->right;
			if (Node_To_Delete->parent == temp)
				x->parent = Node_To_Delete;
			else
			{
				if (Node_To_Delete->parent == zero) {
					root = x;
					Node_To_Delete->right->parent = zero;
				}
				else
					if (Node_To_Delete->parent->right == Node_To_Delete)
						Node_To_Delete->parent->right = x;
					else Node_To_Delete->parent->left = x;
				x->parent = Node_To_Delete->parent;
				Node_To_Delete->right = temp->right;
				Node_To_Delete->right->parent = Node_To_Delete;
			}
			if (temp->parent == zero)
				root = Node_To_Delete;
			else
				if (temp == temp->parent->left)
					temp->parent->left = Node_To_Delete;
				else temp->parent->right = Node_To_Delete;
			Node_To_Delete->parent = temp->parent;
			Node_To_Delete->left = temp->left;
			Node_To_Delete->left->parent = Node_To_Delete;
			Node_To_Delete->color = temp->color;
		}
	size--;
}
template<typename Key, typename Value>
Value RBTree<Key, Value>::Find_Element(Key findKey)
{
	Node* current = root;
	while (current->key != findKey) // find key to remove
	{
		if (findKey > current->key)
			current = current->right;
		else current = current->left;
		if (current == zero)
			cout << "No such element";
	}
	return current->value;
}
template<typename Key, typename Value>
Key* RBTree<Key, Value>::Get_Keys()
{
	Key* Array = new Key[size];
	int i = 0;
	DFT_Iterator iter(root, zero);
	while (iter.Next())
	{
		Array[i] = iter.next()->key;
		i++;
	}
	return Array;
}
template<typename Key, typename Value>
Value* RBTree<Key, Value>::Get_Values() {
	Value* arr = new Value[size]; int i = 0;
	DFT_Iterator iter(root, zero);
	while (iter.Next())
	{
		arr[i] = iter.next()->value; i++;
	}
	return arr;
}

template<typename Key, typename Value>
void RBTree<Key, Value>::Print() {
	DFT_Iterator iter(root, zero);
	Node* current;
	while (iter.Next())
	{
		current = iter.next();
		cout << "\nKey:" << current->key;
		cout << "Elements:" << current->left->key << " " << current->right->key;
	}
}

template<typename Key, typename Value>
bool RBTree<Key, Value>::Get_Color(Key findKey) {
	Node* current = root;
	while (current->key != findKey) {
		if (findKey > current->key)
			current = current->right;
		else current = current->left;
		if (current == zero)
			cout << "No such element";
	}
	return current->color;
}
template<typename Key, typename Value>
void RBTree<Key, Value>::Clear()
{
	while (root != zero) {
		remove(root->key);
		cout << endl;
		Print();
	}
}