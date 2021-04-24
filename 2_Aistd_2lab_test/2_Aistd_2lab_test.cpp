#include "pch.h"
#include "CppUnitTest.h"
#include "..//Huffman.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace My2Aistd2labtest
{
	TEST_CLASS(lab2test)
	{
	public:
		bool* code;
		char* decode;
		TEST_METHOD(test_1)
		{
			
			int codeSize;
			int decodeSize;
			char str[] = { 'I',' ','l','o','v','e',' ','p','i','z','z','a'};
			Huffman Code(str);
			code = Code.Code(codeSize);
			decode = Code.Decode(decodeSize);
			for (size_t i = 0; i < decodeSize; i++)
			{
				Assert::AreEqual(str[i], decode[i]);
			}
		}
	};
}
