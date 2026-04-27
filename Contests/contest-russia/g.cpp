#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i <(b); i++)
#define pb push_back

using vi = vector<int>;
using ll = long long;
using vl = vector<ll>;
using pii = pair<int,int>;

#define deb(x) cerr << #x << " = " << x << "\n";

void solve(){
    int n, k; cin >> n >> k;
    vi a;
    FOR(i,0,k){
        for(int j = n-1; j >=0; j--){
            if(j%k == i) a.pb(j);
        }
    }

    vi ciclo(n);
    FOR(i,0,n){
        int aux = i, cont = 1;
        while(true){
            if(a[aux] == i) break;
            cont++;
            aux = a[aux];
        }
        ciclo[i] = cont;
    }

    ll mmc = 1;
    for(int v : ciclo) mmc = (ll)lcm(mmc, (ll)v);

    cout << mmc << "\n";

}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    // cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
