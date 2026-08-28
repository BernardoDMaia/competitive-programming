#include <bits/stdc++.h>
using namespace std;
#define int long long
using vi = vector<int>;
#define FOR(i,a,b) for(int i =a;i<b;i++)
#define all(x) x.begin(), x.end()
using pii = pair<int,int>;
#define pb push_back
#define sz(x) x.size()
#define deb(x) cerr << #x << "= " << x << "\n";
#define deb2(x,y) cerr << #x << "= " << x << ", "<< #y << "= " << y << "\n";
//ctrl+alt+a p/ accepted

void solve(){
    int n; cin >> n;
    vi v(n); FOR(i,0,n) cin >> v[i];
    vi dp(1e5+5, 0);
    dp[0] = 1;

    for(int x : v){
        for(int s = 1e5+4; s >= x; s--){
            dp[s] |= dp[s-x];
        }
    }

    vi ans;
    FOR(i,1,1e5+5) if(dp[i]) ans.pb(i);
    cout << sz(ans) << "\n";
    for(int x : ans) cout << x << " ";
    cout << "\n";
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--)
    solve();
    return 0;
}