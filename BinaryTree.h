#pragma once
#include<iostream>
#include<vector>
#include<stack>
#include<queue>
using namespace std;

template<typename T>
struct listflags
{
	T nflag;
	T lflag;
	T rflag;
	T mflag;
};
static int idx = 0;
static void* plistflags = nullptr;
template<typename T>
bool isdata(const T& nodevalue, const listflags<T>* pflags)
{
	if (nodevalue == pflags->lflag || nodevalue == pflags->rflag || nodevalue == pflags->nflag || nodevalue == pflags->mflag)
	{
		return false;
	}
	return true;
}

template<typename T>
struct BTNode
{
	T item;
	BTNode<T>* left;
	BTNode<T>* right;
	BTNode() :item(), left(nullptr), right(nullptr) {}
	BTNode(const T& k) :item(k), left(nullptr), right(nullptr) {}
	~BTNode() { cout << "A node is destroyed...\n"; }
	//�ݹ�ر������Դ˽��Ϊ����㣩���ȸ����и�����
	void PreOrder(vector<T>& vec)
	{
		vec.push_back(this->item);
		BTNode<T>* p = this->left;
		if (p != nullptr)
		{
			p->PreOrder(vec);
		}
		p = this->right;
		if (p != nullptr)
		{
			p->PreOrder(vec);
		}
	}
	void InOrder(vector<T>& vec)
	{
		BTNode<T>* p = this->left;
		if (p != nullptr)
		{
			p->InOrder(vec);
		}
		vec.push_back(this->item);
		p = this->right;
		if (p != nullptr)
		{
			p->InOrder(vec);
		}
	}
	void PostOrder(vector<T>& vec)
	{
		BTNode<T>* p = this->left;
		if (p != nullptr)
		{
			p->PostOrder(vec);
		}
		p = this->right;
		if (p != nullptr)
		{
			p->PostOrder(vec);
		}
		vec.push_back(this->item);
	}
	//�ǵݹ�ر������Դ˽��Ϊ����㣩���и�
	void InOrderNR(vector<T>& vec)
	{//vecҲ���Ըĳ�BTNode<T>*�����ͣ�ʵ�ֱ�����㣨ָ�룩
		stack<BTNode<T>*>s;
		BTNode<T>* p = this;
		while (p != nullptr || s.size() != 0)
		{
			if (p != nullptr)
			{
				s.push(p);
				p = p->left;
			}
			else
			{
				p = s.top();
				vec.push_back(p->item);
				s.pop();
				p = p->right;
			}
		}
	}
	//����α���
	void LevelOrder(vector<T>& vec)
	{
		queue<BTNode<T>*>q;
		BTNode<T>* p = this;
		while (p != nullptr)
		{
			vec.push_back(p->item);
			if (p->left != nullptr)
			{
				q.push(p->left);
			}
			if (p->right != nullptr)
			{
				q.push(p->right);
			}
			if (q.size() != 0)
			{
				p = q.front();
				q.pop();
			}
			else
			{
				p = nullptr;
			}
		}
	}
};

template<typename T>
class BTree
{
private:
	BTNode<T>* _root;
public:
	BTree() :
		_root(nullptr)
	{
		cout << "A null BTree constructed...\n";
	}
	BTNode<T>*& root()
	{
		cout << "The root set...\n";
		return _root;
	}
	void dispose()
	{
		if (_root != nullptr) { dispose(_root); _root = nullptr; }
	}
	void dispose(BTNode<T>* p)
	{
		if (p != nullptr)
		{
			dispose(p->left);
			dispose(p->right);
			delete p;
		}
	}
	//�ݹ����������
	void PreOrder(vector<T>& vec)
	{
		if (_root != nullptr)
		{
			cout << "�ȸ�����";
			_root->PreOrder(vec);
		}
	}
	void InOrder(vector<T>& vec)
	{
		if (_root != nullptr)
		{
			cout << "�и�����";
			_root->InOrder(vec);
		}
	}
	void PostOrder(vector<T>& vec)
	{
		if (_root != nullptr)
		{
			cout << "�������";
			_root->PostOrder(vec);
		}
	}
	//�ǵݹ����������
	void InOrderNR(vector<T>& vec)
	{
		if (_root != nullptr)
		{
			cout << "�и��ǵݹ飺";
			_root->InOrderNR(vec);
		}
	}
	//��α���������
	void LevelOrder(vector<T>& vec)
	{
		if (_root != nullptr)
		{
			cout << "��α�����";
			_root->LevelOrder(vec);
		}
	}
};

template<typename T>
void byArray(const T* arr, int cnt, BTree<T>& bt)
{
	if (cnt > 0)
	{
		BTNode<T>** p = new BTNode<T>*[cnt];//һ����ָ��
		for (int i = 0; i < cnt; i++)
		{
			p[i] = new BTNode<T>(arr[i]);//���㣬new��Ӧdispose��delete
		}
		for (int i = 0; i < cnt; i++)
		{
			int j = 2 * i + 1;
			if (j < cnt) { p[i]->left = p[j]; }
			else { p[i]->left = nullptr; }
			j++;
			if (j < cnt) { p[i]->right = p[j]; }
			else { p[i]->right = nullptr; }
		}
		bt.root() = p[0];
		cout << "Success to build a BTree.\n";
	}
	else
	{
		cout << "Failed to build a BTree.\n";
	}
}
template<typename T>
BTNode<T>* rootby2lists(vector<T>& pre, vector<T>& in)
{
	BTNode<T>* p = nullptr;//Ҷ�ӽڵ����һ�����ǿգ���˳�ʼ��Ϊ��
	int n = pre.size();
	if (n > 0)
	{
		vector<T>presub, insub;
		p = new BTNode<T>(pre[0]);
		int k = 0; while (k < n && in[k] != pre[0])k++;
		for (int i = 1; i <= k; i++)
		{
			presub.push_back(pre[i]);
		}
		for (int i = 0; i < k; i++)
		{
			insub.push_back(in[i]);
		}
		p->left = rootby2lists(presub, insub);
		presub.clear(); insub.clear();
		for (int i = k + 1; i < n; i++)
		{
			presub.push_back(pre[i]);
		}
		for (int i = k + 1; i < n; i++)
		{
			insub.push_back(in[i]);
		}
		p->right = rootby2lists(presub, insub);
	}
	return p;
}
template<typename T>
void by2lists(vector<T>& pre, vector<T>& in, BTree<T>* bt)
{
	bt->root() = rootby2lists(pre, in);
}
template<typename T>
BTNode<T>* rootbyglist(T* slist)
{
	BTNode<T>* p = nullptr;
	T nodedata = slist[idx];
	listflags<T>* pflags = (listflags<T>*)plistflags;
	if (isdata(nodedata, pflags))
	{
		p = new BTNode<T>(nodedata);
		idx++;
		nodedata = slist[idx];
		if (nodedata == pflags->lflag)
		{
			idx++;
			p->left = rootbyglist(slist);
			idx++;
			p->right = rootbyglist(slist);
			idx++;
		}
	}
	if (nodedata == pflags->nflag)
	{
		idx++;
	}
	return p;
}
template<typename T>
void byglist(T* slist, int cnt, BTree<T>* bt, const listflags<T>* pClistflags = nullptr)
{
	idx = 0;
	listflags<T>Dlistflags{ '^','(',')',',' };
	if (cnt > 0)
	{
		listflags<T>* p;
		if (pClistflags != nullptr)
		{
			p = (listflags<T>*)pClistflags;
		}
		else
		{
			p = &Dlistflags;
		}
		plistflags = p;
		bt->root() = rootbyglist(slist);
	}
	else
	{
		bt->root() = nullptr;
	}
}
