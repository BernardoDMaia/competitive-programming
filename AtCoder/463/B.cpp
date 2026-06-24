#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
using vll = vector<ll>;
using pll = pair<ll,ll>;
#define FOR(i,a,b) for(int i = a;i<(b);i++)
#define all(x) x.begin(), x.end()
#define deb(x) cerr<< #x << "=" << x << "\n";

void solve(){
    int n; cin >> n;
    char c; cin >> c;
    int x = c - 'A';
    int ok = 0;
    FOR(i,0,n){
        string s; cin >> s;
        if(s[x] == 'o') ok = 1;
    }

    if(ok) cout << "Yes\n";
    else cout << "No\n";
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