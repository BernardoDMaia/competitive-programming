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
    int n, q; cin >> n >> q;
    vi v(n);
    FOR(i,0,n) cin >> v[i];
    sort(all(v));

    while(q--){
        int x; cin >> x;
        int idx = lower_bound(all(v),x) - v.begin();
        int ans = 2e9;
        if(idx < n && idx+1 < n){
            ans = min(ans,(v[idx+1] - x));
        }
        if(idx-1 > 0 && idx-2 >= 0){
            ans = min(ans,(x - v[idx-2]));
        }
        if(idx-1 >= 0 && idx < n){
            ans = min(ans, v[idx]-v[idx-1]);
        }

        cout << ans << "\n";
    }
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