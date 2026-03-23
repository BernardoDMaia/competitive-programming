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
    int n; cin >> n;
    string s; cin >> s;
    ll cont = 0;
    ll ans = 0;

    FOR(i,0,n){
        if(s[i] == '7') cont++;
    }
    FOR(i,0,n){
        if(s[i] == '6') ans += cont;
        else cont--;
    }
    
    cout << ans << endl;
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
}