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
    string s, t; cin >> s >> t;
    int n = sz(s);
    int m = sz(t);

    vector<vi> dp(n+1, vi(m+1));
    FOR(i,1,n+1){
        FOR(j,1,m+1){
            if(s[i-1] == t[j-1]) dp[i][j] = dp[i-1][j-1] + 1;
            else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }

    string ans = "";
    int i = n, j = m;
    while(i > 0 && j > 0){
        if(s[i-1] == t[j-1]){
            ans += s[i-1];
            i--;
            j--;
        }
        else if(dp[i-1][j] >= dp[i][j-1]) i--;
        else j--;
    }
    reverse(all(ans));
    cout << ans << "\n";
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