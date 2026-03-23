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
    ll x, y; cin >> x >> y;
    int n; cin >> n;
    bool ok = true;

    FOR(i,0,n){
        string d; cin >> d;
        int a, b; cin >> a >> b;
        
        if(d == "V"){
            if(a == x) ok = false;
        }
        
        if(d == "H"){
            if(b == y) ok = false;
        }

        if(d == "DP"){
            if((b-y) == (a-x)) ok = false;
        }

        if(d == "DS"){
            if((b-y) == -(a-x)) ok = false;
        }
    }

    if(ok) cout << "YES" << endl;
    else cout << "NO" << endl;

}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
}