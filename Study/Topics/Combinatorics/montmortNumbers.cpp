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

void solve(){
    int n, m; cin >> n >> m;
    int ans = 1;
    FOR(i,1,n+1){
        ans = ((ans*i)+ (i % 2 == 0 ? 1: -1)) % m;
        cout << ans << " ";
    }
    cout << "\n";
}

signed main(){
    ios::sync_with_stdio(false); 
    cin.tie(0);
    solve();
    return 0;
}