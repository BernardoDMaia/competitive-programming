#include <bits/stdc++.h>
using namespace std;

#define fastio cin.tie(0)->sync_with_stdio(0);
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define deb(k) cerr << #k << ":" << k << "\n";
#define pb push_back
using ll = long long ;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int,int>;

const int MOD = 1e9 + 7;
const ll INF = 1e18;

void solve(){
    int n, m, k; cin >> n >> m >> k;
    vector<vi> adj(n);
    vi vis(n,0);

    FOR(i,0,m){
        int x, y; cin >> x >> y;
        x--;y--;
        adj[x].pb(y);
    }

    auto dfs = [&](auto &&self, int u) -> void {

    };

    
}

int main(){
    fastio
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
