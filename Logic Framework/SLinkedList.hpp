#pragma once

template <typename DataType> class SLinkedList
{
private:
	class Node
	{
	public:
		Node*		pFLink;
		DataType	Data;

		Node()
		{
			this->pFLink	= nullptr;
			this->Data		= NULL;
		}
		Node(Node* pFLink, const DataType& Info)
			: Data(Info)
		{
			this->pFLink	= pFLink;
		}
	};

private:
	Node*	pHead;
	size_t	ullLength;


public:
	//Instantiation
	SLinkedList	();
	~SLinkedList();


	//Utility
	DataType	Get			(size_t ullIndex);
	size_t		Length		();
	bool		Lookup		(const DataType& Data);

	bool		Insert		(size_t ullIndex, const DataType& Data);	
	bool		Append		(const DataType& Data);
	bool		Prepend		(const DataType& Data); 

	DataType	Remove		(size_t ullIndex);
	DataType	RemoveFirst	();
	DataType	RemoveLast	();
};

//Instantiation
template <typename DataType> SLinkedList<DataType>::SLinkedList()
{
	this->pHead		= nullptr;
	this->ullLength = NULL;
}

template <typename DataType> SLinkedList<DataType>::~SLinkedList()
{
	if (!this->ullLength)
	{
		return;
	}

	Node* pTraversal = this->pHead;
	while (pTraversal->pFLink != nullptr)
	{
		Node* pNext = pTraversal->pFLink;
		delete pTraversal;
		pTraversal	= pNext;
	}
	delete pTraversal;
}



//Utility
template <typename DataType> DataType SLinkedList<DataType>::Get(size_t ullIndex)		//Don't reference return...
{
	if (ullIndex >= this->ullLength)
	{
		return {};
	}

	Node* pTraversal = this->pHead;
	for (size_t i = 0; i < ullIndex; i++)
	{
		pTraversal = pTraversal->pFLink;
	}

	return pTraversal->Data;
}

template <typename DataType> size_t SLinkedList<DataType>::Length()
{
	return this->ullLength;
}

template <typename DataType> bool SLinkedList<DataType>::Lookup(const DataType& Data)
{
	Node* pTraversal = this->pHead;

	for (size_t i = 0; i < this->ullLength; i++)
	{
		if (pTraversal->Data == Data)
		{
			return true;
		}

		pTraversal = pTraversal->pFLink;
	}

	return false;
}

template <typename DataType> bool SLinkedList<DataType>::Insert(size_t ullIndex, const DataType& Data)
{
	if (ullIndex > this->ullLength)
	{
		return false;
	}

	Node* pNewNode = new Node(nullptr, Data);
	if (!pNewNode)
	{
		return false;
	}

	if (ullIndex == 0)
	{
		pNewNode->pFLink	= this->pHead;
		this->pHead			= pNewNode;
	}
	else
	{
		Node* pTraversal = this->pHead;
		for (size_t i = 0; i < (ullIndex - 1); i++)
		{
			pTraversal = pTraversal->pFLink;
		}

		pNewNode->pFLink	= pTraversal->pFLink;
		pTraversal->pFLink	= pNewNode;
	}

	this->ullLength++;

	return true;
}

template <typename DataType> bool SLinkedList<DataType>::Append(const DataType& Data)
{
	return (this->Insert(this->ullLength, Data));
}

template <typename DataType> bool SLinkedList<DataType>::Prepend(const DataType& Data)
{
	return (this->Insert(0, Data));
}

template <typename DataType> DataType SLinkedList<DataType>::Remove(size_t ullIndex)
{
	if (ullIndex >= this->ullLength)
	{
		return NULL;
	}

	DataType Removed;
	if (ullIndex == 0)
	{
		Removed			= this->pHead->Data;
		Node* pRemoved	= this->pHead;
		this->pHead		= this->pHead->pFLink;
		delete pRemoved;
	}
	else
	{
		Node* pTraversal = this->pHead;
		for (int i = 0; i < (ullIndex - 1); i++)
		{
			pTraversal = pTraversal->pFLink;
		}
		Removed				= pTraversal->pFLink->Data;
		Node* pRemoved		= pTraversal->pFLink;
		pTraversal->pFLink	= pTraversal->pFLink->pFLink;
		delete pRemoved;
	}

	this->ullLength--;
	return Removed;
}

template <typename DataType> DataType SLinkedList<DataType>::RemoveFirst()
{
	return (this->Remove(0));
}

template <typename DataType> DataType SLinkedList<DataType>::RemoveLast()
{
	return (this->Remove(this->ullLength - 1));
}