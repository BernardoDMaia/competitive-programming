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
    int n, m; cin >> n >> m;
    vector<vi>adj(n);
    FOR(i,0,m){
        int x, y; cin >> x >> y;
        x--;y--;
        adj[x].pb(y);
        adj[y].pb(x);
    }

    int w; cin >> w;
    vector<vi>days(n, vi(w));
    FOR(i,0,n){
        FOR(j,0,w){
            char c; cin >> c;
            days[i][j] = (c == 'o'? 1 : 0);
        }
    }

    vector<vi>topo(n);
    FOR(i,0,w){
        FOR(j,0,n){
            
        }
    }

}

int main(){
    fastio
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
