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
    int n, a, b, c; cin >> n >> a >> b >> c;
    vi dp(n+1,0);
    if(a <= n) dp[a] = 1;
    if(b <= n) dp[b] = 1;
    if(c <= n) dp[c] = 1;
    FOR(i,1,n+1){
        if(dp[i]){
            if(a+i <= n) dp[a+i] = max(dp[i]+1, dp[i+a]);
            if(b+i <= n) dp[b+i] = max(dp[i]+1, dp[i+b]);
            if(c+i <= n) dp[c+i] = max(dp[i]+1, dp[i+c]);
        }
    }

    cout << dp[n] << "\n";
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