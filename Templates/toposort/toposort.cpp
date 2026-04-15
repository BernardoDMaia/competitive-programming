#include <bits/stdc++.h>
using namespace std;
using ll= long long;
using vi = vector<int>;
using vll =vector<ll>;
using vc =vector<char>;
using vpii =vector<pair<int,int>>;
#define FOR(i,a,b) for(int i=a;i<(b);i++)
#define all(x) x.begin(), x.end()
#define pb push_back
#define sz(x) (int)x.size()

vi toposort(int n, vector<vi> &adj){
    vi in_degree(n, 0);
    
    FOR(u,0,n){
        for(int v : adj[u]) in_degree[v]++;
    }
    
    //priority queue(lexicograficamente menor):
    //priority_queue<int, vector<int>, greater<int>> pq;
    
    queue<int>q; 
    FOR(i,0,n){
        if(in_degree[i]==0) q.push(i);
    }

    vi order;
    
    while(!q.empty()){
        int u = q.front();
        q.pop();
        order.pb(u);

        for(int v : adj[u]){
            in_degree[v]--;
            if(in_degree[v] == 0) q.push(v);
        }
    }

    if(sz(order) != n) return {};
    return order;

}

void solve(){
    int n,m; cin >> n >> m;
    vector<vi>adj(n);

    FOR(i,0,m){
        int x,y; cin >> x >> y;
        x--;y--;
        adj[x].pb(y);
    }

    vi ans = toposort(n, adj);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
}   