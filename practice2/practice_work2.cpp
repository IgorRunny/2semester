#include <iostream>

template <typename T>
void MScopy(T* arr1, T* arr2, const int& N)
{
	const long long* marker1L = (const long long*)arr1;
	long long* marker2L = (long long*)arr2;
	int n = (sizeof(T) * N) / sizeof(long long);
	
	for (int i = 0; i < n; ++i)
	{
		*(marker2L) = *(marker1L);
		marker2L++;
		marker1L++;
	}

	n = (sizeof(T) * N) % sizeof(long long);
	const char* marker1Ch = (const char*)marker1L;
	char* marker2Ch = (char*)marker2L;

	for (int i = 0; i < n; ++i)
	{
		*(marker2Ch) = *(marker1Ch);
		marker2Ch++;
		marker1Ch++;
	}
}

int main()
{
	const int N = 1000;
	int arr1[N] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 20 };
	int arr2[N] = { 0 };
	MScopy(arr1, arr2, N);
}
