#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for(int i = 0 ; i < n; ++i){
        cin >> v[i];
    }
    for(int i = 0; i < n-1; ++i){
        int min_ind = i;
        for(int j = i; j < n; ++j){
            if(v[min_ind]>v[j]){
                min_ind = j;
            }
        }
        swap(v[min_ind],v[i]);
    }
    for(int i = 0 ; i < n; ++i){
        cout << v[i] << " ";
    }
    cout << endl;
}
