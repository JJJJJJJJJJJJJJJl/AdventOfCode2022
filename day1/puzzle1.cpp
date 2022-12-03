#include <bits/stdc++.h>
using namespace std;

int main(){
    int max_cals = INT_MIN;
    int cur_elve_cals = 0;
    string cals;
    while (getline(cin, cals)){
        if(cals.length() == 1){
            max_cals = max(max_cals, cur_elve_cals);
            cur_elve_cals = 0;
        }
        else cur_elve_cals += stoi(cals);
    }
    max_cals = max(max_cals, cur_elve_cals);
    cout << max_cals << endl;
    return 0;
}