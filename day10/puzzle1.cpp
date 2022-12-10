#include "../bits/stdc++.h"
using namespace std;

int main(){
    int ans = 0;
    int cycle_matter = 20;
    int cur_cycle = 0;
    int x = 1;
    string instr;
    while(getline(cin, instr)){
        stringstream stream(instr);
        string op;
        stream >> op;
        if(op == "noop"){
            cur_cycle++;
            if(cur_cycle == cycle_matter){
                ans += x*cur_cycle;
                cycle_matter += 40;
            }
            continue;
        }
        string sval;
        stream >> sval;
        int val = stoi(sval);

        for(int i=0; i<2; i++){
            cur_cycle++;
            if(cur_cycle == cycle_matter){
                ans += x*cur_cycle;
                cycle_matter += 40;
            }
        }  
        x += val; 
    }
    cout << ans << endl;
    return 0;
}