// Sorter.cpp
// Created by Robin Rowe 2019-01-22
// License MIT open source


// https://github.com/indy256/codelibrary/blob/master/cpp/sort/sort.cpp
// The Unlicense

void merge_sort(vector<int> &a, int low, int high)
{	if(high - low < 2)
	{	return;
	}
	int mid = (low + high) >> 1;
	merge_sort(a, low, mid);
	merge_sort(a, mid, high);
	vector<int> b;
	copy(a.begin() + low, a.begin() + mid, back_inserter(b));
	for(int i = low, j = mid, k = 0; k < b.size(); i++)
	{	if(j == high || b[k] <= a[j])
		{	a[i] = b[k++];
		}
		else
		{	a[i] = a[j++];
		}
	}
}

void counting_sort(vector<int> &a)
{	int max = *max_element(a.begin(), a.end());
	vector<int> cnt(max + 1);
	for(int x : a)
	{	++cnt[x];
	}
	for(int i = 1; i < cnt.size(); i++)
	{	cnt[i] += cnt[i - 1];
	}
	int n = a.size();
	vector<int> b(n);
	for(int i = 0; i < n; i++)
	{	b[--cnt[a[i]]] = a[i];
	}
	a = b;
}