#include <bits/stdc++.h>
using namespace std;
using ll= long long;
using vi = vector<int>;
using vll =vector<ll>;
using vc =vector<char>;
using vpii =vector<pair<int,int>>;
#define FOR(i,a,b) for(int i=a;i<(b);i++)
#define all(x) x.begin(), x.end()
#define pb push_back
#define sz(x) (int)x.size()

void solve(){
    int n, m; cin >> n >> m;
    vector<vector<tuple<ll,ll,ll>>> grafo(n+1);
    FOR(i,1,m+1){
        int idx,d,c; cin >> idx >> d >> c;
        grafo[i].pb({d,idx+1,c});
    }

    vll dp(1e6+5);
    ll maior_peso = 1e7;
    FOR(i,1,n){
        sort(all(grafo[i]));
        int pos = 1;
        int aux = 0;
        int maior = 0;
        FOR(j,0,sz(grafo[i])){
            auto [a,b,c] = grafo[i][j];
            if(c > pos){
                dp[c] += a;
                dp[pos] -= a;
                pos = c;
                aux = a;
            }
            maior = max(maior,c);
        }
        maior_peso = min(maior, maior_peso);
    }

    for(int i = sz(dp)-1; i > 0; i--){
        dp[i-1] += dp[i];
    }

    int q; cin >> q;
    FOR(i,0,q){
        int x; cin >> x;
        if(x > maior_peso) cout << "impossible"<< endl;
        else cout << dp[x] << endl;
    }

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}