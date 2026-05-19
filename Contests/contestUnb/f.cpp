#include <bits/stdc++.h>
using namespace std;
using ll = long long ;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int,int>;
#define FOR(i, a, b) for(int i = a; i < b; i++)
#define all(x) x.begin() , x.end()
#define pb push_back

void solve(){
    int n; cin >> n;
    vi l(n+1);
    FOR(i,1,n+1) cin >> l[i];

    FOR(i,0,n){
        int k = i; //x^k;
        vi vis(n+1, 0);
        FOR(j,1,n+1){
            if(vis[j]) continue;
            vis[j] = 1;

            //adicionar o cara em l[j] - d
             
        }
    }
}

int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
    return 0;
}