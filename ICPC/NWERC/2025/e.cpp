#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int,int>;
#define FOR(i,a,b) for(int i = a;i<(b);i++)
#define all(x) x.begin(), x.end()
#define deb(x) cerr<< #x << "=" << x << "\n";
#define sz(x) x.size()
#define pb push_back

ll fexp (ll b, ll e, ll MOD){
    ll res = 1;
    while(e){
        if(e & 1) res = (res*b)%MOD;
        b = (b*b)%MOD;
        e /= 2;
    } 
    return res;
}

void solve(){
    ll n, k; cin >> n >> k;
    string s; cin >> s;
    string t = s;
    
    FOR(i,0,n){
        ll idx = (fexp(2,k,n)*i)%n;
        t[i] = s[idx];
    }

    cout << t << "\n";
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