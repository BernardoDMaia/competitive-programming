#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);
    //freopen("mootube.in", "r", stdin);
    //freopen("mootube.out", "w", stdout);
    int n, q; cin >> n >> q;
    vector<vector<pair<int,int>>> tree(n);

    for(int i = 0; i < n-1; i++){
        int x, z, w; cin >> x >> z >> w;
        tree[x].push_back({z, w});
        tree[z].push_back({x, w});
    }

    while(q--){
        int k, y; cin >> k >> y;int cont  = 0 ;

        auto dfs = [&](auto &&self,int u, int pai =-1) -> void {
            for(auto[v,p] : tree[u]){
                if(v!=pai && p >= k){
                    cont++;
                    self(self, v, u);
                }
            }
        };
        
        cout << cont << endl;
    }
}