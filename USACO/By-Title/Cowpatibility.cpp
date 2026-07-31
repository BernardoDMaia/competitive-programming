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

    map<vi,int> mp;
    FOR(i,0,n){
        vi v(5);
        FOR(j,0,5){
            cin >> v[j];
        }
        sort(all(v));
        for(int mask = 1; mask <= 31; mask++){
            vi a;
            FOR(k,0,5){
                if((mask >> k) & 1){
                    a.pb(v[k]);
                }
            }
            mp[a]++;
        }
    }

    int ans = 0;
    for(auto [v,qtd] : mp){
        if(sz(v) % 2 == 1){
            ans += ((qtd)*(qtd-1))/2;
        }
        else ans -= ((qtd)*(qtd-1))/2;
    }

    cout << ((n*(n-1))/2) - ans << "\n";

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