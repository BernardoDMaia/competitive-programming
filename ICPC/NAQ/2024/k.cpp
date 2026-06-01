    #include <bits/stdc++.h>
    using namespace std;
    using ll = long long;
    using ld = long double;
    using vi = vector<int>;
    using vll = vector<ll>;
    #define FOR(i,a,b) for(int i =a;i<(b);i++)
    #define all(x) x.begin(), x.end()
    #define pb push_back

    void solve(){
        int n, m; cin >> n >> m;
        vll a(n+1), v(m+1);
        vector<vll> dif(n+1, vll(m+1)), dp(n+1, vll(m+1));
        FOR(i,1,n+1) cin >> a[i];
        FOR(i,1,m+1) cin >> v[i];

        FOR(i,1,n+1){
            FOR(j,1,m+1){
                ll d = abs(a[i]-v[j]);
                if(d <= 15) dif[i][j] = 7;
                else if(d <= 23) dif[i][j] = 6;
                else if(d <= 43) dif[i][j] = 4;
                else if(d <= 102) dif[i][j] = 2;
                else dif[i][j] = 0;
            }
        }

        FOR(i,1,n+1) FOR(j,1,m+1) dp[i][j] = max({dp[i][j-1], dp[i-1][j], (dif[i][j] + dp[i-1][j-1])});

        cout << dp[n][m] << "\n";
    }

    int main(){
        ios::sync_with_stdio(false);
        cin.tie(0);
        solve();

        return 0;
    }