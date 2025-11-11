#include<bits/stdc++.h>
using namespace std;
#define ll long long

bool vowel(char c){
    if(c == 'a' || c == 'e'|| c == 'i'|| c == 'o'|| c == 'u'|| c == 'y') return true;
    return false;
}


int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    string s, ans; cin >> s;

    for(int i = 0; i < s.size(); i++){
        s[i] = tolower(s[i]);
        if(!vowel(s[i])){
            ans += '.';
            ans += s[i];
        }
    }

    cout << ans << endl;

}