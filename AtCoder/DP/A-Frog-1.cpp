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
    vi v(n+1), dp(n+1,0);

    FOR(i,1,n+1) cin >> v[i];

    FOR(i,2,n+1){
        if(i==2) dp[i] = abs(v[2] - v[1]);
        else{
            dp[i] = min((dp[i-2]+ abs(v[i] - v[i-2])), (dp[i-1] + abs(v[i] - v[i-1])));
        }
    }

    cout << dp[n] << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
}