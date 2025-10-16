#include <bits/stdc++.h>
using namespace std;
#define ll long long 

int main(){
    double n, k; cin >> n >> k;
    
    ll ans = max(ceil(n/k), (double)2);

    cout << 5 * ans << endl;
}
