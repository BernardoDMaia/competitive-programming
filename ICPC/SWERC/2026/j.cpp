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
    vi freq(1005);

    FOR(i,0,n){
        int x; cin >> x;
        freq[x]++;
    }

    ll ans = 0;
    FOR(i,0,1005){
        if(freq[i] < i) ans += freq[i];
        else if(freq[i] > i) ans += (n-freq[i]);
    }

    cout << ans << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1; 
    //cin >> t;
    while(t--){
        solve();
    }
    return 0;
}