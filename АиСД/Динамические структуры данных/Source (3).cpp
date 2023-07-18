#include <iostream>
#include <string>
#include "DictionaryList.h"

void dictionaryTest()
{
	std::cout << "-----------------------------------------------------ТЕСТЫ МЕТОДОВ-----------------------------------------------------\n";
	// Создание списка
	// bool insert(const KeyT& key)
	std::cout << "-------------------------ТЕСТЫ INSERT()-------------------------\n";
	DictionaryList<int> dictInt;

	std::cout << "\n-----Вставка нового элемента:\n";
	if (dictInt.Insert(9))
		std::cout << "вставлено\n";
	if (dictInt.Insert(2))
		std::cout << "вставлено\n";
	if (dictInt.Insert(5))
		std::cout << "вставлено\n";
	if (dictInt.Insert(1))
		std::cout << "вставлено\n";
	if (dictInt.Insert(7))
		std::cout << "вставлено\n";

	std::cout << "\n-----Вставка существующего элемента:\n";
	if (!dictInt.Insert(5))
		std::cout << "уже существует\n";
	

	std::cout << dictInt << '\n';

	// Поиск элемента
	// bool search(const KeyT& key)
	std::cout << "-------------------------ТЕСТЫ SEARCH()-------------------------\n";
	std::cout << "\n-----Существующие элементы\n";
	if (dictInt.Search(1))
	{
		std::cout << "найдено\n";
	}
	if (dictInt.Search(5))
	{
		std::cout << "найдено\n";
	}
	if (dictInt.Search(9))
	{
		std::cout << "найдено\n";
	}
	std::cout << "\n-----Несуществующие элементы\n";
	if (!dictInt.Search(-8))
	{
		std::cout << "не найдено\n";
	}
	if (!dictInt.Search(4))
	{
		std::cout << "не найдено\n";
	}
	if (!dictInt.Search(15))
	{
		std::cout << "не найдено\n";
	}

	// Удаление элементов
	// bool delete(const KeyT& key)
	std::cout << "-------------------------ТЕСТЫ DELETE()-------------------------\n";
	std::cout << "\n-----Существующие элементы\n";
	if (dictInt.Delete(5))
	{
		std::cout << "удалено\n";
	}
	if (dictInt.Delete(1))
	{
		std::cout << "удалено\n";
	}
	if (dictInt.Delete(9))
	{
		std::cout << "удалено\n";
	}

	std::cout << dictInt << '\n';
	std::cout << "\n-----Несуществующие элементы\n";
	if (!dictInt.Delete(15))
	{
		std::cout << "не найдено\n";
	}

	std::cout << "\n-----Удаление оставшихся элементов\n";
	if (dictInt.Delete(2))
	{
		std::cout << "удалено\n";
	}
	if (dictInt.Delete(7))
	{
		std::cout << "удалено\n";
	}

	std::cout << dictInt << '\n';

	std::cout << "\n-----Удаление из пустого списка:\n";

	if (!dictInt.Delete(5))
		std::cout << "нет элементов для удаления\n";
	std::cout << dictInt;
}

// Тестирование операций над словарями
void operationTest()
{
	std::cout << "-----------------------------------------------------ТЕСТЫ ОПЕРАЦИЙ-----------------------------------------------------\n";
	// Объединение списков
	// void merge(DictionaryList& dict2)
	std::cout << "\n-------------------------ТЕСТЫ MERGE()-------------------------\n";
	DictionaryList<std::string> dictStr;
	dictStr.Insert("789");
	dictStr.Insert("345");
	dictStr.Insert("567");
	dictStr.Insert("321");
	dictStr.Insert("82");

	std::cout << "-----До MERGE():\n";
	std::cout << dictStr << '\n';

	DictionaryList<std::string> dictStr2;
	dictStr2.Insert("81");
	dictStr2.Insert("123");
	dictStr2.Insert("456");
	dictStr2.Insert("9");
	dictStr2.Insert("987");
	// повторяющийся элемент
	dictStr2.Insert("567");

	std::cout << dictStr2 << '\n';

	dictStr.Merge(dictStr2);

	std::cout << "-----После MERGE():\n";
	std::cout << dictStr << '\n';
	std::cout << dictStr2 << '\n';

	std::cout << "\n-----Объединение с пустым списком:\n (непустой + пустой)";

	dictStr.Merge(dictStr2);
	std::cout << dictStr << '\n';
	std::cout << dictStr2 << '\n';
	std::cout << "\n(меняем местами)\n";
	dictStr2.Merge(dictStr);
	std::cout << dictStr << '\n';
	std::cout << dictStr2 << '\n';
	std::cout << "\n(еще раз меняем местами)\n";
	dictStr.Merge(dictStr2);
	std::cout << dictStr << '\n';
	std::cout << dictStr2 << '\n';
	std::cout << "\n(пустой + пустой)\n";
	DictionaryList<std::string> dict1;
	DictionaryList<std::string> dict2;
	if (dict1.Merge(dict2))
		std::cout << "\nОбъединены 2 пустых списка\n";
	std::cout << dict1;





	// Вычитание списков
	// void subtract(const DictionaryList& dict2)
	std::cout << "-------------------------ТЕСТЫ DELETE_DICT()-------------------------\n";
	dictStr2.Insert("81");
	dictStr2.Insert("123");
	dictStr2.Insert("456");
	dictStr2.Insert("9");
	dictStr2.Insert("987");
	dictStr2.Insert("888");
	dictStr2.Insert("777");
	dictStr2.Insert("444");

	std::cout << "-----До DELETE_DICT():\n";
	std::cout << dictStr << '\n';
	std::cout << dictStr2 << '\n';

	dictStr.DeleteDict(dictStr2);

	std::cout << "-----После DELETE_DICT():\n";
	std::cout << dictStr << '\n';
	std::cout << dictStr2 << '\n';

	std::cout << "\n-----Вычитание пустого списка\n";
	dictStr.DeleteDict(DictionaryList<std::string>());

	std::cout << dictStr << '\n';

	std::cout << "\n-----Вычитание из пустого списка\n";
	if (!DictionaryList<std::string>().DeleteDict(dictStr))
		std::cout << "\nВычитание выполнено\n";
	
	


	// Пересечение списков
	// DictionaryList intersect(const DictionaryList& dict1, const DictionaryList& dict2)
	std::cout << "-------------------------ТЕСТЫ GET_INTERSECTION()-------------------------\n";

	DictionaryList<std::string> dictStr3;
	dictStr3.Insert("789");
	dictStr3.Insert("345");
	dictStr3.Insert("567");
	//неповторяющиеся элементы
	dictStr3.Insert("589");
	dictStr3.Insert("467");

	std::cout << "\n-----До GET_INTERSECTION():\n";
	std::cout << dictStr << '\n';
	std::cout << dictStr3 << '\n';


	DictionaryList<std::string> dictStr4 = getIntersection(dictStr, dictStr3);

	std::cout << "\n-----После GET_INTERSECTION():\n";
	std::cout << dictStr << '\n';
	std::cout << dictStr3 << '\n';
	std::cout << dictStr4 << '\n';

	std::cout << "\n-----Пересечение пустых списков\n";
	dictStr4 = getIntersection(DictionaryList<std::string>(), DictionaryList<std::string>());
	std::cout << dictStr4 << '\n';
}

int main()
{
	setlocale(LC_ALL, "ru");
	
	dictionaryTest();
	operationTest();
	

	return 0;
}





//void Merge(DictionaryList<keyT>& list2)//медленный, дописать быстрый -------------------------
//{
//	if (head_ == nullptr)
//	{
//		head_ = list2.head_;
//	}
//	else
//	{
//		if (list2.head_ != nullptr)
//		{
//			Node* curNode = list2.head_;
//			Node* nextNode = nullptr;
//			while (curNode)
//			{
//				this->Insert(curNode->data_);
//				nextNode = curNode->ptrNext_;
//				list2.Delete(curNode->data_);
//				curNode = nextNode;
//			}
//		}
//	}
//}



//
//void DeleteDict(const DictionaryList<keyT>& list2)
//{
//	Node* curNode = list2.head_;
//	while (curNode != nullptr)
//	{
//		this->Delete(curNode->data_);
//		curNode = curNode->ptrNext_;
//	}
//}