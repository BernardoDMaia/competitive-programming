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
    ll a, b, k; cin >> a >> b >> k;

    int ans = 0;

    if(k >= a && k >= b) ans = 1;
    else if(__gcd(a,b) != 1 && (a/__gcd(a,b)) <= k && (b/__gcd(a,b) <= k)) ans = 1;
    else ans = 2;

    cout << ans << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t = 1; 
    cin >> t;
    while(t--){
        solve();
    }
}