#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int l, r, d, u; cin >> l >> r >> d >> u;
    ll ans = 0;

    for(int i = l; i <= r; i++){
        if(abs(i)%2 == 0) ans += (ll) max(min(u, abs(i)-1)-max(d,-abs(i)+1) + 1, 0);
    }

    for(int i = d; i <= u; i++){
        if(abs(i)%2 == 0) ans += (ll) max(min(r, abs(i))-max(l,-abs(i)) + 1, 0);
    }
    cout << ans << endl;   
}