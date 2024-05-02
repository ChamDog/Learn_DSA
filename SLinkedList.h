#pragma once
#include<iostream>
using namespace std;

template<typename T>
struct SLNode
{
	T item;
	SLNode<T>* next;
	SLNode(const T& k) :item(k), next(nullptr) {}
	SLNode() :item(), next(nullptr) {}
	~SLNode() {}
};

template<typename T>
void dispose(SLNode<T>* p)
{
	SLNode<T>* q;
	while (p != nullptr)
	{
		q = p;
		p = p->next;
		delete q;
	}
}

template<typename T>
class SLinkedList
{
private:
	SLNode<T>* _head;
	int _count;
public:
	SLinkedList()
	{//默认构造
		_head = new SLNode<T>();//_head指向SLNode<T>,所以new这个空间		
		_count = 0;
	}
	SLinkedList(const SLinkedList& other)
	{//拷贝构造
		SLNode<T>* p, * q, * t;
		_head = new SLNode<T>();
		_count = other._count;
		p = _head; q = other._head->next;
		while (q != nullptr)
		{
			t = new SLNode<T>(p->item);
			p->next = t;
			p = p->next; q = q->next;
		}
	}
	SLinkedList(const T* arr, int cnt)
	{//用数组构造
		if (cnt > 0)
		{
			_head = new SLNode<T>();
			_count = cnt;
			SLNode<T>* p, * t;
			p = _head;
			for (int i = 0; i < cnt; i++)
			{
				t = new SLNode<T>(arr[i]);
				p->next = t; p = p->next;
			}
		}
	}
	~SLinkedList()
	{
		dispose(_head);
	}
	bool empty()const;
	int count()const;
	SLNode<T>* findNode(int);
	T& operator[](int);
	const T& operator[](int)const;
	int find_if(const T&);
	void insert(const T&, int);
	void push_back(const T&);
	void remove(int);
	void pop_back();
	void exclude(const T&);
	void reverse();
	void showall();
};

template<typename T>
bool SLinkedList<T>::empty()const
{
	return _head->next == nullptr;
}

template<typename T>
int SLinkedList<T>::count() const
{
	return _count;
}

template<typename T>
SLNode<T>* SLinkedList<T>::findNode(int idx)
{
	if (!empty())
	{
		if (idx >= 0 && idx < _count)
		{
			int i = 0;
			SLNode<T>* p;
			p = _head->next;
			while (i < idx)
			{
				p = p->next;
				i++;
			}
			return p;
		}
		else if (idx == -1) { return _head; }
	}
}

template<typename T>
T& SLinkedList<T>::operator[](int idx)
{
	if (!empty() && idx >= 0 && idx < _count)
	{
		return findNode(idx)->item;
	}
}

template<typename T>
const T& SLinkedList<T>::operator[](int idx) const
{
	if (!empty() && idx >= 0 && idx < _count)
	{
		return findNode(idx)->item;
	}
}

template<typename T>
int SLinkedList<T>::find_if(const T& k)
{
	if (!empty())
	{
		int i = 0;
		SLNode<T>* p;
		p = _head->next;
		while (i < _count)
		{
			if (p->item == k) { return i; }
			else { p = p->next; i++; }
		}
	}
	return -2;
}

template<typename T>
void SLinkedList<T>::insert(const T& k, int idx)
{
	if (!empty())
	{
		if (idx >= 0 && idx < _count)
		{
			SLNode<T>* f, * t, * p;
			f = findNode(idx - 1); p = f->next;
			t = new SLNode<T>(k);
			f->next = t; t->next = p;
			_count++;
		}
	}
}

template<typename T>
void SLinkedList<T>::push_back(const T& k)
{
	SLNode<T>* t;
	t = new SLNode<T>(k);
	findNode(_count - 1)->next = t;
	_count++;
}

template<typename T>
void SLinkedList<T>::remove(int idx)
{
	if (!empty())
	{
		if (idx >= 0 && idx < _count)
		{
			SLNode<T>* f, * t;
			f = findNode(idx - 1); t = f->next;
			f->next = t->next;
			delete t;
			_count--;
		}
	}
}

template<typename T>
void SLinkedList<T>::pop_back()
{
	remove(_count - 1);
}

template<typename T>
void SLinkedList<T>::exclude(const T& k)
{//这个函数删除所有指定值
	if (!empty())
	{
		SLNode<T>* p, * q;
		p = _head; q = p->next;
		while (q != nullptr)
		{
			if (q->item == k)
			{
				p->next = q->next;
				delete q;
				q = p->next;//不需移动p
				_count--;
				continue;
			}
			p = q; q = q->next;
		}
	}
}

template<typename T>
void SLinkedList<T>::reverse()
{
	SLNode<T>* f, * p, * q;
	f = nullptr; p = _head->next; q = p->next;
	while (q != nullptr)
	{
		p->next = f; f = p; p = q; q = q->next;
	}
	p->next = f; _head->next = p;
}

template<typename T>
void SLinkedList<T>::showall()
{
	if (!empty())
	{
		cout << "h->";
		SLNode<T>* p;
		p = _head->next;
		while (p != nullptr)
		{
			cout << p->item << "->";
			p = p->next;
		}
		cout << "n" << "-count:" << _count << endl;
	}
	else { cout << "NULL\n"; }
}

template<typename T>
ostream& operator<<(ostream& os, SLinkedList<T>& SLL)
{
	if (SLL.empty()) { os << "NULL"; return os; }
	SLNode<T>* p;
	p = SLL.findNode(-1)->next;
	while (p != nullptr)
	{
		os << p->item << ' ';
		p = p->next;
	}
	return os;
}
