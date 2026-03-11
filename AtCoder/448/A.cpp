#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, x; cin >> n >> x;
    vector<int>v(n);

    for(int i = 0; i < n; i++){
        cin >> v[i];
        if(v[i] < x){
            cout << 1 << endl;
            x = v[i];
        }
        else cout << 0 << endl;
    }

}