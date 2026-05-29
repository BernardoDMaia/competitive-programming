#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
#define FOR(i,a,b) for(int i =a;i<(b);i++)
#define all(x) x.begin(), x.end()
#define pb push_back
#define deb(x) cerr << #x << "=" <<  x << "\n";

const int MAXN = 1e5+5;

void solve(){
    int n, m; cin >> m >> n;
    vector<vector<pair<int,int>>>adj(n);
    vi vis(m+1), obj(n), curr(n);
    FOR(i,0,m){
        int x, y; cin >> x >> y;
        x--; y--;
        adj[x].pb({y,i+1});
        adj[y].pb({x,i+1});
    }

    FOR(i,0,n) cin >> obj[i];
    bool ok;
    vi ans;

    auto dfs = [&] (auto &&self, int u) -> void {
        if(obj[u] == curr[u]){
            ok = true;
            return;
        }
        if(ok) return;
        
        for(auto [v, idx] : adj[u]){
            if(!vis[idx] && !ok){
                if(!ok){
                    vis[idx] = 1;
                    curr[u] = !curr[u];
                    curr[v] = !curr[v];
                    ans.pb(idx);
                }
                self(self, v);
                if(!ok){
                    ans.pop_back();
                    curr[u] = !curr[u];
                    curr[v] = !curr[v];
                }
            }
        }
    };

    FOR(i,0,n){
        if(curr[i] != obj[i]){
            ok = false;
            dfs(dfs, i);
            if(!ok){
                cout << "-1\n";
                return;
            }
        }
    }

    cout << ans.size() << "\n";
    for(int v : ans) cout << v << " ";
    cout << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();

    return 0;
} 