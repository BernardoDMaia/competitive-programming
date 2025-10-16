#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    ios::sync_with_stdio(false); cin.tie(0);
    
    string s, resp = ""; cin >> s;
    vector<int>freq(26, 0);

    for(int i = 0; i < s.size(); i++){
        freq[s[i] - 'a']++;
    }

    for(int i = 0; i < 25; i++){
        if(freq[i] != 0){
            if(freq[i] % 2 == 1) resp += 'a' + i;
            freq[i+1] += freq[i] / 2;
        }
    }

    for(int i = 0; i < freq[25]; i++){
        resp += 'z';
    }

    sort(resp.rbegin(), resp.rend());

    cout << resp << endl;
}
