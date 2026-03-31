#include <bits/stdc++.h>
using namespace std;
using ll= long long;
using vi = vector<int>;
using vll =vector<ll>;
using vpii =vector<pair<int,int>>;
#define FOR(i,a,b) for(int i=a;i<(b);i++)
#define all(x) x.begin(), x.end()
#define pb push_back
#define sz(x) (int)x.size()

void solve(){
    string s; cin >> s;
    int tam = sz(s);

    set<string>ans;
    FOR(i,0,tam){
        string aux;
        FOR(j,i,tam){
            aux += s[j];
            ans.insert(aux);
        }
    }

    cout << sz(ans) << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
    return 0;
}