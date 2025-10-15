#include <bits/stdc++.h>
using namespace std;

int main(){
    int n; cin >> n;
    string orig, writ;
    for(int i = 0; i < n; i++){
        string s; cin >> s;
        orig += s;
        if(i == n-1) continue;
        orig += " ";
    }

    int m; cin >> m;
    bool caps = false;

    while(m--){
        string r; cin >> r;
        
        if(r == "Backspace"){
            if(writ.size() > 0) writ.pop_back();
        }
        
        else if(r == "CapsLock"){
            if(caps) caps = false;
            else caps = true;
        }

        else if(r == "Space") writ += " ";

        else{
            if(caps) writ += toupper(r[0]);
            else writ += r;
        }
    }

    if(orig == writ) cout << "Correct" << endl;
    else cout << "Incorrect" << endl;
}
