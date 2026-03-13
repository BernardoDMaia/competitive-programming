#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);
    int a1,p1,a2,p2; cin >> a1 >> p1 >> a2 >> p2;
    if((a1+a2) == (p1+p2)) cout << 'D' << endl;
    else if((a1+a2) > (p1+p2)) cout << 'A' << endl;
    else cout << 'P' << endl;
}