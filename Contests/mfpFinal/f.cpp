#include <bits/stdc++.h>
using namespace std;
#define int long long
using vi = vector<int>;
#define FOR(i, a, b) for (int i = a; i < (b); i++)
#define all(x) x.begin(), x.end()
#define pb push_back
#define sz(x) (int)(x).size()
#define deb(x) cerr << #x << " = " << x << "\n";
#define deb2(x,y) cerr << #x << "=" << x << ", " << #y << "=" << y << "\n";
#define deb3(x,y,z) cerr << #x << "=" << x << ", " << #y << "=" << y << ", " << #z << "=" << z << "\n";

void solve(){
    int n; cin >> n;
    vector<double> v(n);
    FOR(i,0,n){
        int x; cin >> x;
        v[i] = x/100.0;
    }

    vector<double> res;
    for(int mask = 0; mask < (1 << n); mask++){
        double p = 1.0;
        FOR(i,0,n){
            if((mask >> i)& 1) p *= v[i];
            else p *= (1.0 - v[i]);
        }
        res.pb(p);
    }
    sort(all(res));
    reverse(all(res));

    double ans = 0.0;
    FOR(i,0,res.size()){
        double p = (i+1) * res[i]; //prob de ser essa
        ans += p;
    }

    cout << fixed << setprecision(12);
    cout << ans << "\n";
}

signed main(){
    ios::sync_with_stdio(false); 
    cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
    return 0;
}