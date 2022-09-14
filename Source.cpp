#include <iostream>
using namespace std;


template <typename T>
struct Node
{
	T data;
	Node<T>* next = nullptr;
	Node<T>* previous = nullptr;
};
template <typename T>
class Iterator
{
private:
	Node<T>* node;

public:
	Iterator(Node<T>* node);

	bool have();

	Iterator operator++(int);
	Iterator operator--(int);
	T get();
};
template<typename T>
Iterator<T>::Iterator(Node<T>* node)
	: node{ node } {}
template<typename T>
bool Iterator<T>::have()
{
	return node != nullptr;
}
template<typename T>
Iterator<T> Iterator<T>::operator++(int)
{
	this->node = this->node->next;
	return *this;
}
template<typename T>
Iterator<T> Iterator<T>::operator--(int)
{
	this->node = this->node->rev;
	return *this;
}
template<typename T>
T Iterator<T>::get()
{
	return node->data;
}


template <typename T>
class DoublyLinkedList
{
private:
	Node<T>* head;
	Node<T>* tail;
	int count;

public:
	~DoublyLinkedList(void);

	void AddToHead(T data);
	void AddToTail(T data);
	void DeleteFromHead();
	void DeleteFromTail();
	T GetDataByIndex(int index);
	void SetDataByIndex(T newData, int index);

	void Clear();

	Iterator<T> begin();
	Iterator<T> end();
};

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList(void)
{
	Clear();
}
template <typename T>
void DoublyLinkedList<T>::AddToHead(T data)
{
	Node<T>* temp = new Node<T>;
	temp->data = data;
	temp->next = head;
	if (head)
		head->previous = temp;
	else
		tail = temp;
	head = temp;
	count++;
}
template <typename T>
void DoublyLinkedList<T>::AddToTail(T data)
{
	Node<T>* temp = new Node<T>;
	temp->data = data;
	temp->previous = tail;
	if (tail)
		tail->next = temp;
	else
		head = temp;
	tail = temp;
	count++;
}
template <typename T>
void DoublyLinkedList<T>::DeleteFromHead()
{
	if (head)
	{
		Node<T>* temp = head->next;
		if (head == tail)
			tail = temp;
		delete head;
		head = temp;
		count--;
	}
}
template <typename T>
void DoublyLinkedList<T>::DeleteFromTail()
{
	if (tail)
	{
		Node<T>* temp = tail->previous;
		if (head == tail)
			head = temp;
		delete tail;
		tail = temp;
		count--;
	}
}
template <typename T>
T DoublyLinkedList<T>::GetDataByIndex(int index)
{

	Node<T>* temp;
	if (index <= count / 2)
	{
		temp = head;
		for (int i = 0; i != index; i++)
			temp = temp->next;
	}
	else
	{
		temp = tail;
		for (int i = count - 1; i != index; i--)
			temp = temp->previous;
	}
	return temp->data;
}
template <typename T>
void DoublyLinkedList<T>::SetDataByIndex(T newData, int index)
{
	Node<T>* temp;
	if (index <= count / 2)
	{
		temp = head;
		for (int i = 0; i != index; i++)
			temp = temp->next;
	}
	else
	{
		temp = tail;
		for (int i = count - 1; i != index; i--)
			temp = temp->previous;
	}
	temp->data = newData;
}
template <typename T>
void DoublyLinkedList<T>::Clear()
{
	Node<T>* temp = head;
	while (temp->next)
	{
		temp = temp->next;
		delete temp->previous;
	}
	delete tail;
	head = tail = nullptr;
	count = 0;
}
template<typename T>
Iterator<T> DoublyLinkedList<T>::begin()
{
	return Iterator<T>(head);
}
template<typename T>
Iterator<T> DoublyLinkedList<T>::end()
{
	return Iterator<T>(tail);
}


int main()
{
	DoublyLinkedList<int> dll;
	dll.AddToTail(25);
	dll.AddToTail(50);
	dll.AddToTail(100);

	for (auto it = dll.begin(); it.have(); it++)
		cout << it.get() << endl;

	return 0;
}
