#pragma once

template <typename D> class SLinkedList
{
private:
	class Node
	{
	public:
		Node*	pFoward;
		D		Data;

	public:
		Node()
		{
			this->pFoward	= nullptr;
			this->Data		= NULL;
		}
		Node(Node* pFwrd, D Data)
		{
			this->pFoward	= pFwrd;
			this->Data		= Data;
		}
	};

	

private:
	Node*			pHead		= nullptr;
	unsigned int	uiLength	= NULL;



public:
	~SLinkedList();

	unsigned int	Length();
	D				Get(unsigned int uiIndex);

	bool			Insert(unsigned int uiIndex, D Data);
	bool			Append(D Data);
	bool			Prepend(D Data);

	D				Remove(unsigned int uiIndex);
	D				RemoveFirst();
	D				RemoveLast();

public:
	SLinkedList<D>& operator+=(D Data);
	D				operator[](unsigned int iIndex);
};



//Nonstatic
template <typename D> SLinkedList<D>::~SLinkedList()
{
	if (this->uiLength == 0)
	{
		return;
	}

	Node* Traversal = this->pHead;
	while (Traversal->pFoward != nullptr)
	{
		Node* Next	= Traversal->pFoward;
		delete[] Traversal;
		Traversal	= Next;
	}

	delete[] Traversal;
}

template <typename D> unsigned int SLinkedList<D>::Length()
{
	return this->uiLength;
}

template <typename D> D SLinkedList<D>::Get(unsigned int uiIndex)
{
	if (uiIndex >= this->Length())
	{
		return NULL;
	}

	Node* pTraversal = this->pHead;
	for (int i = 0; i < uiIndex; i++)
	{
		pTraversal = pTraversal->pFoward;
	}

	return pTraversal->Data;
}

template <typename D> bool SLinkedList<D>::Insert(unsigned int uiIndex, D Data)
{
	if (uiIndex > this->uiLength)
	{
		return false;
	}

	Node* pNewNode = new Node(nullptr, Data);
	if (!pNewNode)
	{
		return false;
	}

	if (uiIndex == 0)
	{
		pNewNode->pFoward	= this->pHead;
		this->pHead			= pNewNode;
	}
	else
	{
		Node* pTraversal = this->pHead;
		for (int i = 0; i < (uiIndex - 1); i++)
		{
			pTraversal = pTraversal->pFoward;
		}

		pNewNode->pFoward	= pTraversal->pFoward;
		pTraversal->pFoward = pNewNode;
	}

	this->uiLength++;
	return true;
}

template <typename D> bool SLinkedList<D>::Append(D Data)
{
	return (this->Insert(this->uiLength, Data));
}

template <typename D> bool SLinkedList<D>::Prepend(D Data)
{
	return (this->Insert(0, Data));
}

template <typename D> D SLinkedList<D>::Remove(unsigned int uiIndex)
{
	if (uiIndex >= this->uiLength)
	{
		return NULL;
	}

	if (uiIndex == 0)
	{
		Node* pRemoved	= this->pHead;
		this->pHead		= this->pHead->pFoward;
		D Removed		= pRemoved->Data;
		delete[] pRemoved;

		this->uiLength--;

		return Removed;
	}
	else
	{
		Node* pTraversal = this->pHead;
		for (int i = 0; i < (uiIndex - 1); i++)
		{
			pTraversal = pTraversal->pFoward;
		}

		Node* pRemoved = pTraversal->pFoward;
		pTraversal->pFoward = pTraversal->pFoward->pFoward;
		D Removed = pRemoved->Data;
		delete[] pRemoved;

		this->uiLength--;

		return Removed;
	}
}

template <typename D> D SLinkedList<D>::RemoveFirst()
{
	return (this->Remove(0));
}

template <typename D> D SLinkedList<D>::RemoveLast()
{
	return (this->Remove(this->uiLength - 1));
}



//Overloading
template <typename D> SLinkedList<D>& SLinkedList<D>::operator+=(D Data)
{
	this->Append(Data);
	return *this;
}

template <typename D> D SLinkedList<D>::operator[](unsigned int uiIndex)
{
	return (this->Get(uiIndex));
}