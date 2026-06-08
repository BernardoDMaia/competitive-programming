#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vi = vector<int>;
#define FOR(i,a,b) for(int i = a; i<(b);i++)

void solve(){
    int n; cin >> n;
    string s; cin >> s;
    int contD = 0, contK = 0;
    map<pair<int,int>, int> freq;

    FOR(i,0,n){
        if(s[i] == 'D') contD++;
        else contK++;
        int d = gcd(contD,contK);
        int x = contD/d;
        int y = contK/d;
        freq[{x,y}]++;
        
        cout << freq[{x,y}]<< " ";
    }
    cout << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t; cin >> t;
    while(t--){
        solve();
    }
    return 0;
}