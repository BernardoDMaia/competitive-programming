#include<bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);

    int n, m; cin >> n >> m;
    vector<int>seats(m);

    for(int i = 0; i < m;i++){
        cin >> seats[i];
    }

    int l, cont = 0; cin >> l;

    for(int i = 0; i < m; i++){
        if(seats[i] > l) cont++;
    }

    if(cont >= n) cout << "SIM" << endl;
    else cout << "NAO" << endl;
}