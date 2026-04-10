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
    int n,q; cin >> n >> q;
    DSU dsu;
    dsu.init(n);
    while(q--){
        int tp, x,y; cin >> tp >> x >> y;
        if(tp==0){
            dsu.unite(x,y);
        }else{
            if(dsu.sameSet(x,y)) cout << "1\n";
            else cout << "0\n";
        }
    }
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