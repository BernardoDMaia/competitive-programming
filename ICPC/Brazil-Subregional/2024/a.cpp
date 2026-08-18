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

void solve(){
    int n, c; cin >> n >> c;
    int pos = min(c, n-c+1);
    int b = c / pos;
    int r = c % pos;

    int custo = 0;
    vi ans;
    auto f = [&](auto &&self, int l, int r) -> void {
        if(r < l) return;
        int mid = (r+l)/2;

        self(self,l, mid-1);
        self(self, mid+1, r);

        ans.pb(mid);
        custo += r-l;
    };

    int init = 1;
    FOR(i,0,pos){
        int tam;
        if(i < r) tam = b+1;
        else tam = b;

        f(f,init, init + tam-1);
        init += tam+1;
    }

    cout << custo << "\n";
    for(auto x : ans) cout << x << " ";
    cout << "\n";
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1;
    // cin >> t;
    while(t--)
    solve();
    return 0;
}