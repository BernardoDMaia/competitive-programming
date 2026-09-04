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
    string s; cin >> s;

    int first1 = 0;
    while(first1 < n && s[first1] == '0') first1++;

    int first0 = first1+1;
    while(first0 < n && s[first0] == '1') first0++;

    if(first1 == n){
        cout << "0\n";
        return;
    }
    else if(first0 == n){
        cout << s.substr(first1) << "\n";
        return;
    }

    int tam = n - first0;
    string ans(tam, '0');

    FOR(i,first1, first0){
        string aux = s.substr(i, tam);
        FOR(k,0,tam){
            if(ans[k] != aux[k] && s[first0+k] != '1'){
                if(aux[k] == '1') ans = aux;
                break;
            }
        }
    }
    FOR(i,first1, first0) cout << "1";
    FOR(i,0,tam) if(ans[i] == '0' && s[first0+i] == '1') ans[i] = '1';
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