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

ll fexp(ll b, ll e, ll m){
    ll res = 1;
    while(e){
        if(e & 1) res = (res*b)%m;
        b = (b*b)%m;
        e /= 2;
    }
    return res;
}

ll inv(ll x, ll m){
    return fexp(x, m-2, m);
}

void solve(){
    int n,m,q; cin >> n >> m >> q;
    vector<pair<int,int>> interv(m);

    FOR(i,0,m){
        int l,r; cin >> l >> r;
        l--;r--;
        interv[i] = {l,r};
    }

    while(q--){
        int l,r,k; cin >> l >> r >> k;
        l--;r--;
        
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