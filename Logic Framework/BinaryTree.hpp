#pragma once

#define NODE_OPERATOR	0x1000
#define NODE_VARIABLE	0x2000
#define NODE_UNDEFINED	0x3000

template <typename DataType> class Tree
{
private:
	class Node
	{
	public:
		unsigned char bTypeFlag;
		
		DataType	Data;
		Node*		pLeft;
		Node*		pRight;

		Node()
		{
			this->bTypeFlag = NODE_UNDEFINE;
			this->Data		= NULL;
			this->pLeft		= this->pRight = nullptr;
		}
		Node(unsigned char bTypeFlag, DataType paramData, Node* pLeft, Node* pRight)
			: Data(paramData)
		{
			this->pLeft		= pLeft;
			this->pRight	= pRight;
			this->bTypeFlag = bTypeFlag;
		}
	};

public:
};