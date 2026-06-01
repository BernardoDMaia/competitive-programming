    #include <bits/stdc++.h>
    using namespace std;
    using ll = long long;
    using ld = long double;
    using vi = vector<int>;
    using vld = vector<ld>;
    #define FOR(i,a,b) for(int i =a;i<(b);i++)
    #define all(x) x.begin(), x.end()
    #define pb push_back

    void solve(){
        int n; cin >> n;
        vector<vector<char>>grid(n, vector<char>(n));
        vector<vi> vis(n, vi(n));

        FOR(i,0,n) FOR(j,0,n) cin >> grid[i][j];

        FOR(i,0,n){
            FOR(j,0,n){
                if(grid[i][j] == '.') continue;
                else if(grid[i][j] == 'X') continue;
                else if(grid[i][j] == '?'){
                    int ok1 = 1, ok2 = 1, ok3 = 1, ok4 = 1;
                    FOR(k,1,n){
                        int up = i - k;
                        int down = i + k;
                        int left = j - k;
                        int right = j + k;
                        if(up >= 0 && ok1){
                            if(grid[up][j] == '?'){
                                cout << "0\n";
                                return;
                            }
                            else if(grid[up][j] == '.') vis[up][j] = 1;
                            else ok1 = 0;
                        }
                        if(left >= 0 && ok2){
                            if(grid[i][left] == '?'){
                                cout << "0\n";
                                return;
                            }
                            else if(grid[i][left] == '.') vis[i][left] = 1;
                            else ok2 = 0;
                        }
                        if(down < n && ok3){
                            if(grid[down][j] == '?'){
                                cout << "0\n";
                                return;
                            }
                            else if(grid[down][j] == '.') vis[down][j] = 1;
                            else ok3 = 0;
                        }
                        if(right < n && ok4){
                            if(grid[i][right] == '?'){
                                cout << "0\n";
                                return;
                            }
                            else if(grid[i][right] == '.') vis[i][right] = 1;
                            else ok4 = 0;
                        }
                    }
                }
                else{
                    int num = grid[i][j] - '0';
                    int cont = 0;
                    FOR(dx,-1,2){
                        FOR(dy,-1,2){
                            if(abs(dx)+abs(dy) == 1){
                                int ddx = dx + i;
                                int ddy = dy + j;
                                if(ddx >= 0 && ddx < n && ddy >= 0 && ddy < n){
                                    if(grid[ddx][ddy] == '?') cont++;
                                } 
                            }
                        }
                    }
                    if(cont != num){
                        cout << "0\n";
                        return;
                    }
                }
            }
        }

        FOR(i,0,n){
            FOR(j,0,n){
                if(grid[i][j] == '.' && !vis[i][j]){
                    cout << "0\n";
                    return;
                }
            }
        }

        cout << "1\n";
    }

    int main(){
        ios::sync_with_stdio(false);
        cin.tie(0);
        solve();

        return 0;
    }