#include <bits/stdc++.h>
using namespace std;
using ll= long long;
using vi = vector<int>;
using vll =vector<ll>;
using vpii =vector<pair<int,int>>;
#define FOR(i,a,b) for(int i=a;i<(b);i++)
#define all(x) x.begin(), x.end()
#define pb push_back
#define sz(x) (int)x.size()

void solve(){
    int n; cin >> n;
    vector<vi> a(2e5+5);

    FOR(i,0,n){
        int r, c; cin >> r >> c;
        a[r].pb(c);
    }

    ll ans = 0;
    FOR(i,0,2e5+5){
        int med = 0, tam = sz(a[i]);
        if(tam == 0) continue;

        sort(all(a[i]));
        if(tam % 2 == 1) med = a[i][tam/2];
        else med = (a[i][tam/2] + a[i][(tam/2)-1])/2;

        FOR(j,0,tam){
            ans += abs(a[i][j]-med);
        }
    }

    cout << ans << endl;

}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
}