#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    int n, k; cin >> n >> k;
    vector<int>a(n);
    
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    
    int mdc; cin >> mdc;
    
    for(int i = 1; i < k; i++){
        int x; cin >> x;
        mdc = __gcd<int>(mdc,x);
    }
    
    int mod = a[0] % mdc;
    int ok = true;
    
    for(int i = 1; i < n; i++){
        if(a[i] % mdc != mod) ok = false;
    }

    if(ok) cout << "Yes" << endl;
    else cout << "No" << endl;
}
