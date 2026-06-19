#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using pll = pair<ll,ll>;
#define FOR(i,a,b) for(int i = a;i<(b);i++)
#define all(x) x.begin(), x.end()
#define deb(x) cerr<< #x << "=" << x << "\n";
#define sz(x) x.size()
#define pb push_back

void solve(){
    int n; cin >> n;
    vll h(n);
    vector<pll> c(n);
    vll ans(n);

    FOR(i,0,n){
        ll x,y,z; cin >> x >> y >> z;
        ans[i] = z;
        h[i] = z;
        c[i] = {x,y};
    }

    ll x1,x2,y1,y2;
    auto dist = [&] () -> ll {
        return ((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2));
    };

    FOR(i,0,n){
        FOR(j,0,n){
            if(i == j) continue;
            if(h[i] < h[j]){
                x1 = c[i].first;
                y1 = c[i].second;
                x2 = c[j].first;
                y2 = c[j].second;
                ll d = dist();
                if(dist() < ans[i]*ans[i]){
                    d = sqrt(d);
                    ans[i] = d;
                }
            }
        }
    }

    for(ll v : ans) cout << v << "\n";

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