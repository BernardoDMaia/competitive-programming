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

void rotate(vector<vector<char>> &mat){
    int n = mat.size();
    FOR(i,0,n){
        for(int j = i+1; j < n; j++) swap(mat[i][j], mat[j][i]);
    }
    FOR(i,0,n) reverse(all(mat[i]));
}

int verify(vector<vector<char>> &mat, int m, int n){
    while(m != 0){
        int ok = 1;
        FOR(i,0,m){
            if(!ok) break;
            FOR(j,0,m){
                if(!ok) break;
                if(mat[i][j] != mat[j][n-i-1] || mat[i][j] != mat[n-i-1][n-j-1]) ok = 0;
            }
        }
        if(ok) return m;
        m--;
    }
    return 0;
}

void solve(){
    int n; cin >> n;
    vector<vector<char>> mat(n, vector<char>(n));
    int ans= 0;

    FOR(i,0,n) FOR(j,0,n) cin >> mat[i][j];

    ans = max(ans, verify(mat, n/2, n));
    
    rotate(mat);
    ans = max(ans, verify(mat, n/2, n));
    
    rotate(mat);
    ans = max(ans, verify(mat, n/2, n));
    
    rotate(mat);
    ans = max(ans, verify(mat, n/2, n));

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