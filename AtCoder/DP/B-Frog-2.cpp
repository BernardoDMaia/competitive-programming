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
    int n, k; cin >> n >> k;
    vi v(n+1), dp(n+1,1e9+7);

    FOR(i,1,n+1) cin >> v[i];

    dp[1] = 0; dp[0] = 0;
    FOR(i,2,n+1){
        int kk = min(k,i-1);
        for(int j = i-kk; j < i; j++){
            int jump = abs(v[j]-v[i]);
            dp[i] = min(dp[i], dp[j]+jump);
        }
    }

    cout << dp[n] << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
}