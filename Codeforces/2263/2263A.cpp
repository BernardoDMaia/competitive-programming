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
    int n; cin >> n;
    int qtd1 = 0, qtd0 = 0;
    FOR(i,0,n){
        int x; cin >> x;
        if(x) qtd1++;
        else qtd0++;
    }

    if(qtd1 >= qtd0) cout << "Bessie\n";
    else cout << "Elsie\n";
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t = 1; 
    cin >> t;
    while(t--)
    solve();
    return 0;
}