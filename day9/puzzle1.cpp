#include "../bits/stdc++.h"
using namespace std;

bool is_adjacent(tuple<int,int> head, tuple<int,int> tail){
    bool adjacent = false;
    adjacent |=  abs(get<0>(head)-get<0>(tail)) == 1 && abs(get<1>(head)-get<1>(tail)) == 1;
    adjacent |= abs(get<0>(head)-get<0>(tail)) == 1 && abs(get<1>(head)-get<1>(tail)) == 0;
    adjacent |= abs(get<0>(head)-get<0>(tail)) == 0 && abs(get<1>(head)-get<1>(tail)) == 1;
    return adjacent;
}

int main(){
    int ans = 0;

    // conceptually - contains tails visited positions
    set<tuple<int,int>> grid;
    // lets assume they start at (0,0), could be anything pair of natural numbers
    // so both head an tail start at (0,0) thus (0,0) is added to the visited positions
    grid.insert(make_tuple(0, 0));

    string move;
    tuple<int, int> cur_head_pos = make_tuple(0,0);
    tuple<int, int> cur_tail_pos = make_tuple(0,0);
    while(getline(cin, move)){
        stringstream stream(move);
        string direction;
        stream >> direction;
        string ssteps;
        stream >> ssteps;
        int steps = stoi(ssteps);
        
        for(int i=0; i<steps; i++){
            /* Updating head position given input */
            if(direction == "U"){
                get<0>(cur_head_pos)--;
            }
            else if(direction == "D"){
                get<0>(cur_head_pos)++;
            }
            else if(direction == "L"){
                get<1>(cur_head_pos)--;
            }
            else{
                get<1>(cur_head_pos)++;
            }
            /* Update tail position */
            // head and tail are in the same position or head is adjacent to tail
            if((get<0>(cur_tail_pos) == get<0>(cur_head_pos) && get<1>(cur_tail_pos) == get<1>(cur_head_pos))
                || is_adjacent(cur_head_pos, cur_tail_pos)){
                continue;
            }
            // head and tail are in the same row but different col
            else if(get<0>(cur_tail_pos) == get<0>(cur_head_pos) && get<1>(cur_tail_pos) != get<1>(cur_head_pos)){
                if(get<1>(cur_head_pos) > get<1>(cur_tail_pos)){
                    get<1>(cur_tail_pos)++;
                }
                else{
                    get<1>(cur_tail_pos)--;
                }
            }
            // head and tail are in the same col but different row
            else if(get<1>(cur_tail_pos) == get<1>(cur_head_pos) && get<0>(cur_tail_pos) != get<0>(cur_head_pos)){
                if(get<0>(cur_head_pos) > get<0>(cur_tail_pos)){
                    get<0>(cur_tail_pos)++;
                }
                else{
                    get<0>(cur_tail_pos)--;
                }
            }
            // tail in different row and column as head so move diagonaly
            else{
                vector<tuple<int, int>> diagonal_moves;
                diagonal_moves.push_back(make_tuple(get<0>(cur_tail_pos)-1, get<1>(cur_tail_pos)-1));
                diagonal_moves.push_back(make_tuple(get<0>(cur_tail_pos)-1, get<1>(cur_tail_pos)+1));
                diagonal_moves.push_back(make_tuple(get<0>(cur_tail_pos)+1, get<1>(cur_tail_pos)-1));
                diagonal_moves.push_back(make_tuple(get<0>(cur_tail_pos)+1, get<1>(cur_tail_pos)+1));
                int min_dist = INT_MAX;
                int best_move = -1;
                for(int j=0; j<4; j++){
                    tuple<int, int> cur_diag_move = diagonal_moves[j];
                    // I'll opt by calculating the euclidean distance without square rooting the sum os squares
                    // so there's no floating point operations messing my sanity up :)
                    int cur_diag_move_dist = pow(get<0>(cur_diag_move)-get<0>(cur_head_pos),2) + pow(get<1>(cur_diag_move)-get<1>(cur_head_pos),2);
                    if(cur_diag_move_dist < min_dist){
                        min_dist = cur_diag_move_dist;
                        best_move = j;
                    }
                }
                get<0>(cur_tail_pos) = get<0>(diagonal_moves[best_move]);
                get<1>(cur_tail_pos) = get<1>(diagonal_moves[best_move]);
            }

            // add tails new position to grid if not visited yet
            grid.insert(cur_tail_pos);
        }
    }
    ans += grid.size();
    cout << ans << endl;
    return 0;
}