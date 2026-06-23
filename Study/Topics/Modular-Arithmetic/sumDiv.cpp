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

map<ll,ll> div(ll x){
    map<ll,ll> res;
    for(ll i = 2; i * i <= x; i++){
        if(x % i == 0){
            ll e = 0;
            while(x % i == 0){
                x /= i;
                e++;
            }
            res[i] = e;
        }
    }
    if(x > 1) res[x]++;
    return res;
}

void solve(){
    //freopen("sumdiv.in", "r", stdin);
    //freopen("sumdiv.out", "w", stdout);
    ll a,b; cin >> a >> b;
    if (a == 0) { cout << 0 << "\n"; return; }
    if (b == 0 || a == 1) { cout << 1 << "\n"; return; }
    
    map<ll,ll> fat = div(a);
    ll ans = 1;

    for(auto [p, e] : fat){
        ll pg = 0;
        
        if (p % MOD == 0) {
            pg = 1;
        }
       
        else if (p % MOD == 1) {
            ll num_termos = ( ((e % MOD) * (b % MOD)) % MOD + 1 ) % MOD;
            pg = num_termos;
        }
       
        else {
            ll exp = (((e % (MOD-1)) * (b % (MOD-1))) + 1) % (MOD-1);
            ll num = (fexp(p % MOD, exp) - 1 + MOD) % MOD;
            ll den = inv((p - 1) % MOD);
            pg = (num * den) % MOD;
        }
        
        ans = (ans * pg) % MOD;
    }

    cout << ans << "\n";
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