#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <ostream>
#include "StackArray.h"
#include "QueueArray.h"

template <class T>
class BinarySearchTree
{
public:
	BinarySearchTree();

	BinarySearchTree(const BinarySearchTree<T>& scr) = delete;
	BinarySearchTree(BinarySearchTree<T>&& scr) noexcept;

	BinarySearchTree <T>& operator= (const BinarySearchTree <T>& src) = delete;
	BinarySearchTree <T>& operator= (BinarySearchTree <T>&& src) noexcept;

	virtual ~BinarySearchTree();

	// 1.1 Функция поиска по ключу в бинарном дереве поиска
	bool iterativeSearch(const T& key) const;
	// 2 Вставка нового элемента в дерево: true, если элемент добавлен; 
	// false, если элемент уже был
	bool insert(const T& key);
	// 3.1 Удаление элемента из дерева, не нарушающее порядка элементов
	// true, если элемент удален; false, если элемента не было
	bool deleteKey(const T& key);
	// 4.1 Печать строкового изображения дерева в выходной поток out,
	// использовать скобки, чтобы показать структуру дерева
	void print(std::ostream& out) const;
	// 5.1 Определение количества узлов дерева
	int getCount() const;
	// 6.1 Определение высоты дерева
	int getHeight() const;
	// 7 Инфиксный обход дерева (итеративный) 
	void iterativeInorderWalk(std::ostream& out) const;
	// 8.1 Инфиксный обход дерева (рекурсивный) 
	void inorderWalk(std::ostream& out) const;
	// 9 Обход двоичного дерева по уровням (в ширину). 
	void walkByLevels(std::ostream& out) const;
	// 10 Являются ли два дерева похожими
	bool isSimilar(const BinarySearchTree<T>& other) const;
	// 11 Есть одинаковые ключи в двух деревьях поиска
	bool isIdenticalKey(const BinarySearchTree<T>& other) const;

	int NodeTwoChildren() const;

	int iterativeNodeTwoChildren() const;


private:
	template <class T>
	struct Node {
		T key_; // значение ключа, содержащееся в узле
		Node<T>* left_; // указатель на левое поддерево
		Node<T>* right_; // указатель на правое поддерево
		Node<T>* p_; // указатель на родителя !!! не используется
		// Конструктор узла
		Node(T key = T(), Node* left = nullptr, Node* right = nullptr, Node* p = nullptr) :
			key_(key), 
			left_(left), 
			right_(right), 
			p_(p)
		{}
		~Node() {
			delete left_;
			delete right_;
		}
	};

	Node<T> *root_;

	// 1.2 Функция поиска адреса узла по ключу в бинарном дереве поиска
	Node<T>* iterativeSearchNode(const T& key) const;
	// 4.2 Рекурсивная функция для вывода изображения дерева в выходной поток
	void printNode(std::ostream& out, Node<T>* root) const;
	// 5.2 Рекурсивная функция определения количества узлов дерева
	int getCount(const Node<T>* node) const;
	// 6.2 Рекурсивная функция определения высоты дерева
	int getHeight(const Node<T>* node) const;
	// 8.2 Рекурсивная функция для инфиксного обхода узлов дерева.
	void inorderWalk(Node<T>* node, std::ostream& out) const;
	int NodeTwoChildren(const Node<T>* root) const;
};

template <class T>
BinarySearchTree<T>::BinarySearchTree() :
	root_(nullptr)
{};

template <class T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>&& scr) noexcept:
	root_(scr.root_)
{
	scr.root_ == nullptr;
}

template <class T>
BinarySearchTree<T>::~BinarySearchTree()
{
	delete root_;
}

//________________________________public методы_____________________________
template<class T>
int BinarySearchTree<T>::iterativeNodeTwoChildren() const
{
	int count = 0;
	if (root_ != nullptr)
	{
		QueueArray <Node<T>*> queue;
		queue.enQueue(root_);
		Node<T>* curNode = root_;
		while (!queue.isEmpty())
		{
			curNode = queue.deQueue();
			if (curNode->left_ != nullptr && curNode->right_ != nullptr)
			{
				count++;
			}
			if (curNode->left_ != nullptr)
				queue.enQueue(curNode->left_);
			if (curNode->right_ != nullptr)
				queue.enQueue(curNode->right_);
		}
	}
	return count;
}

template<class T>
int BinarySearchTree<T>::NodeTwoChildren() const
{
	return NodeTwoChildren(root_);
}


template<class T>
bool BinarySearchTree<T>::iterativeSearch(const T& key) const
{
	return iterativeSearchNode(key);
}

template<class T>
bool BinarySearchTree<T>::insert(const T& key)
{
	Node<T>* curNode = root_;
	Node<T>* curNodeParent = nullptr;

	if (root_ == nullptr)
	{
		root_ = new Node<T>(key);
		return true;
	}
	else
	{
		while (curNode)
		{
			curNodeParent = curNode;
			if (key < curNode->key_)
				curNode = curNode->left_;
			else if (key > curNode->key_)
				curNode = curNode->right_;
			else 
				return false;
		}
		if (key < curNodeParent->key_)
			curNodeParent->left_ = new Node<T>(key, nullptr, nullptr, curNodeParent);
		else
			curNodeParent->right_ = new Node<T>(key, nullptr, nullptr, curNodeParent);
		return true;
	}
}

template<class T>
bool BinarySearchTree<T>::deleteKey(const T& key)
{
	Node<T>* curNode = root_;
	Node<T>* curNodeParent = nullptr;
	if (root_->key_ == key)
	{
		if (root_->left_ == nullptr && root_->right_ == nullptr)
		{
			delete root_;
			return true;
		}
		else if (root_->left_ == nullptr)
		{
			root_ = root_->right_;
			delete curNode;
			return true;
		}
		else if (root_->right_ == nullptr)
		{
			root_ = root_->left_;
			delete curNode;
			return true;
		}
		else
		{
			Node<T>* curMaxNode = curNode->left_;
			Node<T>* curMaxNodeParent = curNode;
			while (curMaxNode->right_ != nullptr)
			{
				curMaxNodeParent = curMaxNode;
				curMaxNode = curMaxNode->right_;
			}
			curNode->key_ = curMaxNode->key_;

			if (curMaxNode->right_ == nullptr && curMaxNode->left_ == nullptr)
				curMaxNodeParent->right_ = nullptr;
			else if (curMaxNode->left_ != nullptr)
				curMaxNodeParent->right_ = curMaxNode->left_;

			if (curMaxNodeParent == curNode) {
				curMaxNodeParent->left_ = nullptr;
			}
			else {
				curMaxNodeParent->right_ = nullptr;
			}
			delete curMaxNode;
			return true;
		}
	}
	else
	{
		while (curNode)
		{
			if (key < curNode->key_)
			{
				curNodeParent = curNode;
				curNode = curNode->left_;
			}
			else if (key > curNode->key_)
			{
				curNodeParent = curNode;
				curNode = curNode->right_;
			}
			else
			{
				if (curNode->left_ == nullptr && curNode->right_ == nullptr)
				{
					if (curNodeParent->left_ == curNode)
						curNodeParent->left_ = nullptr;
					else
						curNodeParent->right_ = nullptr;
					delete curNode;
					return true;
				}
				else if (curNode->left_ == nullptr)
				{
					if (curNodeParent->left_ == curNode)
						curNodeParent->left_ = curNode->right_;
					else 
						curNodeParent->right_ = curNode->right_;
					curNode->left_ = nullptr;
					curNode->right_ = nullptr;
					delete curNode;
					return true;
				}
				else if (curNode->right_ == nullptr)
				{
					if (curNodeParent->left_ == curNode)
						curNodeParent->left_ = curNode->left_;
					else 
						curNodeParent->right_ = curNode->right_;
					curNode->left_ = nullptr;
					curNode->right_ = nullptr;
					delete curNode;
					return true;
				}
				else
				{
					Node<T>* curMaxNode = curNode->left_;
					Node<T>* curMaxNodeParent = curNode;
					while (curMaxNode->right_ != nullptr)
					{
						curMaxNodeParent = curMaxNode;
						curMaxNode = curMaxNode->right_;
					}
					curNode->key_ = curMaxNode->key_;

					if (curMaxNode->right_ == nullptr && curMaxNode->left_ == nullptr)
						curMaxNodeParent->right_ = nullptr;
					else if (curMaxNode->left_ != nullptr)
						curMaxNodeParent->right_ = curMaxNode->left_;

					if (curMaxNodeParent == curNode) {
						curMaxNodeParent->left_ = nullptr;
					}
					else {
						curMaxNodeParent->right_ = nullptr;
					}
					delete curMaxNode;
					return true;
				}
			}
		}
	}
	return false;
}

template<class T>
void BinarySearchTree<T>::print(std::ostream& out) const
{
	printNode(out, root_);
}

template<class T>
int BinarySearchTree<T>::getCount() const
{
	return getCount(root_);
}

template<class T>
int BinarySearchTree<T>::getHeight() const
{
	return getHeight(root_)-1;
}

template<class T>
void BinarySearchTree<T>::iterativeInorderWalk(std::ostream& out) const
{
	Node<T>* curNode = root_;
	StackArray<Node<T>*> stack;
	while (!stack.isEmpty() || curNode != nullptr)
	{
		if (curNode != nullptr)
		{
			stack.push(curNode);
			curNode = curNode->left_;
		}
		else
		{
			curNode = stack.pop();
			out << curNode->key_ << " ";
			curNode = curNode->right_;
		}
	}
}

template<class T>
void BinarySearchTree<T>::inorderWalk(std::ostream& out) const
{
	inorderWalk(root_, out);
}

template<class T>
void BinarySearchTree<T>::walkByLevels(std::ostream& out) const
{
	if (root_ != nullptr)
	{
		QueueArray <Node<T>*> queue;
		queue.enQueue(root_);
		Node<T>* curNode = root_;
		while (!queue.isEmpty())
		{
			curNode = queue.deQueue();
			out << curNode->key_ << " ";
			if (curNode->left_ != nullptr)
				queue.enQueue(curNode->left_);
			if (curNode->right_ != nullptr)
				queue.enQueue(curNode->right_);
		}
	}
}

template<class T>
bool BinarySearchTree<T>::isSimilar(const BinarySearchTree<T>& other) const
{
	StackArray<Node<T>*> stack1;
	StackArray<Node<T>*> stack2;
	Node<T>* curNode1 = root_;
	Node<T>* curNode2 = other.root_;
	if (root_ == nullptr && other.root_ == nullptr)
	{
		return true;
	}
	else
	{
		while ((curNode1 || !stack1.isEmpty()) && (curNode2 || !stack2.isEmpty()))
		{
			while (curNode1 || curNode2)
			{
				if (curNode1 != nullptr)
				{
					stack1.push(curNode1);
					curNode1 = curNode1->left_;
				}
				if (curNode2 != nullptr)
				{
					stack2.push(curNode2);
					curNode2 = curNode2->left_;
				}
			}
			curNode1 = stack1.pop();
			curNode2 = stack2.pop();
			if (curNode1->key_ != curNode2->key_)
				return false;
			curNode1 = curNode1->right_;
			curNode2 = curNode2->right_;
		}
		if (curNode1 == nullptr && stack1.isEmpty() && curNode2 == nullptr && stack2.isEmpty())
			return true;
	}
	return false;

}

template<class T>
bool BinarySearchTree<T>::isIdenticalKey(const BinarySearchTree<T>& other) const
{
	StackArray<Node<T>*> stack1;
	StackArray<Node<T>*> stack2;
	Node<T>* curNode1 = root_;
	Node<T>* curNode2 = other.root_;
	if (root_ == nullptr && other.root_ == nullptr)
	{
		return false;
	}
	else
	{
		while ((curNode1 != nullptr || !stack1.isEmpty()) && (curNode2 != nullptr || !stack2.isEmpty()))
		{
			while (curNode1 != nullptr || curNode2 != nullptr)
			{
				if (curNode1 != nullptr)
				{
					stack1.push(curNode1);
					curNode1 = curNode1->left_;
				}
				if (curNode2 != nullptr)
				{
					stack2.push(curNode2);
					curNode2 = curNode2->left_;
				}
			}
			curNode1 = stack1.pop();
			curNode2 = stack2.pop();
			
			if (curNode1->key_ < curNode2->key_)
			{
				curNode1 = curNode1->right_;
				stack2.push(curNode2);
				curNode2 = nullptr;
			}
			else if (curNode1->key_ > curNode2->key_)
			{
				curNode2 = curNode2->right_;
				stack1.push(curNode1);
				curNode1 = nullptr;
			}
			else
				return true;
		}
	}
	return false;

}


//________________________________private методы_____________________________
template<class T>
int BinarySearchTree<T>::NodeTwoChildren(const Node<T>* node) const
{
	if (node == nullptr)
	{
		return 0;
	}
	if (node->right_ != nullptr && node->left_ == nullptr)
	{
		return (NodeTwoChildren(node->right_));
	}
	else if (node->right_ == nullptr && node->left_ != nullptr)
	{
		return (NodeTwoChildren(node->left_));
	}
	else if (node->right_ != nullptr && node->left_ != nullptr)
	{
		return (1 + NodeTwoChildren(node->left_) + NodeTwoChildren(node->right_));
	}
	else if (node->right_ == nullptr && node->left_ == nullptr)
	{
		return 0;
	}
}

template<class T>
typename BinarySearchTree<T>::Node<T>* BinarySearchTree<T>::iterativeSearchNode(const T& key) const
{
	Node<T>* curNode = root_;
	while (curNode)
	{
		if (key < curNode->key_)
			curNode = curNode->left_;
		else if (key > curNode->key_)
			curNode = curNode->right_;
		else
			return curNode;
	}
	return nullptr;
}

template<class T>
void BinarySearchTree<T>::printNode(std::ostream& out, Node<T>* root) const
{
	if (root_ != nullptr) {
		if (root != nullptr) {
			out << root->key_;
			out << "(";
			printNode(out, root->left_);
			printNode(out, root->right_);
			out << ")";
		}
		else
			out << ".";
	}
}

template<class T>
int BinarySearchTree<T>::getCount(const Node<T>* node) const
{
	if (node == nullptr) 
	{
		return 0;
	}
	return (1 + getCount(node->left_) + getCount(node->right_));
}

template<class T>
int BinarySearchTree<T>::getHeight(const Node<T>* node) const
{
	if (node == nullptr)
		return 0;
	else {
		int lHeight = getHeight(node->left_);
		int rHeight = getHeight(node->right_);
		return std::max(lHeight+1, rHeight+1);
	}
}

template<class T>
void BinarySearchTree<T>::inorderWalk(Node<T>* node, std::ostream& out) const
{
	if (node != nullptr) 
	{
		inorderWalk(node->left_, out);
		out << node->key_ << " ";
		inorderWalk(node->right_, out);
	}
}

template <class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator= (BinarySearchTree <T>&& src) noexcept
{
	if (this != &src) {
		std::swap(src);
	}
	return *this;
}

#endif // !BINARYSEARCHTREE_H
