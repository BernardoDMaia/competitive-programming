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

struct DSU{
    vi e;
    void init(int n){
        e = vi(n,-1);
    }

    int get(int x){
        return e[x] < 0 ? x : e[x] = get(e[x]);
    }

    bool sameSet(int a, int b){
        return get(a) == get(b);
    }
    int size(int x){
        return -e[get(x)];
    }
    bool unite(int x, int y){
        x = get(x), y = get(y);
        if(x==y) return 0;
        if(e[x]>e[y]) swap(x,y);
        e[x] += e[y];
        e[y] = x;
        return 1;
    }
};

void solve(){
 //   freopen("mootube.in", "r", stdin);
   // freopen("mootube.out", "w", stdout);
    int n,q; cin >> n >> q;
    DSU dsu;
    dsu.init(n);

    vector<tuple<int,int,int>>adj, queries;

    FOR(i,0,n-1){
        int a, b, c; cin >> a >> b >> c;
        a--;b--;
        adj.pb({c,a,b});
    }
    FOR(i,0,q){
        int k, v; cin >> k >> v;
        v--;
        queries.pb({k,v,i});
    }

    sort(all(adj)); reverse(all(adj));
    sort(all(queries)); reverse(all(queries));

    int j = 0;
    vi ans(q);
    FOR(i,0,q){
        auto [k,v,idx] = queries[i];

        while(true){
            if(j==sz(adj)) break;
            auto [kadj, x, y] = adj[j];
            if(kadj < k) break;
            dsu.unite(x,y);
            j++;
        }

        ans[idx] = dsu.size(v) - 1;
    }

    for(int u : ans) cout << u << "\n";
    
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    // int t = 1;
    // cin >> t;
//    while(t--){
        solve();
  //  }
}