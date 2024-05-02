#pragma once
#include<memory>
#include<iostream>
#include<sstream>
#include<string>
#define Default_SequencedList_Len 10
using namespace std;
template<typename T>
class SequencedList
{
private:
	int _count;
	int _capacity;
	unique_ptr<T[]> _items;
public:
	SequencedList(int capacity = Default_SequencedList_Len) :
		_count(0), _capacity(capacity)
	{//默认构造
		_items = make_unique<T[]>(_capacity);
	}
	SequencedList(const SequencedList& other) :
		_count(other._count), _capacity(other._capacity)
	{//拷贝构造
		_items = make_unique<T[]>(_capacity);//注意这是构造函数
		for (int i = 0; i < _count; i++)
		{
			_items[i] = other._items[i];
		}
	}
	SequencedList(SequencedList&& other) :
		_count(other._count), _capacity(other._capacity)
	{//移动构造
		*this = move(other);
	}
	SequencedList(const T* arr, int cnt):
		_count(cnt),_capacity(cnt)
	{//用数组构造
		_items = make_unique<T[]>(_capacity);
		for (int i = 0; i < _count; i++)
		{
			_items[i] = arr[i];
		}
	}
	bool empty()const;
	bool full(int cnt = 0)const;
	int count()const;
	void IncreCapacity(int cnt = 5);
	const T& operator[](int)const;
	T& operator[](int);
	int find_if(const T&)const;
	void insert(const T&, int);
	void push_back(const T&);
	void remove(int);
	void showall()const;
	string str()const
	{
		ostringstream ss;
		ss << "SequencencedList:";
		if (empty()) { ss << "NULL"; return ss.str(); }
		for (int i = 0; i < _count; i++)
		{
			ss << _items[i] << " ";
		}
		return ss.str();

	}
};

template<typename T>
inline bool SequencedList<T>::empty() const
{
	return _count == 0;
}

template<typename T>
inline bool SequencedList<T>::full(int cnt) const
{
	return _count + cnt >= _capacity;
}

template<typename T>
inline int SequencedList<T>::count() const
{
	return _count;
}

template<typename T>
inline void SequencedList<T>::IncreCapacity(int cnt)
{
	_capacity = _capacity + cnt;
	unique_ptr<T[]> newspace = make_unique<T[]>(_capacity);
	for (int i = 0; i < _count; i++)
	{
		newspace[i] = _items[i];
	}
	_items.reset();
	_items = move(newspace);
}

template<typename T>
inline const T& SequencedList<T>::operator[](int i) const
{
	if (!empty() && i >= 0 && i < _count) { return _items[i]; }
}

template<typename T>
inline T& SequencedList<T>::operator[](int i)
{
	if (!empty() && i >= 0 && i < _count) { return _items[i]; }
}

template<typename T>
inline int SequencedList<T>::find_if(const T& k) const
{
	if (!empty())
	{
		for (int i = 0; i < _count; i++)
		{
			if (_items[i] == k) { return i; }
		}
	}
	return -1;
}

template<typename T>
inline void SequencedList<T>::insert(const T& k,int idx)
{
	if (full(1)) { IncreCapacity(); }
	if (idx >= 0 && idx < _count)
	{
		for (int i = _count; i > idx; i--)
		{
			_items[i] = _items[i - 1];
		}
		_items[idx] = k;
		_count++;
	}
	else { cout << "Invalid\n"; }
}

template<typename T>
inline void SequencedList<T>::push_back(const T& k)
{
	if (full(1)) { IncreCapacity(); }
	_count++;
	_items[_count - 1] = k;
}

template<typename T>
inline void SequencedList<T>::remove(int idx)
{
	if (idx >= 0 && idx < _count)
	{
		for (int i = idx; i < _count - 1; i++)
		{
			_items[i] = _items[i + 1];
		}
		_count--;
	}
}

template<typename T>
inline void SequencedList<T>::showall() const
{
	for (int i = 0; i < _count; i++)
	{
		cout << _items[i] << '-';
	}
	cout << "capacity:" << _capacity << '-' << "count:" << _count;
}

template<typename T>
ostream& operator<<(ostream& os, const SequencedList<T>& SL)
{
	if (SL.empty()) { os << "NULL"; return os; }
	for (int i = 0; i < SL.count(); i++)
	{
		os << SL[i] << " ";
	}
	return os;
}

