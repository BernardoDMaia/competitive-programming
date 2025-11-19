#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, x; cin >> n >> x;
    string s; cin >> s;

    vector<char>genes = {'A', 'C', 'G', 'T'};

    int idx, idx_comp, desloc = x;
    char c = ' ';

    for(int i = 0; i < n; i++){
        if(s[i] == 'A'){
            idx_comp = 3;
            idx = 0;
        }
        if(s[i] == 'T'){
            idx_comp = 0;
            idx = 3;
        }
        if(s[i] == 'C'){
            idx_comp = 2;
            idx = 1;
        }
        if(s[i] == 'G'){
            idx_comp = 1;
            idx = 2;
        }

        desloc = desloc ^ idx;
        c = genes[(idx_comp + desloc) % 4];
        cout << c;
    }
    cout << endl;
}