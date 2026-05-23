#include <bits/stdc++.h>
using namespace std;
using ll = long long ;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int,int>;
#define FOR(i, a, b) for(int i = a; i < b; i++)
#define all(x) x.begin() , x.end()
#define pb push_back

void solve(){
    ll n; cin >> n;
    vll a(n);
    FOR(i,0,n) cin >> a[i];

    ll mdc = a[0];
    FOR(i,1,n) mdc = __gcd(mdc, a[i]);

    ll ans = 0;
    FOR(i,0,n) ans += a[i]/mdc;

    cout << ans << "\n";
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; 
    //cin >> t;
    while(t--){
        solve();
    }
}