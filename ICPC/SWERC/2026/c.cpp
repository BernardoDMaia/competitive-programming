#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using pll = pair<ll,ll>;
#define FOR(i,a,b) for(int i = a;i<(b);i++)
#define all(x) x.begin(), x.end()
#define deb(x) cerr<< #x << "=" << x << "\n";
#define pb push_back

void solve(){
    int n, m; cin >> n >> m;
    int tam = (n*m)/2;
    vector<vi> adj(tam);
    map<pair<int,int>, int> mp;
    vi p;

    FOR(i,0,n){
        int lst = 0;
        FOR(j,0,m){
            int x; cin >> x;
            x--;
            if(j == 0) p.pb(x);
            else{
                if(mp[{lst,x}] == 0){
                    adj[lst].pb(x);
                    mp[{lst,x}] = 1;
                }
            }
            lst = x;
        }
    }

    vi vis(tam, 0);
    auto dfs = [&](auto &&self, int u) -> void {
        vis[u] = 1;
        cout << u+1 << " ";
        for(int v : adj[u]){
            if(!vis[v]) self(self,v);
        }
    };

    for(int v : p){
        if(!vis[v]) dfs(dfs,v);
    }

    cout << "\n";
    
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1; 
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}