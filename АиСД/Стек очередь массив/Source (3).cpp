#include <iostream>
#include "StackArray.h"
#include "QueueArray.h"


bool checkBalanceBrackets(const char* text, const int maxDeep)
{
	char cur = text[0];
	StackArray<char> stack;
	int deep = 0;
	int index = 0;
	char popped = text[0];
	while (cur != '\0' && maxDeep >= deep)
	{
		
		if (cur == '(' || cur == '{' || cur == '[')
		{
			stack.push(cur);
			deep++;
		}

		if ((cur == ')' || cur == '}' || cur == ']') )
		{
			if (stack.isEmpty())
				return false;
			popped = stack.pop();
			if (popped == '(' && cur == ')' || popped == '{' && cur == '}' || popped == '[' && cur == ']')
			{
				deep--;
			}
			else
				return false;
		}
		index++;
		cur = text[index];
	}
	
	return !deep;
}

void test_CheckBalanceBrackets()
{
	std::cout << "------------реярш CheckBalanceBrackets------------\n";
	std::cout << "1:" << checkBalanceBrackets("((()))", 3) << std::endl;
	std::cout << "2:" << checkBalanceBrackets("()))", 3) << std::endl;
	std::cout << "3:" << checkBalanceBrackets("((()))", 2) << std::endl;
	std::cout << "4:" << checkBalanceBrackets("  ", 3) << std::endl;
	std::cout << "5:" << checkBalanceBrackets("g", 3) << std::endl;
	std::cout << "6:" << checkBalanceBrackets("(", 3) << std::endl;
	std::cout << "7:" << checkBalanceBrackets(")", 3) << std::endl;
	std::cout << "8:" << checkBalanceBrackets(" ", 0) << std::endl;
	std::cout << "9:" << checkBalanceBrackets("(", 0) << std::endl;
	std::cout << "10:" << checkBalanceBrackets("((", 0) << std::endl;
	std::cout << "11:" << checkBalanceBrackets("(3+1)*2", 1) << std::endl;
	std::cout << "12:" << checkBalanceBrackets("()()()()()()", 10) << std::endl;
	std::cout << "13:" << checkBalanceBrackets("{}[]()", 3) << std::endl;
	std::cout << "14:" << checkBalanceBrackets("({[]})", 3) << std::endl;
	std::cout << "15:" << checkBalanceBrackets("{}[]()", 2) << std::endl;
	std::cout << "16:" << checkBalanceBrackets("({[]})", 2) << std::endl;
	std::cout << "17:" << checkBalanceBrackets("{[", 3) << std::endl;
	std::cout << "18:" << checkBalanceBrackets("{(]", 3) << std::endl;
}

void test_Stack()
{
	std::cout << "\n------------реярш Stack------------\n";
	StackArray<int> stack1(4);
	std::cout << stack1.isEmpty() << std::endl;

	try
	{
		std::cout << stack1.pop() << std::endl;
		std::cout << stack1.pop() << std::endl;
	}
	catch (StackUnderflow& e)
	{
		std::cout << e.what() << std::endl;
	}

	stack1.push(1);
	stack1.push(2);
	stack1.push(3);
	stack1.push(4);

	try
	{
		stack1.push(5);
	}
	catch (StackOverflow& e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << stack1.isEmpty() << std::endl;
	std::cout << stack1.pop() << std::endl;
	std::cout << stack1.pop() << std::endl;
	std::cout << stack1.pop() << std::endl;
	std::cout << stack1.pop() << std::endl;
	try
	{
		StackArray<int> stack2(-4);
		stack2.push(2);
		stack2.isEmpty();
	}
	catch (WrongStackSize& e)
	{
		std::cout << e.what() << std::endl;
	}
}

void test_Queue()
{
	std::cout << "\n------------реярш Queue------------\n";
	QueueArray<int> queue1(4);
	std::cout << queue1.isEmpty() << std::endl;

	try
	{
		queue1.deQueue();
	}
	catch (QueueUnderflow& e)
	{
		std::cout << e.what() << std::endl;
	}

	queue1.enQueue(1);
	queue1.enQueue(2);
	queue1.enQueue(3);
	queue1.enQueue(4);

	try
	{
		queue1.enQueue(5);
	}
	catch (QueueOverflow& e)
	{
		std::cout << e.what() << std::endl;
	}

	std::cout << queue1.isEmpty() << std::endl;
	std::cout << queue1.deQueue() << std::endl;
	std::cout << queue1.deQueue() << std::endl;
	queue1.enQueue(5);
	std::cout << queue1.deQueue() << std::endl;
	std::cout << queue1.deQueue() << std::endl;
	queue1.enQueue(6);
	queue1.enQueue(7);
	queue1.enQueue(8);
	std::cout << queue1.deQueue() << std::endl;
	std::cout << queue1.deQueue() << std::endl;
	std::cout << queue1.deQueue() << std::endl;
	std::cout << queue1.deQueue() << std::endl;


	QueueArray<const char*> queue2(2);
	queue2.enQueue("sca");
	queue2.enQueue("safahajsckb");
	std::cout << queue2.deQueue() << std::endl;
	std::cout << queue2.deQueue() << std::endl;
	std::cout << queue2.isEmpty() << std::endl;

	try
	{
		QueueArray<int> queue3(-4);
		queue3.enQueue(3);
		queue3.isEmpty();
	}
	catch(WrongQueueSize& e)
	{
		std::cout << e.what() << std::endl;
	}

}

int main()
{
	setlocale(LC_ALL, "ru");

	test_CheckBalanceBrackets();
	test_Stack();
	test_Queue();

	return 0;
}