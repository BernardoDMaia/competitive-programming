#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
#define FOR(i,a,b) for(int i = a; i<(b);i++)

void solve(){
    int n; cin >> n;
    vi v(n);
    FOR(i,0,n) cin >> v[i];
    vi ans(n+1,0);
    map<int,int> ant;
    FOR(i,0,n){
        map<int,int> novo;
        novo[v[i]] = 1;
        ans[1] = max(ans[1], v[i]);
        for(auto [mdc,size] : ant){
            int a = gcd(mdc,v[i]);
            novo[a] = max(novo[a],size+1);
            ans[size+1] = max(ans[size+1], a);
        }
        ant = novo;
    }

    for(int i = n-1; i >= 1; i--) ans[i] = max(ans[i+1], ans[i]);

    FOR(i,1,n+1) cout << ans[i] << " ";
    cout << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1; 
    cin >> t;
    while(t--){
        solve();
    }
    return 0;
}