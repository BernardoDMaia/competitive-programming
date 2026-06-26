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

const int MAXN = 1e6+5;
ll fat[MAXN], invfat[MAXN];

void build_fat(){
    fat[0] = 1;
    for(int i = 1; i < MAXN; i++){
        fat[i] = (fat[i-1]*i)%MOD;
    }
    
    invfat[MAXN-1] =inv(fat[MAXN-1]);
    for(int i = MAXN-2; i >= 0; i--){
        invfat[i] = (invfat[i+1]*(i+1)) % MOD;
    }
}

ll nCr(ll n, ll k){
    if(k < 0 || k > n) return 0;
    return fat[n] * invfat[k] % MOD *invfat[n-k] % MOD;
}

void solve(){
    build_fat();
    int n; cin >> n;
    FOR(i,0,n){
        int a, b; cin >> a >> b;
        cout << nCr(a,b) << "\n";
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