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
    int n, x; cin >> n >> x;
    vi a(n), v(n);
    FOR(i,0,n) cin >> a[i];
    FOR(i,0,n) cin >> v[i];

    vi dp(x+1, 0);

    FOR(i,0,n){
        for(int c = x; c >= a[i]; c--){
            dp[c] = max(dp[c], dp[c - a[i]] + v[i]);
        }
    }

    cout << *max_element(all(dp)) << "\n";
    
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