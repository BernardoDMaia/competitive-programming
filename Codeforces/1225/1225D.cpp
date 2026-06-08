#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
#define FOR(i,a,b) for(int i = a; i<(b);i++)

const int MAXN = 1e5+5;
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

void solve(){
    int n, k; cin >> n >> k;
    crivo_spf();
    map<vector<pair<int,int>>, ll> freq_sig;
    ll ans = 0;

    FOR(i,0,n){
        int a; cin >> a;
        map<int,int> div = fat(a);

        vector<pair<int,int>> sig, comp;
        for(auto [d,f] : div){
            if(f%k != 0){
                sig.push_back({d, (f%k)});
                comp.push_back({d, (k - (f%k))});
            }
        }

        ans += freq_sig[comp];
        freq_sig[sig]++;
    }

    cout << ans << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();

    return 0;
}