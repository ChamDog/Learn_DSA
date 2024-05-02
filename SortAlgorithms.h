#include<cstdlib>
using namespace std;
/* 
* I found that we can't define template functions in .cpp but .h, so below are them and their definations.
*/

/*
* @brief: InsertSort.
* @param: an array and its length.
*/
template<typename T>void InsertSort(T* arr,int arr_len);
template<typename T>
inline void InsertSort(T* arr, int arr_len)
{
	for (int i = 1; i < arr_len; i++)
	{
		for (int j = i; j >= 1; j--)
		{
			if (arr[j] < arr[j - 1])
			{
				T temp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = temp;
			}
		}
	}
}
/*
* @brief: ShellSort.
* @param: an array and its length.
*/
template<typename T>void ShellSort(T* arr, int arr_len);
template<typename T>
inline void ShellSort(T* arr, int arr_len)
{
	int jump = arr_len / 2;
	while ( jump >= 1 )
	{
		for (int i = jump; i < arr_len; i++)
		{
			for (int j = i; j >= jump; j -= jump)
			{
				if (arr[j] < arr[j - jump])
				{
					T temp = arr[j];
					arr[j] = arr[j - jump];
					arr[j - jump] = temp;
				}
			}
		}
		jump /= 2;
	}
}
/*
* @brief: BubbleSort.
* @param: an array and its length.
*/
template<typename T>void BubbleSort(T* arr, int arr_len);
template<typename T>
inline void BubbleSort(T* arr, int arr_len)
{
	for (int i = 0; i < arr_len; i++)
	{
		for (int j = 0; j < arr_len - i - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				T temp = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = temp;
			}
		}
	}
}
/*
* @brief: SelectSort.
* @param: an array and its length.
*/
template<typename T>void SelectSort(T* arr, int arr_len);
template<typename T>
inline void SelectSort(T* arr, int arr_len)
{
	for (int i = 0; i < arr_len; i++)
	{
		int k = i;
		for (int j = i+1; j < arr_len; j++)
		{
			if (arr[k] > arr[j])
			{
				k = j;
			}
		}
		T temp = arr[k];
		arr[k] = arr[i];
		arr[i] = temp;
	}
}
/*
* @brief: QuickSort. In a single function use, number smaller than pivot will be put in the left of it, 
		  this process can arise a lot of times. So in line 110, I wright i not arr_left.
* @param: an array and its left index and right index.
*/
template<typename T>void QuickSort(T* arr, int arr_left,int arr_right);
template<typename T>
inline void QuickSort(T* arr, int arr_left, int arr_right)
{
	if (arr_left >= arr_right) { return; }
	T pivot = arr[arr_left];
	int i = arr_left, j = arr_right;
	while (i < j)
	{
		while (i < j && arr[j] > pivot) { j--; }
		arr[i] = arr[j];
		while (i < j && arr[i] < pivot) { i++; }
		arr[j] = arr[i];
	}
	arr[i] = pivot;
	QuickSort(arr, arr_left, i - 1);
	QuickSort(arr, i + 1, arr_right);
}
/*
* @brief: Merge. In this function, an array will be cut to tow arrays, then merge them to a sorted array
* @param: an array and its left, mid, right index.
*         In fact, its parameters will be calculate in MergeSort.
*/
template<typename T>void Merge(T* arr, int arr_left, int arr_mid, int arr_right);
template<typename T>
inline void Merge(T* arr, int arr_left, int arr_mid, int arr_right)
{
	//copy
	int nL = arr_mid - arr_left + 1;
	int nR = arr_right - arr_mid;
	T* Left = (T*)malloc(sizeof(T) * nL);
	T* Right = (T*)malloc(sizeof(T) * nR);
	for (int i = 0; i < nL; i++)
	{
		Left[i] = arr[arr_left + i];
	}
	for (int j = 0; j < nR; j++)
	{
		Right[j] = arr[arr_mid + 1 + j];
	}
	//sort: Depend on the array with less elements.
	int i = 0, j = 0, k = arr_left;
	while (i < nL && j < nR)
	{
		if (Left[i] < Right[j])
		{
			arr[k] = Left[i];
			i++;
		}
		else
		{
			arr[k] = Right[j];
			j++;
		}
		k++;
	}
	//left
	while (i < nL)
	{
		arr[k] = Left[i];
		k++; i++;
	}
	while (j < nR)
	{
		arr[k] = Right[j];
		k++; j++;
	}
	//free
	free(Left);
	free(Right);
}
/*
* @brief: MergeSort
* @param: an array and its left and right index.
*/
template<typename T>void MergeSort(T* arr, int arr_left, int arr_right);
template<typename T>
inline void MergeSort(T* arr, int arr_left, int arr_right)
{
	if (arr_left >= arr_right) { return; }
	int arr_mid = arr_left + (arr_right - arr_left) / 2;
	MergeSort(arr, arr_left, arr_mid);
	MergeSort(arr, arr_mid + 1, arr_right);
	Merge(arr, arr_left, arr_mid, arr_right);
}