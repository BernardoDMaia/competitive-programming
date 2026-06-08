#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
#define FOR(i,a,b) for(int i = a; i<(b);i++)
const int MOD = 1e9 + 7;
const int MAXN = 2e5+5;
int spf[MAXN];

void crivo_spf(){
    FOR(i,2,MAXN) spf[i] = i;
    for(int i = 2; i*i < MAXN; i++){
        if(spf[i]==i){
            for(int j = i*i; j < MAXN; j+=i) if(spf[j] == j) spf[j] = i;
        }
    }
}

map<int,int> fat(int x){
    map<int,int> ret;
    while(x != 1){
        ret[spf[x]]++;
        x /= spf[x];
    }
    return ret;
}

ll fast_exp(ll b, ll e){
    ll res = 1;
    while(e){
        if(e & 1) res = (res*b) % MOD;
        b = (b*b) % MOD;
        e /= 2;
    }
    return res;
}

void solve(){
    crivo_spf();
    int n; cin >> n;
    vi v(n+1), vis(n+1,0);
    FOR(i,1,n+1) cin >> v[i];

    vi tam_comp;
    FOR(i,1,n+1){
        int tam = 0;
        if(!vis[i]){
            int j = i;
            while(!vis[j]){
                vis[j] = 1;
                j = v[j];
                tam++;
            }
            tam_comp.push_back(tam);
        }
    }

    map<int,int> freq;
    for(int v : tam_comp) {
        map<int,int> m = fat(v);
        for(auto [l,r] : m){
            freq[l] = max(freq[l], r);
        }
    }

    ll ans = 1;
    for(auto [l,r] : freq){
        ans *= fast_exp((ll)l,(ll)r);
        ans %= MOD;
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