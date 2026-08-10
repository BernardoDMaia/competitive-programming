#include <bits/stdc++.h>
using namespace std;
#define int long long
using vi = vector<int>;
#define FOR(i,a,b) for(int i =a;i<(b);i++)
#define deb(x) cerr << #x << " = " << x << "\n";
#define all(x) x.begin(), x.end()
#define sz(x) x.size()
#define pb push_back

void solve(){
    int n,m; cin >> n >> m;
    vector<vi> adj(m+105);
    FOR(i,0,n){
        int k; cin >> k;
        FOR(j,0,k){
            int x; cin >> x;
            adj[x].pb(m+i+1);
            adj[m+i+1].pb(x);
        }
    }
    vi comp(m+105,-1);
    vi vis(m+105);
    vi pai(m+105);
    iota(all(pai),0);
    auto dfs = [&](auto &&self, int u, int componente) -> void {
        vis[u]=1;
        comp[u]=componente;
        for(int v : adj[u]){
            if(vis[v]) continue;
            pai[v]=u;
            self(self, v, componente);
        }
    };
    FOR(i,1,m+1){
        if(!vis[i]){
            dfs(dfs,i,i);
        }
    }
    // for(auto x : comp) cout << x << " ";
    // cout << "\n";
    // for(auto x: pai) cout << x << " ";
    // cout << "\n";
    int q; cin >> q; 
    while(q--){
        int x,y; cin >> x >> y;
        if(comp[x]!=comp[y]){
            cout << "-1\n";
            continue;
        }
        vi ans;
        int curr = x;
        int fds=0;
        while(pai[curr]!=curr){
            //deb(curr);
            if(curr>m) ans.pb(curr-m);
            else{
                fds++;
                ans.pb(curr);
            } 
            curr=pai[curr];
        }
        vi ans2;
        curr=y;
        while(pai[curr]!=curr){
            if(curr>m) ans2.pb(curr-m);
            else{
                ans2.pb(curr);
                fds++;
            } 
            curr=pai[curr];
        }
        cout << fds+1 << "\n";
        for(auto v:ans) cout << v << " ";
        cout << comp[x] << " ";
        reverse(all(ans2));
        for(auto v:ans2) cout << v << " ";
        cout << "\n";
    }
}  

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}