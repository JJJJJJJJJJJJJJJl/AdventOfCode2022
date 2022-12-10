#include "../bits/stdc++.h"
using namespace std;

int main(){
    int cycle_matter = 20;
    int cur_cycle = 0;
    int x = 1;
    char screen[10][50];
    for(int i=0; i<6; i++){
        for(int j=0; j<40; j++){
            screen[i][j] = '.';
        }
    }
    string instr;
    while(getline(cin, instr)){
        stringstream stream(instr);
        string op;
        stream >> op;
        if(op == "noop"){
            cur_cycle++;
            int row = (int)(cur_cycle / 40);
            int col = (int) (cur_cycle % 40);
            if(col >= x && col <= x+2){
                screen[row][col] = '#';
            }
            if(cur_cycle == cycle_matter){
                cycle_matter += 40;
            }
            continue;
        }
        string sval;
        stream >> sval;
        int val = stoi(sval);

        for(int i=0; i<2; i++){
            cur_cycle++;
            int row = (int)(cur_cycle / 40);
            int col = (int) (cur_cycle % 40);
            if(col >= x && col <= x+2){
                screen[row][col] = '#';
            }
            if(cur_cycle == cycle_matter){
                cycle_matter += 40;
            }
        }  
        x += val; 
    }
    for(int i=0; i<6; i++){
        for(int j=0; j<40; j++){
            cout << screen[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}