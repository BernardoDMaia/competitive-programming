#include <bits/stdc++.h>
using namespace std;
using ll= long long;
using vi = vector<int>;
using vll =vector<ll>;
using vpii =vector<pair<int,int>>;
#define FOR(i,a,b) for(int i=a;i<(b);i++)
#define all(x) x.begin(), x.end()
#define pb push_back
#define sz(x) (int)x.size()

void solve(){
    int n; cin >> n;
    vi a(n), freq(2e5+5), dp(2e5+5);
    FOR(i,0,n){
        cin >> a[i];
        freq[a[i]]++;
    }

    FOR(i,2,2e5+5){
        dp[i] += freq[i];
        for(int j = i; j < 2e5+5; j+=i){
            dp[j] = max(dp[i],dp[j]);
        }
    }
    
    cout << *max_element(all(dp)) + freq[1] << endl;
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
}