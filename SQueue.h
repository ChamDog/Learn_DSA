#pragma once
#include<iostream>
#include<memory>
#define DefaultCapacity 5
using namespace std;

template<typename T>
class SQueue
{
private:
	int _count;
	int _front;
	int _rear;
	int _capacity;
	unique_ptr<T[]> _items;
public:
	SQueue(int capacity = DefaultCapacity);
	SQueue(const SQueue& other);
	SQueue(SQueue&& other);
	const SQueue<T>& operator=(SQueue<T>&& other);
	SQueue<T>& operator=(const SQueue<T>& other);
	SQueue(const T* arr, int cnt);
	bool empty()const;
	bool full(int cnt = 0)const;
	int count()const;
	void IncreCapacity(int amount = DefaultCapacity);
	void enqueue(const T& k);
	void dequeue();
	const T& front()const;
	void showall()const;
	void clear();
};

template<typename T>
SQueue<T>::SQueue(int capacity)
{
	_count = 0;
	_capacity = capacity + 1;
	_front = 0;
	_rear = -1;
	_items = make_unique<T[]>(_capacity);
}

template<typename T>
SQueue<T>::SQueue(const SQueue& other)
{
	_count = other._count;
	_capacity = other._capacity;
	_front = other._front;
	_rear = other._rear;
	_items = make_unique<T[]>(_capacity);
	for (int i = 0; i < _count; i++)
	{
		int j = (_front + i) % _capacity;
		_items[j] = other._items[j];
	}
}

template<typename T>
SQueue<T>::SQueue(SQueue&& other)
{
	if (this != &other)
	{
		//cout << "move consurctor called...\n";
		*this = move(other);
	}
}

template<typename T>
const SQueue<T>& SQueue<T>::operator=(SQueue<T>&& other)
{
	if (this != &other)
	{
		_count = other._count;
		_capacity = other._capacity;
		_front = other._front;
		_rear = other._rear;
		_items.reset();
		_items = move(other._items);
	}
	return *this;
}

template<typename T>
SQueue<T>& SQueue<T>::operator=(const SQueue<T>& other)
{
	if (this != &other)
	{
		_count = other._count;
		_capacity = other._capacity;
		_front = other._front;
		_rear = other._rear;
		_items.reset();
		_items = make_unique<T[]>(_capacity);
		for (int i = 0; i < _count; i++)
		{
			int j = (_front + i) % _capacity;
			_items[j] = other._items[j];
		}
	}
	return *this;
}

template<typename T>
SQueue<T>::SQueue(const T* arr, int cnt)
{
	if (cnt > 0)
	{
		_count = cnt;
		_capacity = cnt + DefaultCapacity + 1;
		_front = 0;
		_rear = -1;
		_items = make_unique<T[]>(_capacity);
		for (int i = 0; i < _count; i++)
		{
			_rear++;
			_items[_rear] = arr[i];
		}
	}
}

template<typename T>
bool SQueue<T>::empty() const
{
	return _count == 0;
}

template<typename T>
bool SQueue<T>::full(int cnt) const
{
	return _count + cnt >= _capacity - 1;
}

template<typename T>
int SQueue<T>::count() const
{
	return _count;
}

template<typename T>
void SQueue<T>::IncreCapacity(int amount)
{
	_capacity = _capacity + amount;
	unique_ptr<T[]>newspace = make_unique<T[]>(_capacity);
	for (int i = 0; i < _count; i++)
	{
		int j = (_front + i) % _capacity;
		newspace[i] = _items[j];
	}
	_front = 0;
	_rear = _count - 1;
	_items.reset();
	_items = move(newspace);
}

template<typename T>
void SQueue<T>::enqueue(const T& k)
{
	if (full(1)) { IncreCapacity(); }
	_rear = (_rear + 1) % _capacity;
	_items[_rear] = k;
	_count++;
}

template<typename T>
void SQueue<T>::dequeue()
{
	if (!empty())
	{
		_front = (_front + 1) % _capacity;
		_count--;
	}
}

template<typename T>
const T& SQueue<T>::front() const
{
	if (!empty()) { return _items[_front]; }
}

template<typename T>
void SQueue<T>::showall() const
{
	cout << "SQueue:";
	if (!empty())
	{
		for (int i = 0; i < _count; i++)
		{
			int j = (_front + i) % _capacity;
			cout << _items[j] << "-";
		}
	}
	else { cout << "NULL-"; }
	cout << "count:" << _count << "-capacity:" << _capacity << endl;
}

template<typename T>
void SQueue<T>::clear()
{
	_count = 0;
	_front = 0;
	_rear = -1;
}

