#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
#define FOR(i,a,b) for(int i = a; i<(b);i++)

void solve(){
    int n; cin >> n;
    vi v(1e6+5);

    FOR(i,0,n){
        int x; cin >> x;
        v[x]++;
    }

    for(int i = 1e6; i >= 0; i--){
        int ans = 0;
        for(ll j = i; j < 1e6+5; j += i){
            ans += v[j];
            if(ans >= 2){
                cout << i << "\n";
                return;
            }
        }
    }

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1; 
    //cin >> t;
    while(t--){
        solve();
    }
    return 0;
}