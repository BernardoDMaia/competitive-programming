#include <bits/stdc++.h>
using namespace std;
#define int long long
using vi = vector<int>;
#define FOR(i,a,b) for(int i =a;i<b;i++)
#define all(x) x.begin(), x.end()
using pii = pair<int,int>;
#define pb push_back
#define sz(x) x.size()
#define deb(x) cerr << #x << "= " << x << "\n";
#define deb2(x,y) cerr << #x << "= " << x << ", "<< #y << "= " << y << "\n";
const int MOD = 1e9 + 7;
//ctrl+alt+a p/ accepted

void solve(){
    int n; cin >> n;
    vector<vi> adj(n);
    FOR(i,0,n-1){
        int x, y; cin >> x >> y;
        adj[x-1].pb(y-1);
        adj[y-1].pb(x-1);
    }

    vector<vi> dp(n, vi(2, 1)); vi vis(n,0);
    auto dfs = [&](auto &&self, int u) -> void {
        vis[u] = 1;
        bool ok = true;
        for(int v : adj[u]){
            if(!vis[v]){
                ok = false;
                self(self, v);
                dp[u][0] = dp[u][0] * (dp[v][0] + dp[v][1]) % MOD;
                dp[u][1] = dp[u][1] * dp[v][0] % MOD;
            }
        }
    };

    dfs(dfs,0);

    cout << (dp[0][0] + dp[0][1]) % MOD << "\n"; 
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--)
    solve();
    return 0;
}