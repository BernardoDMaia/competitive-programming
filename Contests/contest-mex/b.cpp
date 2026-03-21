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
    vector<vi>mat(n, vi(n));
    vi v,v2,v3,v4,v5,v6,v7,v8;

    FOR(i, 0, n) FOR(j, 0, n) cin >> mat[i][j];

    FOR(i,0,n) {
        v.pb(mat[i][0]);
        v2.pb(mat[0][i]);
    }

    int i = n-1, j = 0; bool sig_i = false, sig_j = true;
    int aux = n-1;
    while(aux>0){
        FOR(k,0,aux){
            if(sig_j){
                j++;
                v.pb(mat[i][j]);
                v2.pb(mat[j][i]);
            }
            else{
                j--;
                v.pb(mat[i][j]);
                v2.pb(mat[j][i]);
            }
        }

        FOR(k,0,aux){
            if(sig_i){
                i++;
                v.pb(mat[i][j]);
                v2.pb(mat[j][i]);
            }
            else{
                i--;
                v.pb(mat[i][j]);
                v2.pb(mat[j][i]);
            }
        }

        sig_i = !sig_i; sig_j = !sig_j;
        aux--;
    }

    
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}