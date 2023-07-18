#ifndef QUEUE_H
#define QUEUE_H

template <class T>
class Queue
{
public:
	virtual ~Queue() {}
	virtual void enQueue(const T& e) = 0; // Добавление элемента в очередь
	virtual T deQueue() = 0; // Удаление элемента из очереди
	virtual bool isEmpty() = 0; // Проверка очереди на пустоту 
};

#endif // !QUEUE_H


