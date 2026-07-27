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

int ans(int n, int k){
    if(k > n-k) k = n-k;
    int res = 1;
    FOR(i,0,k){
        res = res*(n-i)/(i+1);
    }
    return res;
}

void solve(){
    int n, m; cin >> n >> m;
    cout << ans(n-1,m-1) << "\n";
}

signed main(){
    ios::sync_with_stdio(false); 
    cin.tie(0);
    int t; cin >> t;
    while(t--){
        solve();
    }
    return 0;
}