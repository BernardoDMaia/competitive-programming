#include <bits/stdc++.h>
using namespace std;
using ll= long long;
using vi = vector<int>;
using vll =vector<ll>;
using vpii =vector<pair<int,int>>;
#define FOR(i,a,b) for(int i=a;i<(b);i++)
#define all(x) x.begin(), x.end()
#define pb push_back
#define sz(x) (int)x.size()

void solve(){
    int n,m,k; cin >> n >> m >> k;
    vector<vpii> adj(n);

    FOR(i,0,m){
        int a,b,c; cin >> a >> b >> c;
        a--;b--;
        adj[a].pb({b,c});
    }

    vector<vi> dist(n, vi(101, 2e9)); //menor dist para chegar no indice i com custo x; 
    queue<pair<int,int>> q; //vertice e peso
    q.push({0,0});
    dist[0][0] = 0;

    while(!q.empty()){
        auto [s,x] = q.front();
        if(s == n-1){
            cout << dist[s][x] << endl;
            return;
        }
        q.pop();
            
        for(auto[v,d] : adj[s]){   
            if(x + d <= k && dist[v][d+x] == 2e9){
                dist[v][d+x] = dist[s][x] + 1; 
                q.push({v, d+x});     
            }
        }
    }

    cout << -1 << endl;
    
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
}