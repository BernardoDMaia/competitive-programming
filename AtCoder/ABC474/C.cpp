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

void solve(){
    int n, q; cin >> n >> q;
    vi a(n), end;
    FOR(i,0,n) cin >> a[i];

    while(q--){
        int x; cin >> x;
        x--;
        end.pb(x);
    }

    int idx = n-1;
    vi vis(n, 0), ans(n);
    for(int i = sz(end) - 1; i >= 0; i--){
        if(!vis[end[i]]){
            ans[idx] = end[i];
            vis[end[i]] = 1;
            idx--;
        }
    }

    for(int i = n - 1; i >= 0; i--){
        if(!vis[a[i] -1]){
            ans[idx] = a[i] -1;
            vis[a[i]-1] = 1;
            idx--;
        }
    }

    for(int x : ans) cout << x+1 << " ";
    cout << "\n";
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