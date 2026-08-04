    #include <bits/stdc++.h>
    using namespace std;
    #define int long long
    using vi = vector<int>;
    #define FOR(i, a, b) for (int i = a; i < (b); i++)
    #define all(x) x.begin(), x.end()
    #define pb push_back
    #define sz(x) (int)(x).size()
    #define deb(x) cerr << #x << " = " << x << "\n";
    #define deb2(x,y) cerr << #x << "=" << x << ", " << #y << "=" << y << "\n";
    #define deb3(x,y,z) cerr << #x << "=" << x << ", " << #y << "=" << y << ", " << #z << "=" << z << "\n";

    void solve(){
        int n, m; cin >> n >> m;
        vector<vector<pair<int,int>>> adj(n);
        FOR(i,0,m){
            int u, v, a; cin >> u >> v >> a;
            u--;v--;
            adj[u].pb({a,v});
        }

        queue<int>q;
        q.push(0);
        vi vis2(n,0);
        vis2[0] = 1;
        while(!q.empty()){
            int u = q.front();
            q.pop();

            for(auto[dv,v]: adj[u]){
                if(!vis2[v]){
                    vis2[v] = 1;
                    q.push(v);
                }
            }
        }

        if(vis2[n-1] == 0){
            cout << -1 << "\n";
            return;
        }

        vi vis;
        int ok;
        auto dfs = [&](auto &&self, int u, int x) -> void {
            vis[u] = 1;
            if(u == n-1) ok = true;
            for(auto [dv,v]: adj[u]){
                if(!vis[v] && (dv & x) == x) self(self,v,x);
            }
        };

        int mask = 0;
        for(int i = 30; i >= 0; i--){
            int curr = mask + (1 << i);
            vis.assign(n,0);
            ok = 0;
            dfs(dfs,0,curr);
            if(ok) mask = curr;
        }

        cout << mask << "\n";

    }

    signed main(){
        ios::sync_with_stdio(false); 
        cin.tie(0);
        int t = 1;
        //cin >> t;
        while(t--){
            solve();
        }
        return 0;
    }