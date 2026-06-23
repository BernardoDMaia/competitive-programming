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

const int MOD = 998244353;

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
    int q; cin >> q;
    queue<pll>f;
    ll prodA = 1;
    ll bfinal = 0;
    while(q--){
        int tp; cin >> tp;
        if(tp == 0){
            ll a, b; cin >> a >> b;
            f.push({a,b});
            prodA = (prodA * a) % MOD;
            bfinal = (b + (a*(bfinal))%MOD)%MOD;
        }
        else if(tp == 1){
            auto [a,b] = f.front();
            f.pop();
            prodA = (prodA * inv(a)) % MOD;
            ll retirar = (prodA * b)%MOD;
            bfinal = (bfinal - retirar + MOD) % MOD;
        }
        else{
            ll x; cin >> x;
            ll ans = (x*prodA)%MOD;
            ans = (ans + bfinal) % MOD;
            cout << ans << "\n";
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