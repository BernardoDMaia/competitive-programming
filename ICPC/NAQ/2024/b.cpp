    #include <bits/stdc++.h>
    using namespace std;
    using ll = long long;
    using ld = long double;
    using vi = vector<int>;
    using vld = vector<ld>;
    #define FOR(i,a,b) for(int i =a;i<(b);i++)
    #define all(x) x.begin(), x.end()
    #define pb push_back

    void solve(){
        int n; cin >> n;

        ld ans = 1e10;
        FOR(i,0,n){
            ld x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
            if(x1 > 0.0 && x2 > 0.0) continue;
            if(x1 < 0.0 && x2 < 0.0) continue;
            ld curr = -(x2/x1);
            ld b = ((y1*curr) + y2)/(curr+1);
            if(b > 0.0) ans = min(ans, b);
        }
        
        cout << fixed << setprecision(15);
        if(ans == 1e10) cout << "-1.0\n";
        else cout << ans << "\n";
    }

    int main(){
        ios::sync_with_stdio(false);
        cin.tie(0);
        solve();

        return 0;
    }