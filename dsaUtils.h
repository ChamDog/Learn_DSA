#include<iostream>
#include<vector>

using namespace std;

void RandomizeData(int* a, int cnt, int minValue = -99, int maxValue = 100);
template<typename T>void Show(T* a, int cnt);
template<typename IIt>void Show(IIt first, IIt last);

template<typename T>
inline void Show(T* a, int cnt)                     //为何在此处？
{
	for (int i = 0; i < cnt; i++) {
		cout << a[i] << " ";
	}
	cout << endl;

}

template<typename IIt>
inline void Show(IIt first, IIt last)
{
	while (first != last) {
		cout << *first << " "; first++;
	}
	cout << endl;

}
