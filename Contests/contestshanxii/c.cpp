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

void solve(){
    int n; cin >> n;
    vector<vi> adj(2*n); 
    vi indegree(2*n, 0), dp(2*n, 0);

    FOR(i,0,n){
        int x; cin >> x;
        x--;
        adj[i].pb(x);
        indegree[x]++;
    }

    queue<int>q;
    FOR(i,0,2*n){
        if(indegree[i] == 0) q.push(i);
    }

    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int v : adj[u]){
            dp[v] = max(dp[u]+1, dp[v]);
            indegree[v]--;
            if(indegree[v] == 0) q.push(v);
        }
    }

    int ans = 0;
    for(int v : indegree) if(v>=1) ans++;

    FOR(i,n,2*n){
        ans += dp[i];
    }

    cout << ans << "\n";

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
}   