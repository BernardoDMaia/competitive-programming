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
    int n, m; cin >> n >> m;
    vi a(n), v(m);
    FOR(i,0,n) cin >> a[i];
    FOR(i,0,m) cin >> v[i];

    vector<vi> lcs(n+1, vi(m+1));
    FOR(i,1,n+1){
        FOR(j,1,m+1){
            if(a[i-1] == v[j-1]) lcs[i][j] = lcs[i-1][j-1] + 1;
            else{
                lcs[i][j] = max(lcs[i-1][j], lcs[i][j-1]);
            }   
        }
    }

    vi ans;
    int i = n, j = m;
    while(i > 0 && j > 0){
        if(a[i-1] == v[j-1]){
            ans.pb(a[i-1]);
            i--;j--;
        }
        else if(lcs[i-1][j] > lcs[i][j-1]) i--;
        else j--;
    }
    reverse(all(ans));

    cout << lcs[n][m] << "\n";
    for(int x : ans) cout << x << " ";
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