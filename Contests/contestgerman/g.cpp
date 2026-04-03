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
    int n,m; cin >> n >> m;
    vector<vc>grid(n, vc(m));
    vector<vi>vis(n,vi(m));

    FOR(i,0,n) FOR(j,0,m) grid[i][j];

    int currx = 0, curry = 0, lastcx = 0, lastcy = 0;
    FOR(i,0,n){
        currx = i;
        curry = 0;lastcx = 0; lastcy = 0;
        while(currx + curry != n-2){
            vis[currx][curry] = 1;
            if(grid[currx][curry] = 'C'){
                lastcx = currx;
                lastcy = curry;
            }
        }
    }

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}