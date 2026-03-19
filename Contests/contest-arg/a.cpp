#include <bits/stdc++.h>
using namespace std;
using ll= long long;
using vi = vector<int>;
using vll =vector<ll>;
using vpii =vector<pair<int,int>>;
#define FOR(i,a,b) for(int i=a;i<(b);i++)
#define all(x) x.begin(), x.end()
#define pb push_back
#define sz(x) (int)x.size()

void solve(){
    int n, m; cin >> n >> m;
    vi a(n), b;
    FOR(i,0,n){
        cin >> a[i];
    }

    int u = 2e9;
    FOR(i,0,m){
        int x; cin >> x;
        if(x<u){
            b.pb(x);
            u = x;
        }
    }

    FOR(i,0,n){
        int v = a[i];
        while(true){
            auto it = lower_bound(all(b), v, greater<int>());
            if(it == b.end() || v == 0) break;
            v %= *it;
        }
        cout << v << ' ';
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}