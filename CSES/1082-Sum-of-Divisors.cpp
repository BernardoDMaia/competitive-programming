#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using pll = pair<ll,ll>;
#define FOR(i,a,b) for(int i = a;i<(b);i++)
#define all(x) x.begin(), x.end()
#define deb(x) cerr<< #x << "=" << x << "\n";
#define sz(x) x.size()
#define pb push_back

const int MOD = 1e9+7;

ll fexp(ll b, ll e){
    ll res = 1;
    while(e){
        if(e & 1) res = (res*b)%MOD;
        b = (b*b)%MOD;
        e /= 2;
    }
    return res;
}

ll inv(ll x){
    return fexp(x, MOD-2);
}

void solve(){
    ll n; cin >> n;
    ll l = 1, r = 1;
    ll ans = 0;
    //l e r
    while(l <= n){
        ll k = (n/l);
        r = n/k;
        ll sum = (l+r)%MOD;
        ll sum2 = (r-l+1)%MOD;
        ll m = (sum*sum2)%MOD;
        ll pa = (m*inv(2))%MOD;
        k %= MOD;
        ans += (pa*k)%MOD;
        l = r+1;
    }

    cout << ans % MOD << "\n";
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