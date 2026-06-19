#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int,int>;
#define FOR(i,a,b) for(int i = a;i<(b);i++)
#define all(x) x.begin(), x.end()
#define deb(x) cerr<< #x << "=" << x << "\n";
#define sz(x) x.size()
#define pb push_back

void solve(){
    int n; cin >> n;
    vll p(n);
    ll sum = 0;
    FOR(i,0,n) {
        cin >> p[i];
        sum += p[i];
    }

    sort(all(p));
    reverse(all(p));

    ll alvo = sum/2;

    vll dp(1e6+5, 0);
    dp[0] = 1;
    for(int v : p){
        for(int i = 1e6; i >= 0; i--){
            if(i-v >= 0 && i-v <= alvo) dp[i] += dp[i-v];
        }
    }

    ll ans = 0;
    FOR(i,alvo+1,1e6+5) ans += dp[i];

    cout << ans << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--){
        solve();    
    }
    return 0;
}