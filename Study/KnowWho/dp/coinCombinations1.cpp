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
    int n, x; cin >> n >> x;
    vi dp(1e6+1, 0), a(n);
    FOR(i,0,n){
        cin >> a[i];
        dp[a[i]] = 1;
    }

    FOR(i,1,x+1){
        FOR(j,0,n){
            if(i - a[j] >= 0) dp[i] = (dp[i] + dp[i - a[j]])%MOD;
        }
    }

    cout << dp[x] << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
}