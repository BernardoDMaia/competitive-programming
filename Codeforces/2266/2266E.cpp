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
const int MAXN = 2e6;

int spf[MAXN];

void crivo_spf(){
    for(int i = 2; i < MAXN; i++) spf[i] = i;

    for(int i = 2; i * i < MAXN; i++){
        if(spf[i] == i){
            for(int j = i * i; j < MAXN; j += i)
                if(spf[j] == j) spf[j] = i;
        }
    }
}

vi fatorar(int x){
    vi ret;
    while(x != 1){
        int div = spf[x];
        ret.pb(div);
        while(x % div == 0) x /= div;
    }
    return ret;
}

void solve(){
    int n, k; cin >> n >> k;

    vi dp(n+1, 1e18);
    dp[0] = dp[1] = 0;
    FOR(i,2,n+1){
        if(i <= k) dp[i] = 0;
        else{
            vi p = fatorar(i);
            for(auto x : p) dp[i] = min(dp[i], (dp[i/x] * x) + 1);
        }
    }

    int ans = 0;
    FOR(i,0,n){
        int x; cin >> x;
        ans += dp[x];
    }

    cout << ans << "\n";
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    crivo_spf();
    int t = 1;
    cin >> t;
    while(t--)
    solve();
    return 0;
}