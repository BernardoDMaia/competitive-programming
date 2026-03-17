#include <bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);
    int t; cin >> t;
    while(t--){
        int n; cin >> n;
        string s; cin >> s;
        int l_idx = 0, r_idx = 0;
        for(int i = 0; i < n-1;i++){
            if(s[i] > s[i+1]){
                char c = s[i];
                l_idx = i;
                r_idx = n-1; 
                for(int j = i+1; j < n; j++){
                    if(s[j] > c) {
                        r_idx = j-1;
                        break;
                    }
                }
                break;
            }
        }

        char first = s[l_idx];
        for(int i = l_idx; i < r_idx; i++){
            s[i] = s[i+1];
        }
        s[r_idx] = first;

        cout << s << endl;
    }
}