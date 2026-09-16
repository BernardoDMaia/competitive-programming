#include <bits/stdc++.h>
using namespace std;
#define int long long
using vi = vector<int>;
#define FOR(i,a,b) for(int i =a;i<b;i++)
#define all(x) x.begin(), x.end()
using pii = pair<int,int>;
#define pb push_back
#define sz(x) x.size()
#define deb(x) cerr << #x << "= " << x << "\n";
#define deb2(x,y) cerr << #x << "= " << x << ", "<< #y << "= " << y << "\n";
//ctrl+alt+a p/ accepted
const int MOD = 998244353;

void solve(){
    int n; cin >> n;
    vi a(n); FOR(i,0,n) cin >> a[i];
    sort(all(a));
    reverse(all(a));

    int fat = 1, sum = a[0], ans = 0;
    FOR(i,1,n){
        int curr = (sum - ((i*a[i]) % MOD) + MOD) % MOD;
        ans = ans*i % MOD;
        ans = (ans+(curr*fat)) % MOD;
        sum = (sum+a[i])%MOD;
        fat = (fat*i) % MOD;
    }

    cout << ans << "\n";
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    cin >> t;
    while(t--)
    solve();
    return 0;
}