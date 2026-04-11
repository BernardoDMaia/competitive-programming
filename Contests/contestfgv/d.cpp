#include <bits/stdc++.h>
using namespace std;
typedef long long ll;


void solve(){
    ll c, r, s; cin >> c >> r >> s;

    if(s == 1){
        cout << c << " " << c << "\n";
        return;
    }

    ll total = (r+c+(s-1))/s;
    ll ruins = (r+(s-1))/s;
    cout << total-ruins << " " << max(total-r, 0ll) << "\n";


}

int main(){
    cin.tie(0), ios_base::sync_with_stdio(false);
    int t; cin >> t;
    while(t--) solve();
}