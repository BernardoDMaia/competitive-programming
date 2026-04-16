#include <bits/stdc++.h>
using namespace std;

using pii = pair<int,int>;
#define all(x) x.begin(), x.end()

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m; cin >> n >> m;
    vector<string> grid(n);
    for(int i = 0; i < n; i++) cin >> grid[i];

    pii begin;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(grid[i][j] == 'S') begin = {i,j};
        }
    }

    // 0=U,1=D,2=L,3=R
    int dx[4] = {-1,1,0,0};
    int dy[4] = {0,0,-1,1};
    char dc[4] = {'U','D','L','R'};

    // 🔥 VIS COM DIREÇÃO
    vector vis(n, vector(m, vector<int>(4, 0)));

    // parent[x][y][dir] = {{px,py}, pdir}
    vector parent(n, vector(m, vector<pair<pii,int>>(4)));

    queue<tuple<int,int,int>> q;

    // começa com todas direções
    for(int d = 0; d < 4; d++){
        q.push({begin.first, begin.second, d});
        vis[begin.first][begin.second][d] = 1;
        parent[begin.first][begin.second][d] = {{-1,-1}, -1};
    }

    pii end;
    int end_dir = -1;
    bool ok = false;

    while(!q.empty()){
        auto [x,y,d] = q.front(); q.pop();

        if(grid[x][y] == 'G'){
            end = {x,y};
            end_dir = d;
            ok = true;
            break;
        }

        for(int nd = 0; nd < 4; nd++){
            int nx = x + dx[nd];
            int ny = y + dy[nd];

            if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
            if(grid[nx][ny] == '#') continue;

            // regras da célula atual
            if(grid[x][y] == 'o' && nd != d) continue;
            if(grid[x][y] == 'x' && nd == d) continue;

            if(!vis[nx][ny][nd]){
                vis[nx][ny][nd] = 1;
                parent[nx][ny][nd] = {{x,y}, d};
                q.push({nx,ny,nd});
            }
        }
    }

    if(!ok){
        cout << "No\n";
        return 0;
    }

    // reconstrução
    string path = "";
    int x = end.first, y = end.second, d = end_dir;

    while(true){
        auto [p, pd] = parent[x][y][d];
        if(pd == -1) break;

        path += dc[d];

        x = p.first;
        y = p.second;
        d = pd;
    }

    reverse(all(path));

    cout << "Yes\n";
    cout << path << "\n";
}