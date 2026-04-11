#include<bits/stdc++.h>
using namespace std;

void solve(){
    int n; cin >> n;
    string s = to_string(n);
    int ans = 0;

    int aux = n;
    if(n <= 9){
        cout << 0 << "\n";
        return;
    }
    while(true){
        int aux2 = 1;
        for(int i = 0; i < s.size(); i++){
            int a = s[i] - '0';
            aux2 *= a;
        }
        ans++;
        //cout << "aux2:" << aux2 << "\n";
        if(aux2 <= 10) break;
        else{
            s = to_string(aux2);
        }
        cout << "str:" << s << "\n";
    }

    cout << ans << "\n";
}

int main(){
    int t; cin >> t;
    while(t--){
        solve();
    }
}