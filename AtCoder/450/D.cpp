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
    int n, k; cin >> n >> k;
    vi v;
    set<int>s;
    FOR(i,0,n){
        int x; cin >> x;
        s.insert(x%k);
    }

    for(int y: s) v.pb(y);

    int mx = 0;
    FOR(i,0,sz(v)-1){
        mx = max(mx,(v[i+1]-v[i]));
        
    }

    mx = max(mx,v[0]-v[sz(v)-1]+k);

    cout << k-mx << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}