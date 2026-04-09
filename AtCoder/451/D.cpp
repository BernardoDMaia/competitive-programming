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

void solve(){
    int n; cin >> n;

    set<int>ss;
    auto recursao = [&](auto &&self, string a) ->void {
        if(sz(a)>0)ss.insert(stoi(a));
        int v = 1;
        while(true){
            string s = to_string(v);
            if(sz(s)+sz(a)<=9){
                string aux = "";
                aux += a;
                aux += s;
                self (self, aux);
            }
            else break;
            v*=2;
        }
    };

    recursao(recursao,"");
    auto it = ss.begin();
    advance(it, n-1);
    cout << *it << endl;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    solve();
}