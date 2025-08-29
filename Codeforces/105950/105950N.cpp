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
    vector<vi>dp(n, vi(n)), vis(n, vi(n));

    queue<pair<int,int>>q;
    q.push({0,0});
    vis[0][0] = 1;

    vi dx={2,2, -2, -2, 1, 1, -1, -1};
    vi dy={1,-1, 1, -1, 2, -2, 2, -2};

    while(!q.empty()){
        auto [u,v] = q.front();
        q.pop();
        FOR(i,0,8){
            FOR(j,0,8){
                int vx = u+dx[i];
                int vy = v+dy[i];
                if(vx >=0 && vx<n && vy>=0 && vy<n && !vis[vx][vy]){
                    dp[vx][vy] = dp[u][v]+1;
                    vis[vx][vy] = 1;
                    q.push({vx,vy});
                }
            }
        }
    }

    FOR(i,0,n){
        FOR(j,0,n){
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}