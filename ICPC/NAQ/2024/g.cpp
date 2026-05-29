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
        vector<vld> a(1e5+6);
        FOR(i,0,n){
            ld x, y; cin >> x >> y;
            a[x].pb(y);
        }

        ld ans = 0.0;
        FOR(i,0,1e5+6){
            int tam = a[i].size();
            if(tam){
                sort(all(a[i]));
                FOR(j,0,(tam/2)){
                    ld curr = a[i][tam-1-j]/a[i][j];
                    ans += log(curr);
                }
            }
        }

        cout << fixed << setprecision(15);
        cout << ans << "\n";
    }

    int main(){
        ios::sync_with_stdio(false);
        cin.tie(0);
        solve();

        return 0;
    }