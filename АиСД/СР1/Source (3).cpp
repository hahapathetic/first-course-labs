#include <iostream>

class DictionaryList
{
public:
	DictionaryList():
		head_(nullptr)
	{}
	~DictionaryList()
	{
		while (head_)
		{
			Node* curNode = head_;
			head_ = head_->ptrNext_;
			delete curNode;
		}
	}	
	DictionaryList(DictionaryList& list) = delete;
	DictionaryList(DictionaryList&& list) = delete;
	DictionaryList& operator= (DictionaryList& list) = delete;
	DictionaryList& operator= (DictionaryList&& list) = delete;

	void Insert(int data)
	{
		if (head_ == nullptr)
		{
			head_ = new Node(data);
		}
		else
		{
			Node* curNode = new Node(data);
			curNode->ptrNext_ = head_;
			head_->ptrPrev_ = curNode;
			head_ = curNode;
		}
	}
	void Print()
	{
		std::cout << "\nCписок: \n";
		if (head_ == nullptr)
			std::cout << "Пустой список!\n";
		else
		{
			Node* curNode = head_;
			while (curNode)
			{
				std::cout << curNode->data_ << " ";
				curNode = curNode->ptrNext_;
			}
			std::cout << std::endl;
		}
	}
	

	void removeLess()
	{
		if (head_ != nullptr )
			if (head_->ptrNext_ != nullptr) 
			{
				{
					Node* curNode = head_;
					Node* nextCur = nullptr;
					int maxData = head_->data_;
					while (curNode)
					{
						if (curNode->data_ >= maxData)
						{
							maxData = curNode->data_;
							curNode = curNode->ptrNext_;
						}
						else
						{
							curNode->ptrPrev_->ptrNext_ = curNode->ptrNext_;
							if (curNode->ptrNext_ != nullptr)
							{
								curNode->ptrNext_->ptrPrev_ = curNode->ptrPrev_;
							}
							nextCur = curNode->ptrNext_;
							delete curNode;
							curNode = nextCur;
						}
					}
				}
			}
	}
private:
	struct Node
	{
	public:
		Node* ptrNext_;
		Node* ptrPrev_;
		int data_;
		Node(const int& data, Node* ptrNext = nullptr, Node* ptrPrev = nullptr) :
			data_(data),
			ptrNext_(ptrNext),
			ptrPrev_(ptrPrev)
		{};
	};
	Node* head_;
};

int main()
{
	setlocale(LC_ALL, "ru");
	DictionaryList dc1;
	DictionaryList dc2;
	dc1.Insert(1);
	dc1.Insert(10);
	dc1.Insert(3);
	dc1.Insert(1);
	dc1.Insert(5);
	dc1.Insert(9);
	dc1.Insert(2);

	dc1.Print();

	dc2.removeLess();

	dc1.removeLess();

	dc1.Print();

	dc2.Print();
}

