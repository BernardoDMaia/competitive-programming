#include <bits/stdc++.h>
using namespace std;
using ll= long long;
using vi = vector<int>;
using vll =vector<ll>;
using vc =vector<char>;
using vpii =vector<pair<int,int>>;
#define FOR(i,a,b) for(int i=a;i<(b);i++)
#define all(x) x.begin(), x.end()
#define pb push_back
#define sz(x) (int)x.size()

void solve(){
    ll n; cin >> n;
    if(n<3){ 
        cout << n << endl;
        return;
    }

    vll pot;
    ll a = 2;
    while(a <= n){
        pot.pb(a);
        a *= 2;
    }

    FOR(i,0,sz(pot)){
        ll u = pot[i];
        auto it = lower_bound(all(pot), n-u-1);
        if(it == pot.end()) continue;

        ll v = *it;
        if(u+v+1 == n){
            cout << u+(ll)1 << endl;
            return;
        }
    }
    cout << "impossible\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}