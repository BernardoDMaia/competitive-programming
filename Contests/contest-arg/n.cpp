#include<bits/stdc++.h>
using namespace std;
#define ll long long 


int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);
    int n; cin >> n;
    vector<int>v(n);
    int cont0 =  0, cont1 = 0, cont2 = 0, cont3 = 0, cont4= 0;

    for(int i = 0; i < n; i++){
        int x; cin >> x;
        v[i] = x%5;
        if(v[i] == 0) cont0++;
        if(v[i] == 1) cont1++;
        if(v[i] == 2) cont2++;
        if(v[i] == 3) cont3++;
        if(v[i] == 4) cont4++;
    }

    int ans = 0;
    ans += cont0;

    int a;
    a = min(cont4, cont1);
    ans += a;
    cont4 -= a; cont1 -= a;

    a = min(cont2, cont3);
    ans += a;
    cont3 -= a; cont2 -= a;

    a = min(cont1/2, cont3);
    ans += a;
    cont1 -= 2*a; cont3 -= a;

    a = min(cont2/2, cont1);
    ans += a;
    cont2 -= 2*a; cont1 -= a;

    a = min(cont3/2, cont4);
    ans += a;
    cont3 -= 2*a; cont4 -= a;

    a = min(cont4/2, cont2);
    ans += a;
    cont4 -= 2*a; cont2 -= a;

    a = min(cont1/3, cont2);
    ans += a;
    cont1 -= 3*a; cont2 -= a;

    a = min(cont2/3, cont4);
    ans += a;
    cont2 -= 3*a; cont4 -= a;

    a = min(cont3/3, cont1);
    ans += a;
    cont3 -= 3*a; cont1 -= a;

    a = min(cont4/3, cont3);
    ans += a;
    cont4 -= 3*a; cont3 -= a;

    ans += cont1/5;
    ans += cont2/5;
    ans += cont3/5;
    ans += cont4/5;

    cout << ans << endl;

}
 