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
    int n, m, k; cin >> n >> m >> k;
    vi v(m);
    k = (2*k)+1;
    FOR(i,0,m) cin >> v[i];
    sort(all(v));

    int curr = 1;
    int ans = 0;
    FOR(i,0,m){
        ans += (v[i] - curr + k)/k;
        curr = v[i]+1;
    }
    ans += (n-curr+k)/k;

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