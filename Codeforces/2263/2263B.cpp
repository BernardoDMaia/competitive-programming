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
    int n,k; cin >> n >> k;

    if(k < n || k > (2*n)-1){
        cout << "-1\n";
        return;
    }

    int outDiag = k-n;
    int m = 1;
    vector<vi> mat(n, vi(n, -1));
    FOR(i,0,n){
        mat[i][i] = m;
        m++;
        if(outDiag){
            outDiag--;
            mat[i][i+1] = m;
            m++;
        }
    }

    FOR(i,0,n){
        FOR(j,0,n){
            if(mat[i][j] == -1){
                mat[i][j] = m;
                m++;
            }
        }
    }

    FOR(i,0,n){
        FOR(j,0,n){
            cout << mat[i][j] << " ";
        }
        cout << "\n";
    }

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