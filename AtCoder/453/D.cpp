#include <bits/stdc++.h>
using namespace std;
using ll= long long;
using vi = vector<int>;
using vll =vector<ll>;
using vc =vector<char>;
using vpii =vector<pair<int,int>>;
using pii = pair<int,int>;
#define FOR(i,a,b) for(int i=a;i<(b);i++)
#define all(x) x.begin(), x.end()
#define pb push_back
#define sz(x) (int)x.size()


void solve(){
    int n, m; cin >> n >> m;
    vector<vc> grid(n, vc(m));
    vector<vi> vis(n, vi(m, 0));

    pii begin;
    FOR(i,0,n) FOR(j,0,m) {cin >> grid[i][j]; if(grid[i][j] == 'S') begin = {i,j};};

    queue<pair<pii,char>> q;
    q.push({begin, ' '});
    vis[begin.first][begin.second] = 1;

    auto down = [&](int x, int y, char d) -> bool {
        if(grid[x][y] == 'o'){
            if(d == 'D') return (x+1 >= 0 && x+1 < n && y >= 0 && y < m && !vis[x+1][y] && grid[x+1][y] != '#');
            return false;
        }
        if(grid[x][y] == 'x') if(d == 'D') return false;
        return (x+1 >= 0 && x+1 < n && y >= 0 && y < m && !vis[x+1][y] && grid[x+1][y] != '#');
    };

    auto up = [&](int x, int y, char d) -> bool {
        if(grid[x][y] == 'o'){
            if(d == 'U') return (x-1 >= 0 && x-1 < n && y >= 0 && y < m && !vis[x-1][y] && grid[x-1][y] != '#');
            return false;
        }
        if(grid[x][y] == 'x') if(d == 'U') return false;
        return (x-1 >= 0 && x-1 < n && y >= 0 && y < m && !vis[x-1][y] && grid[x-1][y] != '#');
    };

    auto left = [&](int x, int y, char d) -> bool {
        if(grid[x][y] == 'o'){
            if(d == 'L') return (x >= 0 && x < n && y-1 >= 0 && y-1 < m && !vis[x][y-1] && grid[x][y-1] != '#');
            return false;
        }
        if(grid[x][y] == 'x') if(d == 'L') return false;
        return (x >= 0 && x < n && y-1 >= 0 && y-1 < m && !vis[x][y-1] && grid[x][y-1] != '#');
    };

    auto right = [&](int x, int y, char d) -> bool {
        if(grid[x][y] == 'o'){
            if(d == 'R') return (x >= 0 && x < n && y+1 >= 0 && y+1 < m && !vis[x][y+1] && grid[x][y+1] != '#');
            return false;
        }
        if(grid[x][y] == 'x') if(d == 'R') return false;
        return (x >= 0 && x < n && y+1 >= 0 && y+1 < m && !vis[x][y+1] && grid[x][y+1] != '#');
    };

    pii end;
    vector<vpii> parent(n, vpii(m));
    parent[begin.first][begin.second] = begin;
    bool ok = false;
    
    while(!q.empty()){
        auto[u, d] = q.front();
        q.pop();
        int x = u.first;
        int y = u.second;

        if(grid[x][y] == 'G'){
            end = {x,y};
            ok = true;
            break;
        }

        if(up(x,y,d)) {
            q.push({{x-1,y}, 'U'});
            if(grid[x-1][y] == '.') vis[x-1][y] = 1;
            parent[x-1][y] = {x,y};
        }
        if(down(x,y,d)){
            q.push({{x+1,y}, 'D'});
            if(grid[x+1][y] == '.') vis[x+1][y] = 1;
            parent[x+1][y] = {x,y};
        }
        if(left(x,y,d)) {
            q.push({{x,y-1}, 'L'});
            if(grid[x][y-1] == '.') vis[x][y-1] = 1;
            parent[x][y-1] = {x,y};
        }
        if(right(x,y,d)){
            q.push({{x,y+1}, 'R'});
            if(grid[x][y+1] == '.') vis[x][y+1] = 1;
            parent[x][y+1] = {x,y};
        }
    }

    // FOR(i,0,sz(parent)){
    //     for(pii v : parent[i]){
    //         cout << "{" << v.first << "," << v.second << "}\n";
    //     }
    // }

    if(ok){
        cout << "Yes\n";
        string path = "";
        int u = end.first, v = end.second;
        while(u != begin.first || v != begin.second){
            auto [a,b] = parent[u][v];
            // cout << "a:" << a << "b:" << " " << b << "\n";
            // cout << "u:" << u << "v:" << " " << v << "\n";
            if(u-a == 1) path += "D";
            if(u-a == -1) path += "U";
            if(v-b == 1) path += "R";
            if(v-b == -1) path += "L";
            u = a; v = b;
        }

        reverse(all(path));
        cout << path <<"\n";
    } 
    else cout << "No\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
}