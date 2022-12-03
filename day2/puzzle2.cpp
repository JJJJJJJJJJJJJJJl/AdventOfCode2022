#include <bits/stdc++.h>
using namespace std;

/* 
    Rock <- 1
    Paper <- 2
    Scissors <- 3
 */

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
            if(c == 'X'){
                if(char_to_move[last_c] == 1) ans += 3;
                else ans += char_to_move[last_c]-1;
            }
            else if(c == 'Y'){
                ans += 3 + char_to_move[last_c];
            }
            else{
                ans += 6;
                if(char_to_move[last_c] == 3) ans += 1;
                else ans += char_to_move[last_c]+1;
            }
            k = 0;
        }
        last_c = c;
    }
    cout << ans << endl;
    return 0;
}