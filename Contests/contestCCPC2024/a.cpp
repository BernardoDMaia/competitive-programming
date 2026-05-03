#include <bits/stdc++.h>
using namespace std;

#define fastio cin.tie(0)->sync_with_stdio(0);
#define FOR(i,a,b) for (int i = (a); i < (b); i++)
#define all(x) (x).begin(), (x).end()
#define deb(k) cerr << #k << ":" << k << "\n";
#define pb push_back
using ll = long long ;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int,int>;

const int MOD = 1e9 + 7;
const ll INF = 1e18;

void solve(){
    int a,b,c,d; cin >> a >> b >> c >> d;
    
    if(a < 4){
        cout << 0 << "\n";
        return;
    } 
    
    int ans = 4;
    for(int i = 2; i <= 1000; i+=2){
        if(b < i || c < i || d < i-1) break;
        int mid = min(i,d);
        int aux = (2 * i) + 4 + mid;
        ans = max(ans, aux);
    }

    cout << ans << "\n";
}

int main(){
    fastio;
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
