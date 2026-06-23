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
    ll n; cin >> n;
    vector<vi> v(n);
    map<int,ll> mp;
    FOR(i,0,n){
        int k; cin >> k;
        FOR(j,0,k){
            int x; cin >> x;
            v[i].pb(x);
            mp[x]++;
        }
    }

    ll ans = 0;
    ll num = 0, den = 0;
    ll p = inv(n*n %MOD);
    FOR(i,0,n){
        num = 0;
        den = sz(v[i]);
        for(int x : v[i]){
            num = (mp[x] + num) % MOD;
        }
        ll pcrianca = (num * inv(den)) % MOD;
        ans = (ans+pcrianca)%MOD;
    }

    ans = (p*ans)%MOD;

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