#include <bits/stdc++.h>
using namespace std;

const int MAX = 2e5 + 5;
vector<int>v(MAX);
vector<int>graph[MAX];
vector<bool>vis(MAX, false);
vector<bool>repeat(MAX,true);
map<int,int>freq;

void dfs(int x){
    vis[x] = true;
    freq[v[x]]++;
    
    if(freq[v[x]] == 2){
        freq[v[x]]--;
        return;
    }
    
    repeat[x] = false;
    for(auto y: graph[x]){
        if(!vis[y]) dfs(y);
    }

    freq[v[x]]--;
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;

    for(int i = 0; i < n; i++){
        cin >> v[i];
        freq[v[i]] = 0;
    }
    
    for(int i = 0; i< n-1; i++){
        int u,w; cin >> u >> w;
        u--;w--;
        graph[u].push_back(w);
        graph[w].push_back(u);
    }

    dfs(0);

    for(int i = 0; i < n; i++){
        if(repeat[i]) cout << "Yes" << endl;
        else cout << "No" << endl;
    }

}