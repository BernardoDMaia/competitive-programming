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

void solve(){
    int n, q; cin >> n >> q;

    vi prefix(q+1, 0);
    vi ans(n, 0);
    vi estados(n,0);
    int tam = 0;

    FOR(i,1,q+1){
        int x; cin >> x;
        x--;
        if(estados[x]){
            tam--;
            //recolhe todos desde que entrou; i-1 pois nao recolhe esse, estados[x]-1 pois estados[x] conta
            ans[x] += (prefix[i-1] - prefix[estados[x] - 1]);
            estados[x] = 0; //saiu
        }
        else{
            tam++;
            estados[x] = i; //quando entrou
        }
        prefix[i] = prefix[i-1] + tam;
    }
    FOR(i,0,n){//aqueles que nao saíram
        if(estados[i]) ans[i] += (prefix[q] - prefix[estados[i]-1]);
    }

    for(int x : ans) cout << x << " ";
    cout << "\n";
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