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

void solve(){
    int n, k; cin >> n >> k;
    vi c(k+1);
    FOR(i,0,n){
        int x; cin >> x;
        c[x]++;
    }

    int mx = *max_element(all(c)), ans = 0;
    FOR(i,1,k+1){
        if(c[i]+1 >= mx) ans++;
    }

    cout << ans << "\n";
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--)
    solve();
    return 0;
}