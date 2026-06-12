#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using pll = pair<ll,ll>;
#define FOR(i,a,b) for(int i = a;i<(b);i++)
#define all(x) x.begin(), x.end()
#define deb(x) cerr<< #x << "=" << x << "\n";

void solve(){
    int n; cin >> n;
    vi v(n);
    
    FOR(i,0,n) cin >> v[i];
    int mdc = v[0];
    int curr = v[0];
    FOR(i,1,n){
        mdc = gcd(mdc, v[i]);
        if(v[i] <= curr){
            int l = v[i];
            cout << (curr/(l-1)) << "\n";
            return;
        }
        curr = v[i];
    }
    
    cout << max(mdc,(v[n-1]/mdc)) << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    while(t--){
        solve();
    }
    return 0;
}