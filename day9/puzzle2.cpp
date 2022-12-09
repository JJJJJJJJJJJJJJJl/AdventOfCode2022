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

    // conceptually - contains knot 9 visited positions
    set<tuple<int,int>> grid;
    // lets assume they start at (0,0), could be anything pair of natural numbers
    // so both head an tail start at (0,0) thus (0,0) is added to the visited positions
    grid.insert(make_tuple(4, 0));

    // indexes - head = 0,...,knot9 = 9
    vector<tuple<int, int>> cur_knots_pos;
    for(int i=0; i<10; i++){
        cur_knots_pos.push_back(make_tuple(4,0));
    }
    string move;
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
                get<0>(cur_knots_pos[0])--;
            }
            else if(direction == "D"){
                get<0>(cur_knots_pos[0])++;
            }
            else if(direction == "L"){
                get<1>(cur_knots_pos[0])--;
            }
            else{
                get<1>(cur_knots_pos[0])++;
            }

            for(int k=1; k<10; k++){
                tuple<int, int> prev_knot_pos = cur_knots_pos[k-1];
                tuple<int, int> cur_knot_pos = cur_knots_pos[k];
                /* Update tail position */
                // head and tail are in the same position or head is adjacent to tail
                if((get<0>(cur_knot_pos) == get<0>(prev_knot_pos) && get<1>(cur_knot_pos) == get<1>(prev_knot_pos))
                    || is_adjacent(prev_knot_pos, cur_knot_pos)){
                    continue;
                }
                // head and tail are in the same row but different col
                else if(get<0>(cur_knot_pos) == get<0>(prev_knot_pos) && get<1>(cur_knot_pos) != get<1>(prev_knot_pos)){
                    if(get<1>(prev_knot_pos) > get<1>(cur_knot_pos)){
                        get<1>(cur_knots_pos[k])++;
                    }
                    else{
                        get<1>(cur_knots_pos[k])--;
                    }
                }
                // head and tail are in the same col but different row
                else if(get<1>(cur_knot_pos) == get<1>(prev_knot_pos) && get<0>(cur_knot_pos) != get<0>(prev_knot_pos)){
                    if(get<0>(prev_knot_pos) > get<0>(cur_knot_pos)){
                        get<0>(cur_knots_pos[k])++;
                    }
                    else{
                        get<0>(cur_knots_pos[k])--;
                    }
                }
                // tail in different row and column as head so move diagonaly
                else{
                    vector<tuple<int, int>> diagonal_moves;
                    diagonal_moves.push_back(make_tuple(get<0>(cur_knot_pos)-1, get<1>(cur_knot_pos)-1));
                    diagonal_moves.push_back(make_tuple(get<0>(cur_knot_pos)-1, get<1>(cur_knot_pos)+1));
                    diagonal_moves.push_back(make_tuple(get<0>(cur_knot_pos)+1, get<1>(cur_knot_pos)-1));
                    diagonal_moves.push_back(make_tuple(get<0>(cur_knot_pos)+1, get<1>(cur_knot_pos)+1));
                    int min_dist = INT_MAX;
                    int best_move = -1;
                    for(int j=0; j<4; j++){
                        tuple<int, int> cur_diag_move = diagonal_moves[j];
                        // I'll opt by calculating the euclidean distance without square rooting the sum os squares
                        // so there's no floating point operations messing my sanity up :)
                        int cur_diag_move_dist = pow(get<0>(cur_diag_move)-get<0>(prev_knot_pos),2) + pow(get<1>(cur_diag_move)-get<1>(prev_knot_pos),2);
                        if(cur_diag_move_dist < min_dist){
                            min_dist = cur_diag_move_dist;
                            best_move = j;
                        }
                    }
                    get<0>(cur_knots_pos[k]) = get<0>(diagonal_moves[best_move]);
                    get<1>(cur_knots_pos[k]) = get<1>(diagonal_moves[best_move]);
                }
            }

            // add tails new position to grid if not visited yet
            grid.insert(cur_knots_pos[9]);
        }
    }
    ans += grid.size();
    cout << ans << endl;
    return 0;
}