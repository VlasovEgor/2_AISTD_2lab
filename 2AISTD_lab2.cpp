#include <iostream>
#include "Huffman.h"

int main()
{
    int Char_Size = 100;
    char* str = new char[Char_Size];
    int size=0;
    char symbol;
    do
    {
        cin >> noskipws >> symbol;
        str[size] = symbol;
        size++;
    } while ((symbol != '.') && ((size + 1) < Char_Size));
    double cf = 1.0 * 8 * size * sizeof(char);
    Huffman Code(str);
    int sizeC;
    bool* code = Code.Code(size);
    char* decode = Code.Decode(sizeC);
    for (size_t i = 0; i < size; i++)
    {
        cout << code[i];
    }
    cout << endl;
    cf = cf / (1 * size);
    cout << "Coefficient : " << cf << endl;
    for (size_t i = 0; i < sizeC; i++)
    {
        cout << decode[i];
    }
}