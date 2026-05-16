#include <bits/stdc++.h>
using namespace std;
using ll = long long ;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int,int>;
#define FOR(i, a, b) for(int i = a; i < b; i++)
#define all(x) x.begin() , x.end()
#define pb push_back

const int MOD = 1e9 + 7;

ll fexp(ll b, ll e){
    ll res = 1;
    while(e){
        if(e & 1) res = (res*b) % MOD;
        b = (b * b) % MOD;
        e /= 2;
    }
    return res;
}

ll inv(ll x){
    return fexp(x, MOD - 2);
}

const int MAXN = 1e6+5;

ll fat[MAXN], invfat[MAXN];

void build_fat(){
    fat[0] = 1;
    FOR(i,1,MAXN) fat[i] = (fat[i-1] * i) % MOD;

    invfat[MAXN-1] = inv(fat[MAXN-1]);
    for(int i = MAXN - 2; i >= 0; i--) invfat[i] = (invfat[i+1] * (i+1)) % MOD;
}

ll nCr(ll n, ll k){
    if(k<0 || k>n) return 0;
    return fat[n]* invfat[k] % MOD * invfat[n - k] % MOD;
}

void solve(){
    ll n, k; cin >> n >> k;
    multiset<ll> bigger,smaller;
    vll p(n);
    build_fat();

    FOR(i,0,n){
        ll x; cin >> x;
        p[i] = x;
        if(bigger.size() < k) bigger.insert(x);
        else{
            auto it = bigger.lower_bound(x);
            if(it != bigger.begin()){
                ll sla = *bigger.begin();
                if(smaller.size() < k) smaller.insert(-sla);
                else{
                    auto it2 = smaller.lower_bound(-sla);
                    if(it2 != smaller.begin()){
                        smaller.erase(smaller.begin());
                        smaller.insert(-sla);
                    }
                }
                bigger.erase(bigger.begin());
                bigger.insert(x);
            }
            else{
                if(smaller.size() < k) smaller.insert(-x);
                else{
                    auto it2 = smaller.lower_bound(-x);
                    if(it2 != smaller.begin()){
                        smaller.erase(smaller.begin());
                        smaller.insert(-x);
                    }
                }
            }
        }
    }

    ll min_maior = *bigger.begin();
    ll max_menor = -(*smaller.begin());
    ll cont1 = 0, cont2 = 0;

    ll equals = 1;
    for(ll v : p){
        if(v != p[0]) equals = 0;
        if(v == min_maior) cont1++;
        if(v == max_menor) cont2++;
    }

    ll sum1 = 0, sum2 = 0;
    ll qtd1 = 0, qtd2 = 0;
    for(ll v: bigger){
        sum1 += v;
        if(v == min_maior) qtd1++;
    }
    for(ll v: smaller){
        sum2 -= v;
        if(-v == max_menor) qtd2++;
    }

    if(min_maior == max_menor) cont2 -= qtd1;
    ll sum = sum1 - sum2;

    ll ans = (nCr(cont1, qtd1) * nCr(cont2,qtd2))%MOD;
    if(equals) ans *= inv(2);

    cout << sum << " " << ans%MOD << "\n";

}

int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
    return 0;
}