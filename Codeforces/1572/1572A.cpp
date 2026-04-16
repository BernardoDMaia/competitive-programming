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
    vi indegree(n, 0);
    FOR(i,0,n){
        for(int v : adj[i]) indegree[v]++;
    }

    queue<int>q;
    FOR(i,0,n){
        if(indegree[i] == 0) q.push(i);
    }

    vi order;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        order.pb(u);
        for(int v : adj[u]){
            if(!--indegree[v]) q.push(v);
        }
    }

    if(sz(order) != n) return {};
    return order;
}

void solve(){
    int n; cin >> n;
    vector<vi>adj(n);

    FOR(i,0,n){
        int x; cin >> x;
        FOR(j,0,x){
            int y; cin >> y;
            y--;
            adj[y].pb(i);
        }
    }

    vi ans = toposort(n, adj);

    if(sz(ans) != n) cout << -1 << "\n";
    else{
        vi dp(n,1);
        for(int u : ans){
            for(int v : adj[u]){
                if(u < v){
                    dp[v] = max(dp[u],dp[v]);
                }
                else{
                    dp[v] = max(dp[v],dp[u]+1);
                }
            }
        }

        cout << max(*max_element(all(dp)),0) << "\n";
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t; cin >> t;
    while(t--){
        solve();
    }
}   