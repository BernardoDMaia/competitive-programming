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
    int n, m, k; cin >> n >> m >> k;
    vector<vc>grid(n, vc(m));

    int e = 0; 
    int idx_x = 0;
    int idx_y = 0;
    FOR(i,0,n){
        FOR(j,0,m){
            cin >> grid[i][j];
            if(grid[i][j] == '.') {
                e++;
                idx_x = i;
                idx_y = j;
            }
        }
    }

    queue<pair<int,int>>q;
    vector<vi>vis(n, vi(m,0));
    q.push({idx_x,idx_y});
    vis[idx_x][idx_y]=1;
    e--;
    int ok = 0;

    while(!q.empty()){
        auto [u,v] = q.front();
        q.pop();
        FOR(dx,-1,2){
            FOR(dy,-1,2){
                if(e == k){
                    ok = 1;
                    break;
                }
                if(abs(dx)+abs(dy) != 1) continue;
                int vx = u+dx;
                int vy = v+dy;

                if(vx>= 0 && vx <n && vy >= 0&& vy <m && !vis[vx][vy] && grid[vx][vy] == '.'){
                    q.push({vx,vy});
                    vis[vx][vy] = 1;
                    e--;
                }
            }
            if(ok) break;
        }
        if(ok) break;
    }
    
    FOR(i,0,n){
        FOR(j,0,m){
            if(grid[i][j] == '.' && !vis[i][j]) grid[i][j] = 'X';
        }
    }
    
    FOR(i,0,n){
        FOR(j,0,m){
            cout << grid[i][j];
        }
        cout << endl;
    }
    
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}