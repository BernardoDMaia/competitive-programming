#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAXN = 1e5+7;

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);
    int n; cin >> n;
    vector<ll>carga(n + 1);
    vector<vector<tuple<ll,ll>>> tree(n+1);

    for(int i = 1; i <= n; i++){
        cin >> carga[i];
    }

    for(int i = 0; i < n-1; i++){
        ll u, v, w; cin >> u >> v >> w;
        tree[u].push_back({v,w});
        tree[v].push_back({u,w});
    }

    ll ans = 0;

    auto dfs = [&](auto &&self, int root, int pai = -1, ll peso = 0) -> void {       
        for(auto [idx,weight] : tree[root]){
            if(idx != pai) self(self,idx,root,weight);
        }
        
        if(pai != -1){
            carga[pai] += carga[root];
            ll vv = abs(carga[root]);
            ans += 1LL*peso*vv;
        }
    };

    dfs(dfs,1);

    cout << ans << endl;
}