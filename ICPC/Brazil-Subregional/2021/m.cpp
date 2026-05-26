    #include <bits/stdc++.h>
    using namespace std;
    using ll = long long;
    using vi = vector<int>;
    #define FOR(i,a,b) for(int i =a;i<(b);i++)
    #define all(x) x.begin(), x.end()
    #define pb push_back
    #define deb(x) cerr << #x << "=" <<  x << "\n";

    const int MAXN = 1e5+5;

    void solve(){
         int q; cin >> q;

         vector<vi> adj(MAXN); // conferir 
         vi mortes;
         queue<int> ordem; // ordem de monarcas dfs

         int curr = 1;
         while(q--){
            int t, u;cin >> t >>u;
            u--;
            if(t  ==1){ //nasce
                adj[u].pb(curr);
                curr++;
            }
            else{ //morre
                mortes.pb(u);
            }
         }

         vi vis(MAXN, 0);
         auto dfs = [&](auto&& self, int u)->void{
            vis[u] = 1;
            ordem.push(u);
            for(int v: adj[u]){
                if(!vis[v]){
                    self(self,v);
                }
            }
         };
         dfs(dfs,0);
        vi ans;
        vi morridos(MAXN,0);         
         for(int m : mortes){
            morridos[m] =1; //morreu 
            if(m != ordem.front()){
                ans.pb(ordem.front());
            }
            else{
                while(morridos[ordem.front()] ){
                    ordem.pop();
                }
                ans.pb(ordem.front());
            }
         }

         for(int x : ans) cout << x +1 << "\n";

    }

    int main(){
        ios::sync_with_stdio(false);
        cin.tie(0);
        solve();

        return 0;
    }