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
    vll coins(n), dp(1e6+5 , 1e9+7);
    
    FOR(i,0,n){
        cin >> coins[i];
        dp[coins[i]] = 1;
    }

    FOR(i,1,x+1){
        FOR(j,0,n){
            int idx = i - coins[j];
            if(idx > 0) dp[i] = min(dp[i], dp[idx]+1);
        }
    }

    if(dp[x] == 1e9+7) dp[x] = -1;

    cout << dp[x] << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
}