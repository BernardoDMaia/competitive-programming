#include <bits/stdc++.h>
using namespace std;
using ll = long long ;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int,int>;
#define FOR(i, a, b) for(int i = a; i < b; i++)
#define all(x) x.begin() , x.end()
#define pb push_back

void solve(){
    double n, k; cin >> n >> k;
    double ans = 1;
    FOR(i,0,n){
        double x; cin >> x;
        if(x >= k){
            ans *= (k-1)/x;
        }
    }

    ans = 1 - ans;
    cout << fixed << setprecision(14);
    cout << ans << "\n";
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int t = 1; 
    //cin >> t;
    while(t--){
        solve();
    }
}