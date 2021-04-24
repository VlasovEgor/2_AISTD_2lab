#pragma once
#include "Stack.h"
#include "Red_Black_Tree.h"
#include "Queue.h"
#include "Queue.cpp"
class Huffman
{
private:
	class Node
	{
	public:
		Node(int freq = 0, Node* left = nullptr, Node* right = nullptr, char letter = '\n')
		{
			freq = freq;
			letter = letter;
			left = left;
			right = right;
			parent = nullptr;
		};
		~Node() {};
		int freq;
		char letter;
		Node* left;
		Node* right;
		Node* parent;
	};
	void Cop_Arr(bool* copy, bool* str, int size) 
	{
		for (size_t i = 0; i < size; i++)
			copy[i] = str[i];
	};
	Node* root;
	char* str;
	size_t sizeStr;
	bool* readyCode;
	size_t sizeReadyCode;
	struct strArr
	{
		bool* str = NULL;
		int size = 0;
	};
	RBTree<char, strArr*> codeLetter;
public:
	~Huffman()
	{
	}
	Huffman(char* _str)
	{
		codeLetter = RBTree<char, strArr*>();
		str = _str; //original string to code
		sizeStr = 0;  //line size
		for (size_t i = 0; str[i] != '\n'; i++)
			sizeStr++;
		if (sizeStr > 1)
		{
			Priority<Node*> pq;
			Node* BN_1;
			Node* BN_2;
			int chars[256] = { 0 };
			for (int i = 0; str[i] != '\n'; i++)  //count the number letters with repeat
				chars[str[i] + 128]++;
			int Cl = 0;
			cout << "Frequency: " << endl;
			for (int i = 0; i < 256; i++)
				if (chars[i] != 0)
				{
					Cl++;
					cout << (char)(i - 128) << " : " << chars[i] << endl;
					BN_1 = new Node(chars[i], nullptr, nullptr, (i - 128));
					pq.push_el(BN_1, chars[i]);
				}
			int BI;
			BI = pq.tail_prior();
			BN_1 = pq.pop();
			for (size_t i = 0; (i < Cl) && (!pq.isEmpty()); i++)
			{
				BI += pq.tail_prior();
				BN_2 = pq.pop();
				root = new Node(BI, BN_1, BN_2); //create a parent node for two with minimum priority
				BN_1->parent = root;
				BN_2->parent = root;
				pq.push_el(root, root->freq);  //return it to the queue
				BI = pq.tail_prior();
				BN_1 = pq.pop();
			}
			bool* bufStr = new bool[Cl / 2 + 1];
			memset(bufStr, 0, Cl / 2 + 1);
			size_t indexStr = 0;
			unsigned int bufCodeLetter = 0;
			Stack<Node*> dft;
			if (root->right != nullptr)
			{
				dft.push_el(root->right);
			}
			BN_1 = root;
			strArr* bufStrArr = new strArr;
			cout << "Code: " << endl;
			while (!dft.isEmpty())
			{
				while (BN_1->left != nullptr)  //go down to the sheet
				{
					bufStr[indexStr] = 0;
					indexStr++;
					BN_1 = BN_1->left;
					if (BN_1->right != nullptr) //add the right child to the Stack
					{
						dft.push_el(BN_1->right);
					}
				}
				bufStrArr = new strArr;
				bufStrArr->str = new bool[indexStr];
				bufStrArr->size = indexStr;
				Cop_Arr(bufStrArr->str, bufStr, indexStr);
				cout << BN_1->letter << " : ";
				for (size_t i = 0; i < indexStr; i++)
				{
					cout << bufStrArr->str[i];
				}
				cout << endl;
				codeLetter.insert(BN_1->letter, bufStrArr);  //Add correspondence between letter and code
				indexStr--;
				while ((BN_1->parent != nullptr) && (BN_1->parent->right != dft.get_last())) //go up
				{
					BN_1 = BN_1->parent;
					indexStr--;
				}
				BN_1 = dft.pop();
				if (BN_1->right != nullptr)
				{
					dft.push_el(BN_1->right);
				}
				bufStr[indexStr] = 1;
				indexStr++;
			}
			bufStrArr = new strArr;
			bufStrArr->size = indexStr;
			bufStrArr->str = new bool[indexStr];
			Cop_Arr(bufStrArr->str, bufStr, indexStr);
			cout << BN_1->letter << " : ";
			for (size_t i = 0; i < indexStr; i++)
			{
				cout << bufStrArr->str[i];
			}
			cout << endl;
			codeLetter.insert(BN_1->letter, bufStrArr);
			readyCode = NULL;
			sizeReadyCode = 0;
			delete bufStr;
		}
		else {
			cout << "Frequency: " << str[0] << " " << 1 << endl;
			cout << "Code: " << str[0] << " " << 0 << endl;
			root = new Node(1, nullptr, nullptr, str[0]);
			sizeReadyCode = 0;
			readyCode = NULL;
			strArr* bufStrArr = new strArr;
			bufStrArr->str = new bool[1];
			bufStrArr->str[0] = false;
			bufStrArr->size = 1;
			codeLetter.insert(str[0], bufStrArr);
		}
	}
	bool* Code(int& codeSize)
	{
		bool* copyStr;
		codeSize = 0;
		for (int i = 0; str[i] != '\n'; i++) {
			codeSize += codeLetter.find(str[i])->size;
		}
		sizeReadyCode = codeSize;
		readyCode = new bool[codeSize];
		size_t indexStr = 0;
		for (int i = 0; str[i] != '\n'; i++) {
			copyStr = codeLetter.find(str[i])->str;  //we find a match in the tree
			for (size_t j = 0; j < codeLetter.find(str[i])->size; j++) {
				readyCode[indexStr] = copyStr[j];
				indexStr++;
			}
		}
		return readyCode;
	}
	char* Decode(int& sizeStrDecode) {
		char* decodeStr = new char[sizeStr + 1];
		sizeStrDecode = sizeStr;
		if (sizeStr == 1)
		{
			decodeStr[0] = root->letter;
			decodeStr[0] = '\n';
		}
		else 
		{
			size_t indexCode = 0;
			Node* curNode = root;
			size_t indexDecode = 0;
			while (indexCode < sizeReadyCode)
			{
				if ((readyCode[indexCode] == 0) && (curNode->left != nullptr))  //go left
				{
					curNode = curNode->left;
					indexCode++;
				}
				else if ((readyCode[indexCode] == 1) && (curNode->right != nullptr)) 
				{  //go right
					curNode = curNode->right;
					indexCode++;
				}
				else { //came to the desired node
					decodeStr[indexDecode] = curNode->letter;
					indexDecode++;
					curNode = root;
				}
			}
			decodeStr[indexDecode] = curNode->letter;
			decodeStr[indexDecode + 1] = '\n';
		}
		return decodeStr;
	}
};