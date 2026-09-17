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
const int MOD = 998244353;

/*
Se eu faço um update em Ai
    (Ai+x)*Bi -> Ai*Bi + x*Bi
E vice versa para Bi

Se há uma query em cada
    (Ai+x)*(Bi+y) -> Ai*Bi + Ai*y + Bi*x + x*y

Então num intervalo de tamanho len = r-l+1:
    sum[l,r] = sum Ai*Bi + sum Ai*y + sum Bi*x + sum x*y
    sum[l,r] = sum Ai*Bi + y*sum Ai + x*sum Bi + len*x*y

E se quero +x e depois +y no mesmo vetor, posso somar ambos e adicionar +(x+y)
*/

enum QueryType { UPDATE, SET, NONE };

struct Tag{
    QueryType type = NONE;
    int x = 0, y = 0;

    void apply(const Tag& t){
        if(t.type == UPDATE){
            type = UPDATE;
            x = (x + t.x) % MOD;
            y = (y + t.y) % MOD;
        }
    }

};

struct Info{
    int val = 0;
    int suma = 0;
    int sumb = 0;

    void apply(const Tag& t, int l, int r){
        if(t.type == UPDATE){
            int len = r-l+1;

            int s1 = t.y % MOD * suma % MOD;
            int s2 = t.x % MOD * sumb % MOD;
            int s3 = len * t.x % MOD * t.y % MOD;

            val = (val+s1+s2+s3) % MOD; 

            suma = (suma + (len* t.x %MOD)) % MOD;
            sumb = (sumb + (len* t.y %MOD)) % MOD;
        }
    }
};

Info operator+(const Info& a, const Info& b){
    Info ret;
    ret.val = (a.val + b.val) % MOD;
    ret.suma = (a.suma + b.suma) % MOD;
    ret.sumb = (a.sumb + b.sumb) % MOD;

    return ret;
}

template<class Info, class Tag>
struct LazySegtree{
    int n;
    vector<Info> tree;
    vector<Tag> lazy;

    LazySegtree(int n) : n(n){
        tree.assign(4*n, Info());
        lazy.assign(4*n, Tag());
    }

    LazySegtree(const vector<Info>& a) : n(sz(a)){
        tree.assign(4*n, Info());
        lazy.assign(4*n, Tag());
        build(1, 0, n-1, a);
    }

    void build(int v, int l, int r, const vector<Info>& a){
        if(l == r){ tree[v] = a[l]; return; }
        int m = (l+r)/2;
        build(2*v, l, m, a);
        build(2*v+1, m+1, r, a);
        tree[v] = tree[2*v] + tree[2*v+1];
    }

    void apply(int v, int l, int r, const Tag& x){
        tree[v].apply(x, l, r);
        lazy[v].apply(x);
    }

    void push(int v, int l, int r){
        if(lazy[v].type == NONE || l == r) return;
        int m = (l+r)/2;
        apply(2*v, l, m, lazy[v]);
        apply(2*v+1, m+1, r, lazy[v]);
        lazy[v] = Tag();
    }

    void update(int v, int l, int r, int ql, int qr, const Tag& x){
        if(qr < l || r < ql) return;
        if(ql <= l && r <= qr){ apply(v, l, r, x); return; }
        push(v, l, r);
        int m = (l+r)/2;
        update(2*v, l, m, ql, qr, x);
        update(2*v+1, m+1, r, ql, qr, x);
        tree[v] = tree[2*v] + tree[2*v+1];
    }

    Info query(int v, int l, int r, int ql, int qr){
        if(qr < l || r < ql) return Info();
        if(ql <= l && r <= qr) return tree[v];
        push(v, l, r);
        int m = (l+r)/2;
        return query(2*v, l, m, ql, qr) + query(2*v+1, m+1, r, ql, qr);
    }

    void update(int ql, int qr, const Tag& x){ update(1, 0, n-1, ql, qr, x); }
    Info query(int ql, int qr){ return query(1, 0, n-1, ql, qr); }
};

void solve(){
    int n, q; cin >> n >> q;
    vi va(n); FOR(i,0,n) cin >> va[i];
    vi vb(n); FOR(i,0,n) cin >> vb[i];

    vector<Info> base(n);
    FOR(i,0,n) base[i] = {(va[i]*vb[i] % MOD), va[i], vb[i]};
    LazySegtree<Info, Tag> lst(base);

    while(q--){
        int type, l ,r; cin >> type >> l >> r;
        l--;r--;
        if(type == 1){
            int x; cin >> x;
            lst.update(l,r, {UPDATE,x,0});
        }
        else if(type == 2){
            int y; cin >> y;
            lst.update(l,r,{UPDATE,0,y});
        }
        else cout << lst.query(l,r).val << "\n";
    }

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