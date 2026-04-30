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
    vi dp(k+1, 0), coins(n);
    
    dp[0] = 1;
    FOR(i,0,n){
        cin >> coins[i];
        dp[coins[i]] = 1;
    }

    FOR(i,1,k+1){
        FOR(j,0,n){
            if(i-coins[j] >= 0 && dp[i-coins[j]]) {
                dp[i] = 1;
            } 
        }
    }
    
    int tam = 0;
    FOR(i,0,k+1) if(dp[i]) tam++;
    cout << tam << "\n";
    FOR(i,0,k+1) if(dp[i]) cout << i << " ";
    cout << "\n";
    
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
}