#include <bits/stdc++.h>
using namespace std;

int partition(vector<int>& v, int low, int high){
    int i = low-1;
    for(int j = low; j < high; ++j){
        if(v[j]<v[high]){
            i += 1;
            swap(v[i],v[j]);
        }
    }
    swap(v[i+1],v[high]);
    return i+1;
}

void quick_sort(vector<int>& v, int low, int high){
    if(low<high){
        int par = partition(v,low,high);
        quick_sort(v,low,par-1);
        quick_sort(v,par+1,high);
    }
}

int main() {
	int n;
	cin >> n ;
	vector<int> v(n);
	for(int i = 0; i < n ;++i){
	    cin >> v[i];
	}
	quick_sort(v,0,n-1);
	for(int i = 0; i < n ; ++i){
	    cout << v[i] << " ";
	}
	cout << endl;
}
