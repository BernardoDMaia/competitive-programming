#include <bits/stdc++.h>
using namespace std;
#define ll long long 

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);
    //freopen("milkvisits.in", "r", stdin);
    //freopen("milkvisits.out", "w", stdout);
    int n, m; cin >> n >> m;
    string s; cin >> s;
    vector<vector<int>>tree(n);

    for(int i = 0; i < n-1; i++){
        int x, y; cin >> x >> y;
        x--;y--;
        tree[x].push_back(y);
        tree[y].push_back(x);
    }

    vector<pair<int,int>>freqHG(n);
    vector<bool>vis(n);
    
    auto dfs = [&](auto &&self, int u) -> void {
        vis[u] = true;
        char cur = s[u];
        for(auto v : tree[u]){
            if(!vis[v]){
                if(cur == 'H'){
                    freqHG[v].first = freqHG[u].first + 1;
                    freqHG[v].second = freqHG[u].second;
                }
                else{
                    freqHG[v].second = freqHG[u].second + 1;
                    freqHG[v].first = freqHG[u].first;
                }
                self(self,v);
            }
        }
    };
    
    dfs(dfs, 0);
    
    vector<int>ans(m, 0);
    for(int i = 0; i < m; i++){
        int a,b; cin >> a >> b;
        a--;b--;
        char c; cin >> c;
        if(c == 'H'){
            int qtd = abs(freqHG[a].first - freqHG[b].first);
            if(s[a] == c || s[b] == c || qtd > 0) ans[i] = 1;
        }
        else{
            int qtd = abs(freqHG[a].second - freqHG[b].second);
            if(s[a] == c || s[b] == c || qtd > 0) ans[i] = 1;
        }
    }

    for(int i = 0; i < m; i++){
        cout << ans[i];
    }
    cout << endl;
}
