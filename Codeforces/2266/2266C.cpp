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
    int n; cin >> n;
    vi zeros(n, 0), ones(n, 0);
    string s; cin >> s;
    for(int i = n-2; i >= 0; i--) zeros[i] = zeros[i+1] + (s[i+1] == '0' ? 1 : 0);
    for(int i = 2; i < n; i++) ones[i] = ones[i-1] + (s[i-1] == '0' ? 0 : 1);
    
    if(s[0] == '1'){
        cout << zeros[0] << "\n";
        return;
    }

    int ans = n;
    
    FOR(i,0,n){
        // i é divisória
        ans = min(ones[i]+zeros[i], ans);
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