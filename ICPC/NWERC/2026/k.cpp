#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
#define FOR(i,a,b) for(int i = a; i<(b);i++)
#define all(x) x.begin(), x.end()

void solve(){
    int n, m; cin >> n >> m;
    int k,i,t; cin >> k >> i >> t;
    vector<vector<char>> a(n, vector<char>(m));
    vector<vi> vis(n, vi(m));

    int cont = 1;
    FOR(idx,0,n){
        FOR(j,0,m){
            if(cont > 3) break;
            vis[idx][j] = 1;
            if(cont == 1)a[idx][j] = 'K';
            if(cont == 2)a[idx][j] = 'I';
            if(cont == 3)a[idx][j] = 'T';
            cont++;
        }
    }
    k--;i--;t--;

    FOR(idx,0,n){
        FOR(j,0,m){
            if(!vis[idx][j]){
                if(t){
                    vis[idx][j] = 1;
                    a[idx][j] = 'T';
                    t--;
                }
                else if(k){
                    vis[idx][j] = 1;
                    a[idx][j] = 'K';
                    k--;
                }
                else{
                    vis[idx][j] = 1;
                    a[idx][j] = 'I';
                    i--;
                }
            }
        }
    }

    FOR(idx,0,n){
        FOR(j,0,m) cout << a[idx][j];
        cout << "\n";
    } 
    
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();

    return 0;
}