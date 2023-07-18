#ifndef DICTIONARYLIST_H
#define DICTIONARYLIST_H
#include <iostream>
#include <string>

template <class keyT>
class DictionaryList
{
public:
	DictionaryList() :
		head_(nullptr)
	{};

	DictionaryList(DictionaryList& list) = delete;

	DictionaryList(DictionaryList&& list) noexcept;
	
	~DictionaryList();

	DictionaryList& operator= (DictionaryList&& list) noexcept
	{
		if (this == &list)
			return *this;
		else
		{
			while (head_)
			{
				Node* curNode = head_;
				head_ = head_->ptrNext_;
				delete curNode;
			}
			head_ = list.head_;
			list.head_ = nullptr;
		}
		return *this;
	}

	DictionaryList& operator= (DictionaryList& list) = delete;

	template <class keyT> friend std::ostream& operator<<(std::ostream& stream, const DictionaryList<keyT>& list);

	bool Search(const keyT& data);

	bool Insert(const keyT& data);

	bool Delete(const keyT& data);

	bool Merge(DictionaryList<keyT>& list2);

	bool DeleteDict(const DictionaryList<keyT>& list2);

	template <typename keyT> friend DictionaryList<keyT> getIntersection(const DictionaryList<keyT>& list1, const DictionaryList<keyT>& list2);

private:

	struct Node
	{
	public:
		Node* ptrNext_;
		keyT data_;
		Node(Node* ptrNext = nullptr, const keyT& data = keyT()) :
			ptrNext_(ptrNext),
			data_(data)
		{};
	};

	Node* head_;
};


template <class keyT>
DictionaryList <keyT>::DictionaryList(DictionaryList&& list) noexcept :
	head_(list.head_)
{
	list.head_ = nullptr;
}

template <class keyT>
DictionaryList <keyT>::~DictionaryList()
{
	while (head_)
	{
		Node* curNode = head_;
		head_ = head_->ptrNext_;
		delete curNode;
	}
}

template <class keyT>
bool DictionaryList <keyT>::Search(const keyT& data)
{
	bool flag = false;
	if(head_ != nullptr)
	{
		Node* curNode = head_;
		while (curNode)
		{
			if (curNode->data_ == data)
			{
				flag = true;
				break;
			}
			curNode = curNode->ptrNext_;
		}
	}
	return flag;
}

template <class keyT>
bool DictionaryList <keyT>::Insert(const keyT& data)
{
	if (this->Search(data))
	{
		return false;
	}
	else
	{
		if (head_ == nullptr)
		{
			Node* newNode = new Node(nullptr, data);
			head_ = newNode;
		}
		else if (head_->ptrNext_ == nullptr)
		{
			Node* newNode = new Node(nullptr, data);

			if (head_->data_ < data)
			{
				head_->ptrNext_ = newNode;
				newNode->ptrNext_ = nullptr;
			}
			else
			{
				newNode->ptrNext_ = head_;
				head_ = newNode;
			}
		}
		else
		{
			Node* newNode = new Node(nullptr, data);
			Node* prevNode = head_;
			Node* nextNode = head_->ptrNext_;
			if (data < prevNode->data_)
			{
				newNode->ptrNext_ = prevNode;
				head_ = newNode;
			}
			else
			{
				bool changeFlag = false;
				while (nextNode != nullptr && !changeFlag)
				{
					if (data < nextNode->data_)
					{
						prevNode->ptrNext_ = newNode;
						newNode->ptrNext_ = nextNode;
						changeFlag = true;
					}
					prevNode = nextNode;
					nextNode = nextNode->ptrNext_;
				}
				if (!changeFlag)
				{
					prevNode->ptrNext_ = newNode;
					newNode->ptrNext_ = nullptr;
				}
			}
		}
		return true;
	}
}

template <class keyT>
bool DictionaryList <keyT>::Delete(const keyT& data)
{
	bool check = false;
	if (head_ != nullptr)
	{
		if (data >= head_->data_)
		{
			if (head_->data_ == data)
			{
				Node* curNode = head_;
				head_ = head_->ptrNext_;
				delete curNode;
				check = true;
			}
			else
			{
				Node* prevNode = head_;
				Node* nextNode = head_->ptrNext_;

				while (nextNode != nullptr && check != true)
				{
					if (data == nextNode->data_)
					{
						prevNode->ptrNext_ = nextNode->ptrNext_;
						delete nextNode;
						check = true;
					}
					if (!check)
					{
						prevNode = prevNode->ptrNext_;
						nextNode = nextNode->ptrNext_;
					}
					else
					{
						break;
					}
				}

			}
		}
	}
	return check;
}

template <class keyT>
bool DictionaryList <keyT>::Merge(DictionaryList<keyT>& list2)
{
	bool merged = true;

	if (list2.head_ != nullptr )
	{
		if (head_ == nullptr)
		{
			head_ = list2.head_;
			list2.head_ = nullptr;
		}
		else
		{
			Node* curNode = list2.head_;
			Node* prevNode = head_;
			Node* nextNode = head_->ptrNext_;
			if (head_->data_ > curNode->data_)
			{
				list2.head_ = list2.head_->ptrNext_;
				curNode->ptrNext_ = head_;
				head_ = curNode;
				curNode = list2.head_;
				prevNode = head_;
				nextNode = head_->ptrNext_;
			}
			while (curNode != nullptr && nextNode != nullptr)
			{
				if (prevNode->data_ == curNode->data_)
				{
					list2.head_ = list2.head_->ptrNext_;
					delete curNode;

					curNode = list2.head_;
				}
				else if (prevNode->data_ < curNode->data_ && nextNode->data_ > curNode->data_)
				{
					list2.head_ = list2.head_->ptrNext_;
					prevNode->ptrNext_ = curNode;
					curNode->ptrNext_ = nextNode;
					prevNode = curNode; //вставили узел и 1 узел = вставленный
					curNode = list2.head_;
				}
				else
				{
					prevNode = nextNode;
					nextNode = nextNode->ptrNext_;
				}
			}
			if (curNode != nullptr)
			{
				if (curNode->data_ == prevNode->data_)
				{
					list2.head_ = list2.head_->ptrNext_;
					delete curNode;
					curNode = list2.head_;
				}
				prevNode->ptrNext_ = list2.head_;
				list2.head_ = nullptr;
			}
		}
	}
	return merged;
}

template <class keyT>
bool DictionaryList <keyT>::DeleteDict(const DictionaryList<keyT>& list2)
{
	bool deleted = false;
	if (head_ != nullptr && list2.head_ != nullptr)
	{
		Node* curNode = list2.head_;
		Node* prevNode = head_;
		Node* nextNode = head_->ptrNext_;
		while (curNode != nullptr && prevNode != nullptr && (curNode->data_ <= prevNode->data_))
		{
			if (curNode->data_ == head_->data_)
			{
				head_ = prevNode->ptrNext_;
				delete prevNode;
				deleted = true;
				prevNode = head_;
				nextNode = nextNode->ptrNext_;
				curNode = curNode->ptrNext_;
			}
			else
				curNode = curNode->ptrNext_;
		}
		while (curNode != nullptr && nextNode != nullptr)
		{
			if (curNode->data_ < nextNode->data_)
				curNode = curNode->ptrNext_;
			else if (curNode->data_ > nextNode->data_)
			{
				prevNode = prevNode->ptrNext_;
				nextNode = nextNode->ptrNext_;
			}
			else
			{
				prevNode->ptrNext_ = nextNode->ptrNext_;
				delete nextNode;
				deleted = true;
				nextNode = prevNode->ptrNext_;
			}

		}
	}
	return deleted;
}

template <typename keyT>
DictionaryList<keyT> getIntersection(const DictionaryList<keyT>& list1, const DictionaryList<keyT>& list2)
{
	DictionaryList<keyT> intersected;
	typename DictionaryList<keyT>::Node* curNode = intersected.head_;
	typename DictionaryList<keyT>::Node* curNode1 = list1.head_;
	typename DictionaryList<keyT>::Node* curNode2 = list2.head_;

	while (curNode1 != nullptr && curNode2 != nullptr)
	{
		if (curNode1->data_ > curNode2->data_)
			curNode2 = curNode2->ptrNext_;
		else if (curNode1->data_ < curNode2->data_)
			curNode1 = curNode1->ptrNext_;
		else
		{
			if (curNode == nullptr)
			{
				intersected.head_ = new typename DictionaryList<keyT>::Node(nullptr, curNode1->data_);
				curNode = intersected.head_;
				curNode2 = curNode2->ptrNext_;
				curNode1 = curNode1->ptrNext_;
			}
			else
			{
				curNode->ptrNext_ = new typename DictionaryList<keyT>::Node(nullptr, curNode1->data_);
				curNode = curNode->ptrNext_;
				curNode2 = curNode2->ptrNext_;
				curNode1 = curNode1->ptrNext_;
			}
		}
	}
	return intersected;
}

template <class keyT>
std::ostream& operator <<(std::ostream& stream, const DictionaryList<keyT>& list)
{
	stream << "\nCписок: \n";
	if (!list.head_)
		stream << "Пустой список!\n";

	else
	{
		typename DictionaryList<keyT>::Node* curNode = list.head_;
		while (curNode)
		{
			stream << curNode->data_ << " ";
			curNode = curNode->ptrNext_;
		}
		stream << std::endl;
	}
	return stream;
}

#endif // !DICTIONARYLIST_H

