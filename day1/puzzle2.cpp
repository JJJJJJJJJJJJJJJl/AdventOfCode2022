#include <bits/stdc++.h>
using namespace std;

int main(){
    set<int> elves_cals;
    int cur_elve_cals = 0;
    string cals;
    while (getline(cin, cals)){
        if(cals.length() == 1){
            elves_cals.insert(cur_elve_cals);
            cur_elve_cals = 0;
        }
        else cur_elve_cals += stoi(cals);
    }
    elves_cals.insert(cur_elve_cals);

    int top_three_elves_cals = 0;
    set<int>::reverse_iterator it;
    int k;
    for (it=elves_cals.rbegin(), k=0; it!=elves_cals.rend(), k<3; it++, k++){
        top_three_elves_cals += *it;
    }
    cout << top_three_elves_cals << endl;
    return 0;
}