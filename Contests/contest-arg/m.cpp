#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);cin.tie(0);
    double n, t; cin >> n >> t;
    double tp = t*(double)0.75;
    double tnp = t*(double)0.25;
    vector<double>p, np;

    for(int i = 0; i < n; i++){
        char c; cin >> c;
        double x; cin >> x;
        if(c == 'P') p.push_back(x);
        else np.push_back(x);
    }

    sort(p.begin(),p.end());
    sort(np.begin(),np.end());

    int tamP = p.size();
    int tamNP = np.size();
    int idxP = 0, idxNP = 0;
    double dp = 0, dnp = 0;
    double ans = 0;

    while(tamP > 0 && tamNP > 0){
        if(p[idxP] == 0){
            tamP--;
            idxP++;
            continue;
        }
        if(np[idxNP] == 0){
            tamNP--;
            idxNP++;
            continue;
        }
        double timeP = (p[idxP] - dp)/(tp/tamP); 
        double timeNP = (np[idxNP] - dnp)/(tnp/tamNP);
        if(timeP <= timeNP){
            ans += timeP;
            dp += (tp/tamP) * timeP;
            dnp += (tnp/tamNP) * timeP;
            tamP--;
            idxP++;
        }
        else{
            ans += timeNP;
            dp += (tp/tamP) * timeNP;
            dnp += (tnp/tamNP) * timeNP;
            tamNP--;
            idxNP++;
        }
    }

    if(tamP != 0){
        while(tamP != 0){
            double timeP = (p[idxP] - dp)/(t/tamP); 
            ans += timeP;
            dp += (t/tamP) * timeP;
            tamP--;
            idxP++;
        }
    }
    
    if(tamNP != 0){
        while(tamNP != 0){
            double timeNP = (np[idxNP] - dnp)/(t/tamNP); 
            ans += timeNP;
            dnp += (t/tamNP) * timeNP;
            tamNP--;
            idxNP++;
        }
    }

    cout << ans << endl;
}