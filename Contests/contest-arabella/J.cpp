#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    ios::sync_with_stdio(false); cin.tie(0);
    
    string s; cin >> s;
    ll ans = 0;
    int size_s = s.size();
    
    for(int i = size_s - 1; i >= 0; i--){
        
        if(s[i] == '5'){
            
        }

        if(s[i] > '5'){
            ans += '9' - s[i] + 1;
            for(int j = i - 1; j >= 0; j--){
                if(s[j] >= '9'){
                    s[j] = '0';
                }
                else{
                    s[j]++;
                    break;
                }
            }
        }

        else{
            ans += s[i] - '0';
        }
    }

    if(s[0] == '0' || s[0] > '5') ans++;

    cout << ans << endl;
}
