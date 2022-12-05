#include "../bits/stdc++.h"
using namespace std;

int main(){
    vector<vector<char>> reverse_order;
    string line;
    bool moves = false;
    vector<stack<char>> stacks;
    while(getline(cin, line)){
        vector<char> stacks_level;
        int n = line.length();
        if(n == 0){
            moves = true;
            for(int i=0; i<reverse_order[0].size(); i++){
                stack<char> st;
                for(int j=reverse_order.size()-1; j>-1; j--){
                    if(isalpha(reverse_order[j][i])) st.push(reverse_order[j][i]);
                }
                stacks.push_back(st);
            }
            continue;
        }
        if(!moves){
            int z = 1;
            int cur_stack = 0;
            for(int i=0; i<n; i++){
                if(z == 2){
                    stacks_level.push_back(line[i]);
                }
                else if(z == 4){
                    cur_stack++;
                    z = 0;
                }
                z++;
            }
            reverse_order.push_back(stacks_level);
        }
        else{
            int spaces = 0;
            int move;
            int from;
            int to;
            string num = "";
            for(int i=0; i<n; i++){
                if(line[i] == ' '){
                    if(spaces == 1){
                        move = stoi(num);
                    }
                    else if(spaces == 3){
                        from = stoi(num);
                    }
                    num = "";
                    spaces++;
                    continue;
                }
                if(isdigit(line[i]) && spaces % 2 != 0){
                    num += line[i];
                }
            }
            to = stoi(num);
            vector<char> crane9001_queue;
            while(move > 0){
                if(!stacks[from-1].empty()){
                    crane9001_queue.push_back(stacks[from-1].top());
                    stacks[from-1].pop();
                }
                move--;
            }
            for(int k=crane9001_queue.size()-1; k>-1; k--){
                stacks[to-1].push(crane9001_queue[k]);
            }
        }
    }
    string ans = "";
    for(int i=0; i<reverse_order[0].size(); i++){
        ans += stacks[i].top();
    }
    cout << ans << endl;
    return 0;
}