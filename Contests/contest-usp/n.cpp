#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main(){
    ios::sync_with_stdio(false);cin.tie(0);
    ll d, y; cin >> d >> y;

    ll dist = 1, pos = 0, aux = 1, l = 0, r = 0;

    while(d>=dist){
        d -= dist;
        pos += aux;
        if(dist == 1){
            aux = -3;
            dist = 3;
        }
        else{
            dist *= 2;
            aux *= -2;
        }
        l = min(l,pos);
        r = max(r,pos);
        cout << "pos:" << pos << " " << "dist:" << dist << " " << "aux:" << aux << " " << "l:" << l << " " << "r:" << r << endl;
    }

    if(d != 0){
        if(aux>0)pos += d;
        else pos -= d;
    }

    ll x = y - pos;

    if((y > (x+l)) && (y < (x+r))){
        cout << "Nao" << endl;
    }
    else{
        cout << "Sim" << endl;
        cout << x << endl;
    }

}