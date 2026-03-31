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
    int n, d; cin >> n >> d;
    vi a, b;
    FOR(i,0,n){
        int x; cin >> x;
        if(x < d) a.pb(x);
        else b.pb(x);
    }
    sort(all(a));
    sort(all(b));

    set<int> ans;
    FOR(i,0,sz(a)) ans.insert(a[i]+d);
    FOR(i,0,sz(b)){
        if(ans.find(b[i]-d) != ans.end()) ans.insert(b[i]+d);
        else ans.insert(b[i]-d);
    }

    cout << sz(ans) << endl;

}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
}