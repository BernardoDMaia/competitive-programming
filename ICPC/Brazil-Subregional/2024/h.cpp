#include <bits/stdc++.h>
using namespace std;
#define int long long
using vi = vector<int>;
#define FOR(i,a,b) for(int i =a;i<b;i++)
#define all(x) x.begin(), x.end()
#define deb(x) cerr << #x << "= " << x << "\n";
#define deb2(x,y) cerr << #x << "= " << x << ", "<< #y << "= " << y << "\n";
const int INF = 1e18;
#define pb push_back

void solve(){
 int n, m, q; cin >> n>> m >> q;
    vector<vi> adj(m);
    vector<vi> caras(n);
// deb(m);
    FOR(i,0,n){
        int x; cin >> x;
        vi v(x); 
        FOR(j,0,x){
            cin >> v[j];v[j]--;
            caras[i].pb(v[j]);
        }
        FOR(j,0,x){
            FOR(k,j,x){
                if(j==k) continue;
                adj[v[k]].pb(v[j]);
                adj[v[j]].pb(v[k]);
            }
        }
    }
    // cerr<< "adj\n";
    // FOR(i,0,m){
    //     FOR(j,0, adj[i].size()){
    //         cerr << adj[i][j] << " ";
    //     }
    //     cerr << endl;
    // }


    vector<vi> dist(m+1, vi(m+1, INF)); // dist da lingua i a j
    vi vis(m+5);
    auto bfs = [&] (int u) -> void{
        queue<pair<int, int>> q;
        q.push({u,0});
        vis[u]=1;

        while(!q.empty()){
            auto [v, c] = q.front();
            // deb2(v,c);
            q.pop();
            for(auto k : adj[v]){
                if(!vis[k]){
                    vis[k]=1;
                    q.push({k, c+1});
                    dist[u][k] = c+1;
                }
            }

        }

    };

    FOR(i,0, m){
        vis.assign(m+5, 0);
        bfs(i);
        // deb(i);
    }
    
    

    while(q--){
        int a, b; cin >> a >> b; a--;b--;
        int ans = INF;
        // deb2(a,b);
        for(int l1: caras[a]){
            for(int l2: caras[b]){
                // deb(dist[l1][l2]);
                if(l1==l2){
                    ans= 0;
                    break;
                }
                ans = min(ans, dist[l1][l2]);
            }
        }
        if(ans == INF) cout << "-1\n";
        else cout << ans << "\n";
    }




}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}