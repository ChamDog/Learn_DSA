#pragma once
#include<iostream>
#include<memory>
#include<utility>
#define DefualtCapacity 10
using namespace std;

template<typename T>
class SStack
{
private:
	int _size;
	int _capacity;
	int _topi;
	unique_ptr<T[]> _items;
public:
	SStack(int capacity = DefualtCapacity) :
		_size(0), _capacity(capacity), _topi(-1)
	{//默认构造
		_items = make_unique<T[]>(_capacity);
	}
	SStack(const SStack& other) :
		_size(other._size), _capacity(other._capacity), _topi(other._topi)
	{//拷贝构造
		_items = make_unique<T[]>(_capacity);
		if (_topi >= 0)
		{
			for (int i = 0; i <= _topi; i++)
			{
				_items[i] = other._items[i];
			}
		}
	}
	SStack(SStack&& other)
	{//移动构造
		cout << "move constructor called...\n";
		*this = move(other);
	}
	SStack& operator=(SStack&& other)
	{
		if (this != &other)
		{
			_size = other._size;
			_capacity = other._capacity;
			_topi = other._topi;
			_items.reset();
			_items = move(other._items);
		}
		return *this;
	}
	const SStack& operator=(const SStack& other)
	{
		if (this != &other)
		{
			_size = other._size;
			_capacity = other._capacity;
			_topi = other._topi;
			for (int i = 0; i <= _topi; i++)
			{
				_items[i] = other._items[i];
			}
		}
		return *this;
	}
	SStack(const T* arr, int len)
	{//用数组构造
		if (len > 0)
		{
			_size = len;
			_capacity = len;
			_topi = len - 1;
			_items = make_unique<T[]>(_capacity);
			for (int i = 0; i <= _topi; i++)
			{
				_items[i] = arr[i];
			}
		}
	}
	bool empty()const;
	bool full(int cnt = 0)const;
	int size()const;
	void IncreCapacity(int amount = DefualtCapacity);
	void push(const T&);
	void pop();
	const T& top()const;
	void showall()const;
};

template<typename T>
bool SStack<T>::empty() const
{
	return _topi == -1;
}

template<typename T>
bool SStack<T>::full(int cnt) const
{
	return _topi + cnt >= _capacity - 1;
}

template<typename T>
int SStack<T>::size() const
{
	return _topi + 1;
}

template<typename T>
void SStack<T>::IncreCapacity(int amount)
{
	_capacity = _capacity + amount;
	unique_ptr<T[]>newspace = make_unique<T[]>(_capacity);
	for (int i = 0; i <= _topi; i++)
	{
		newspace[i] = _items[i];
	}
	_items.reset();
	_items = move(newspace);
}

template<typename T>
void SStack<T>::push(const T& k)
{
	if (full(1)) { IncreCapacity(); }
	_size++;
	_topi++;
	_items[_topi] = k;
}

template<typename T>
void SStack<T>::pop()
{
	if (!empty())
	{
		_size--;
		_topi--;
	}
}

template<typename T>
const T& SStack<T>::top() const
{
	if (!empty()) { return _items[_topi]; }
}

template<typename T>
void SStack<T>::showall() const
{
	cout << "SStack:bottom|";
	for (int i = 0; i <= _topi; i++)
	{
		cout << _items[i] << "|";
	}
	cout << "top-size:" << _size << "-capacity:" << _capacity << "\n";
}

template<typename T>
ostream& operator<<(ostream& os, const SStack<T>& s)
{
	if (s.empty()) { os << "NULL"; return os; }
	SStack<T>copy(s);
	while (!copy.empty())
	{
		os << copy.top() << " ";
		copy.pop();
	}
	return os;
}

