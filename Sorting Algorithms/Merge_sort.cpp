#include <bits/stdc++.h>
using namespace std;

void merge(vector<int>& v, int low, int mid, int high){
    int n = v.size();
    int l1 = low, l2 = mid+1;
    vector<int> ans;
    while(l1<=mid && l2<=high){
        if(v[l1]<v[l2]){
            ans.push_back(v[l1]);
            l1++;
        }
        else{
            ans.push_back(v[l2]);
            l2++;
        }
    }
    while(l1<=mid){
        ans.push_back(v[l1]);
        l1++;
    }
    while(l2<=high){
        ans.push_back(v[l2]);
        l2++;
    }
    int l = 0;
    for(int i = low; i<=high; ++i){
        v[i] = ans[l];
        l++;
    }
}

void merge_sort(vector<int>& v, int low, int high){
    // cout << low << " " << high << endl;
    if(low >= high){
        return;
    }
    int mid = low+(high-low)/2;
    merge_sort(v,low,mid);
    merge_sort(v,mid+1,high);
    merge(v,low,mid,high);
}

int main() {
	int n;
	cin >> n;
	vector<int> v(n);
	for(int i = 0; i < n ; ++i){
	    cin >> v[i];
	}
    merge_sort(v,0,n-1);
    for(int i = 0; i < v.size(); ++i){
        cout << v[i] << " ";
    }
    cout << endl;
}
//O(nlog(n)) Time Complexity
//O(n) Space Complexity