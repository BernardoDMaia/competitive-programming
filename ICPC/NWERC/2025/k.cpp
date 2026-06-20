#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using pll = pair<ll,ll>;
#define FOR(i,a,b) for(int i = a;i<(b);i++)
#define all(x) x.begin(), x.end()
#define deb(x) cerr<< #x << "=" << x << "\n";
#define sz(x) x.size()
#define pb push_back

void solve(){
    int n, m, k; cin >> n >> m >> k;
    vector<vector<pll>> adj(n);
    FOR(i,0,m){
        ll x, y, w; cin >> x >> y >> w;
        x--;y--;
        adj[x].pb({w,y});
        adj[y].pb({w,x});
    }

    vector<pair<ll,double>> lojas(k);
    int ok = 0;
    FOR(i,0,k){
        ll x; cin >> x;
        x--;
        double p; cin >> p;
        if(p == 1.0) ok = 1;
        lojas[i] = {x,p};
    }

    if(!ok){
        cout << "impossible\n";
        return;
    }

    auto dijkstra = [&](int start) -> vll {
        vll dist(n, 1e18);
        using T = pair<ll,ll>;
        priority_queue<T, vector<T>, greater<T> > pq;
        dist[start] = 0LL;
        pq.push({dist[start],start});

        while(!pq.empty()){
            auto [du,u] = pq.top();
            pq.pop();
            if(du != dist[u]) continue;
            for(auto [dv,v] : adj[u]){
                if(du+dv < dist[v]){
                    dist[v] = du+dv;
                    pq.push({dist[v], v});
                }
            }
        }

        return dist;
    };

    vll d1 = dijkstra(0);
    vll d2 = dijkstra(n-1);

    FOR(i,0,k){
        auto [idx,p] = lojas[i];
        ll df = d1[idx]+d2[idx];
        lojas[i] = {df,p};
    }

    sort(all(lojas));

    double ans = 0;
    double psim = 1.0;
    double pnao = 1.0;

    FOR(i,0,k){
        auto [dfinal,p] = lojas[i];
        psim = p;
        double ve = dfinal*psim*pnao;
        ans += ve;
        pnao *= (1.0 - psim);
        if(psim == 1.0) break;
    }

    cout << fixed << setprecision(10);
    cout << ans << "\n";

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--){
        solve();    
    }
    return 0;
}