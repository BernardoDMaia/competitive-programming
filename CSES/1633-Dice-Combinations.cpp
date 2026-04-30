#include <bits/stdc++.h>
using namespace std;
using ll= long long;
using vi = vector<int>;
using vll =vector<ll>;
using vc =vector<char>;
using vpii =vector<pair<int,int>>;
using pii = pair<int,int>;
#define FOR(i,a,b) for(int i=a;i<(b);i++)
#define all(x) x.begin(), x.end()
#define pb push_back
#define sz(x) (int)x.size()

const int MOD = 1e9+7;

void solve(){
    int n; cin >> n;
    vi dp(n+1, 0);
    dp[0] = 1;

    FOR(i,1,n+1){
        FOR(j,0,7){
            if(i-j >= 0) dp[i] = (dp[i] + dp[i-j])%MOD;
        }
    }

    cout << dp[n] << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
}