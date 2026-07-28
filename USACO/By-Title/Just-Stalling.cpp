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
    vi h(n), s(n), cnt(n);
    FOR(i,0,n) cin >> h[i];
    FOR(i,0,n) cin >> s[i];
    sort(all(h));
    reverse(all(h));
    
    FOR(i,0,n){
        int curr = 0;
        FOR(j,0,n){
            if(h[i] <= s[j]) curr++;
        }
        cnt[i] = curr;
    }

    int ans = 1;
    FOR(i,0,n){
        ans *= (cnt[i] - i);  
    }

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