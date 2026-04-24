#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i = (a); i <(b); i++)
#define push_back pb

using vi = vector<int>;
using ll = long long;
using vl = vector<ll>;
using pii = pair<int,int>;

#define deb(x) cerr << #x << " = " << x << "\n";

void solve(){
    string s, ans = ""; cin >> s;
    int n = s.size();

    auto add = [&](int count) -> void{
        FOR(i,0,7-count) ans+= "0000:";
    };

    int count = 0, block = 0;
    string aux = "";
    
    FOR(i,0,n){
        if(s[i] == ':'){
            if(block == 1){
                block = 0;
                ans += "000";
                ans += aux;
                ans += ":";
                aux = "";
            }
            if(block == 2){
                block = 0;
                ans += "00";
                ans += aux;
                ans += ":";
                aux = "";
            }
            if(block == 3){
                block = 0;
                ans += "0";
                ans += aux;
                ans += ":";
                aux = "";
            }
            if(block == 4){
                block = 0;
                ans += aux;
                ans += ":";
                aux = "";
            }
            if(s[0] != ':') count++;

            if(s[i+1] == ':'){
                if(i+1 == n-1) count--;
                FOR(j,i+2,n) if(s[j] == ':') count++;
                add(count);
            }
        }
        else if(i == n-1){
            block++;
            aux += tolower(s[i]);
            if(block == 1){
                    block = 0;
                    ans += "000";
                    ans += aux;
                    ans += ":";
                    aux = "";
                }
                else if(block == 2){
                    block = 0;
                    ans += "00";
                    ans += aux;
                    ans += ":";
                    aux = "";
                }
                if(block == 3){
                    block = 0;
                    ans += "0";
                    ans += aux;
                    ans += ":";
                    aux = "";
                }
                if(block == 4){
                    block = 0;
                    ans += aux;
                    ans += ":";
                    aux = "";
                }
        }
        else{
            block++;
            aux += tolower(s[i]);
        }
    }
    ans.pop_back();
    cout << ans << "\n";
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t=1;
    // cin >> t;
    while(t--){
        solve();
    }
    return 0;
}
