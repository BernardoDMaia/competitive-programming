#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);
    int n; cin >> n;
    
    while(n--){

        string s, p; cin >> s >> p;
    
        int ls = 0, rs = 0, lp = 0, rp = 0;
        int ok = 1;
        while(rs < s.size() && rp < p.size()){
            while(rs < s.size() && s[ls] == s[rs]){
                rs++;
            }
            while(rp < p.size() && s[ls] == p[rp]){
                rp++;
            }
            if(rp-lp < rs-ls || rp-lp > 2*(rs-ls)){
                ok = 0;
                break;
            }
            else{
                ls = rs;
                lp = rp;
            }
        }

        if(rs != s.size() || rp != p.size()) ok = 0;
    
        if(ok == 0) cout << "NO" << endl;
        else cout << "YES" << endl;
    }
    
}