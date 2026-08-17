#include <bits/stdc++.h>
using namespace std;
#define int long long
using vi = vector<int>;
#define FOR(i,a,b) for(int i =a;i<b;i++)
#define all(x) x.begin(), x.end()
#define deb(x) cerr << #x << "= " << x << "\n";
#define deb2(x,y) cerr << #x << "= " << x << ", "<< #y << "= " << y << "\n";
#define pb push_back
#define sz(x) x.size()
struct DSU{
    vi f,siz;
    DSU(){}
    DSU(int n){
        init(n);
    }
    void init(int n){
        f.resize(n);
        iota(all(f),0);
        siz.assign(n,1);
    }
    int find(int x){
        while(x!=f[x]) x=f[x]=f[f[x]];
        return x;
    }
    bool same(int x,int y){
        return find(x)==find(y);
    }
    bool merge(int x, int y){
        x=find(x);
        y=find(y);
        if(x==y) return false;
        if(siz[x]<siz[y]) swap(x,y);
        siz[x]+=siz[y];
        f[y]=x;
        return true;
    }
};


void solve(){
    int n, m, q; cin >> n>> m >> q;
    vector<vector<pair<int,int>>> adj(m);
    vector<vi> caras(n);
    DSU dsu(m);
    FOR(i,0,n){
        int x; cin >> x;
        int prim=-1;
        FOR(j,0,x){
            int v; cin >> v;
            v--;
            caras[i].pb(v);
            if(prim==-1){
                prim=v;
            }else{
               // cout << "erro\n";
                if(dsu.merge(prim,v)){
                    adj[prim].pb({v,i});
                    adj[v].pb({prim,i});
                }
            }
        }
    }
    while(q--){
        int a,b; cin >> a >> b;
        a--;b--;
        
        int v1 = caras[a][0], v2 = caras[b][0];
        if(!dsu.same(v1,v2)){
            cout << "-1\n";
           // cout << "e2\n";
            continue;
        }
        vi vis(m,-1);
        queue<pair<int,int>> q;
        for(auto x : caras[a]){
            q.push({x,a});
            vis[x]=0;
        }
        while(!q.empty()){
            auto [u,pai]=q.front();
            q.pop();
            if(find(all(caras[b]), u)!= caras[b].end()){
                cout << vis[u] << "\n";
                break;
            }
            for(auto x: caras[pai]){
                if(vis[x]!=-1) continue;
                q.push({x,pai});
                vis[x]=vis[u];
            }
            
            for(auto [v,fds] : adj[u]){
                if(vis[v]!=-1) continue;
                q.push({v,fds});
                vis[v]=vis[u]+1;
            }
        }
    }
}


signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    solve();
    return 0;
}