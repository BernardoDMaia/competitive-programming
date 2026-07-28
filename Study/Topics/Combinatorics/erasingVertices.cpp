#include <bits/stdc++.h>
using namespace std;
#define int long long
using vi = vector<int>;
#define FOR(i, a, b) for (int i = a; i < (b); i++)
#define all(x) x.begin(), x.end()
#define pb push_back
#define sz(x) (int)(x).size()
#define deb(x) cerr << #x << " = " << x << "\n";
#define deb2(x,y) cerr << #x << "=" << x << ", " << #y << "=" << y << "\n";
#define deb3(x,y,z) cerr << #x << "=" << x << ", " << #y << "=" << y << ", " << #z << "=" << z << "\n";

void solve(){
    int n; cin >> n;
    vector<vi>adj(n, vi(n));
    FOR(i,0,n){
        FOR(j,0,n){
            char c; cin >> c;
            adj[i][j] = (c == '1');
        }
    }

    vi v(n); //quem tira i
    FOR(i,0,n){
        //tirar vertice i
        queue<int>q;
        q.push(i);
        vi vis(n,0);
        vis[i] = 1;
        //quem chega a partir de i
        while(!q.empty()){
            int curr = q.front();
            q.pop();
            FOR(j,0,n){
                if(adj[curr][j] && !vis[j]){
                    v[j]++;//chega no vertice j
                    vis[j] = true;
                    q.push(j);
                }
            }
        }
    }

    double ans = 0.0;
    FOR(i,0,n){
        ans += 1.0/(v[i] + 1);
    }
    cout << fixed << setprecision(15);
    cout << ans << "\n";
    
}

signed main(){
    ios::sync_with_stdio(false); 
    cin.tie(0);
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
    return 0;
}