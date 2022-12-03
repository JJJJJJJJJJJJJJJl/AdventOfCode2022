#include <bits/stdc++.h>
using namespace std;

/* 
    Rock <- 1
    Paper <- 2
    Scissors <- 3
 */

int round_result(int elf_move, int my_move){
    if(my_move == 1 && elf_move == 3) return 6; 
    if(my_move < elf_move || (my_move == 3 && elf_move == 1)) return 0;
    else if(my_move == elf_move) return 3;
    return 6;
}

int main(){
    int ans = 0;

    map<char,int> char_to_move;
    char_to_move['A'] = 1;char_to_move['X'] = 1;
    char_to_move['B'] = 2;char_to_move['Y'] = 2;
    char_to_move['C'] = 3;char_to_move['Z'] = 3;

    char last_c;
    char c;
    int k = 0;
    while(cin.get(c)){
        if(c == '\0' ||c == ' ' || c == '\n' || c == 13) continue;
        k++;
        if(k == 2){
            ans += char_to_move[c] + round_result(char_to_move[last_c], char_to_move[c]);
            k = 0;
        }
        last_c = c;
    }
    cout << ans << endl;
    return 0;
}