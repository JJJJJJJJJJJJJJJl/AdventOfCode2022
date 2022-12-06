#include "../bits/stdc++.h"
using namespace std;

int main(){
    string signal;
    cin >> signal;
    int * occs = (int *) malloc(sizeof(int)*26);
    memset(occs, 0, sizeof(int)*26);
    int n = signal.length();
    bool marker;
    
    int l = 0, r = 3;
    stack<int> fckoff;
    while(r < n){
        marker = true;
        for(int i=l; i<=r; i++){
            fckoff.push(signal[i]-97);
            occs[signal[i]-97]++;
            if(occs[signal[i]-97] > 1) marker &= false;
        }
        if(marker){
            cout << r+1 << endl;
            return 0;
        }
        while(!fckoff.empty()){
            occs[fckoff.top()]--;
            fckoff.pop();
        }
        l++;r++;
    }
    free(occs);
    return 0;
}