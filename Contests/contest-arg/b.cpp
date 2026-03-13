#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);
    int n; cin >> n;
    vector<vector<char>>grid(n, vector<char>(n));
    int ans = 0;
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) cin >> grid[i][j];
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(grid[i][j] == 'N'){
                if(j+1 < n) if(grid[i][j+1] == 'N'){
                    ans++;
                    j++;
                }
            }
        }
    }
    cout << ans << endl;
}