    #include <bits/stdc++.h>
    using namespace std;
    using ll = long long;
    using vi = vector<int>;
    #define FOR(i,a,b) for(int i =a;i<(b);i++)
    #define all(x) x.begin(), x.end()
    #define pb push_back

    void solve(){
        int n; cin >> n;
        int ans = 0;
        FOR(i,0,n){
            int x; cin >> x;
            ans += x%2;
        }
        cout << ans << "\n";
    }

    int main(){
        ios::sync_with_stdio(false);
        cin.tie(0);
        solve();

        return 0;
    }