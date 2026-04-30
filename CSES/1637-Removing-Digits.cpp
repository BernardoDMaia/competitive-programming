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
    vi dp(n+1, 1e6+5);
    
    auto findDigits = [&](int x) -> vi {
        vi v;
        while(x>0){
            int a = x%10;
            if(a != 0) v.pb(a);
            x /= 10;
        }
        return v;
    };

    dp[0] = 0;
    FOR(i,1,n+1){
        vi digits = findDigits(i);
        // for(int v : digits) cout << v << " ";
        // cout <<"\n";
        FOR(j,0,sz(digits)){
            dp[i] = min(dp[i], dp[i-digits[j]]+1);
        }
    }

    cout << dp[n] << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
}