#include <bits/stdc++.h>
using namespace std;
#define int long long
using vi = vector<int>;
#define FOR(i,a,b) for(int i =a;i<b;i++)
#define all(x) x.begin(), x.end()
using pii = pair<int,int>;
#define pb push_back
#define sz(x) x.size()
#define deb(x) cerr << #x << "= " << x << "\n";
#define deb2(x,y) cerr << #x << "= " << x << ", "<< #y << "= " << y << "\n";
//ctrl+alt+a p/ accepted
//1 2 3 4 5
//v p1 v p2 p3
//1 2 3 4 5
//p3 v p1 p2 v
//5 1 2 4 3

//1 0 2

//2 1 0

struct segtree{
    int size = 1;
    vi tree;
    const int NEUTRO = 0;

    void init(int n){
        while(size < n) size *= 2;
        tree.assign(2 * size, NEUTRO);
    }

    void build(vi& a, int x, int lx, int rx){
        if(rx - lx == 1){
            if(lx < sz(a)) tree[x] = a[lx];
            return;
        }
        int m = (lx + rx) / 2;
        build(a, 2*x+1, lx, m);
        build(a, 2*x+2, m, rx);
        tree[x] = tree[2*x+1] + tree[2*x+2];
    }

    void set(int i, int v, int x, int lx, int rx){
        if(rx - lx == 1){
            tree[x] = v;
            return;
        }
        int m = (lx + rx) / 2;
        if(i < m) set(i, v, 2*x+1, lx, m);
        else set(i, v, 2*x+2, m, rx);
        tree[x] = (tree[2*x+1] + tree[2*x+2]);
    }

    int query(int l, int r, int x, int lx, int rx){
        if(lx >= r || rx <= l) return NEUTRO;
        if(l <= lx && rx <= r) return tree[x];
        int m = (lx + rx) / 2;
        return (query(l, r, 2*x+1, lx, m) +
                   query(l, r, 2*x+2, m, rx));
    }

    void set(int i, int v){ set(i, v, 0, 0, size); }
    int query(int l, int r){ return query(l, r, 0, 0, size); }
    void build(vi& a){ build(a, 0, 0, size); }
};

const int MAXN = 1e6;

void solve(){
    int n; cin >> n;
    vi init(n), final(MAXN);
    FOR(i,0,n) cin >> init[i];
    FOR(i,0,n) cin >> final[i];

    segtree st;
    st.init(n);

    vi compFinal(n), compInit(n);
    vector<pii> aux1(n), aux2(n), aux3(n);

    FOR(i,0,n) aux1[i] = {init[i], i};
    sort(all(aux1));//monta a ordem original
    FOR(i,0,n) compInit[aux1[i].second] = i;

    FOR(i,0,n) aux2[i] = {final[i], i};
    sort(all(aux2));
    FOR(i,0,n) compFinal[aux2[i].second] = i;

    int ans = 0;
    for(auto [v,pessoa] : aux2){
        int x = compInit[pessoa];

        ans += st.query(x+1,n);
        st.set(x, 1);
    }

    //counting zeros
    FOR(i,0,n){
        int zerosInit = init[i] - compInit[i];
        int zerosFinal = final[i] - compFinal[i];

        ans += abs(zerosInit - zerosFinal);
    }

    cout << ans << "\n";
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--)
    solve();
    return 0;
}