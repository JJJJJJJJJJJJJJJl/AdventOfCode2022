#include "../bits/stdc++.h"
using namespace std;

#define N 1000
char grid[N][N];

int main(){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            grid[i][j] = '.';
        }
    }
    int max_x = INT_MIN;
    int max_y = INT_MIN;
    int min_x = INT_MAX;
    int min_y = INT_MAX;
    string line;
    while(getline(cin, line)){
        stringstream stream(line);
        int k = 1;
        string p;
        tuple<int,int> last_rock;
        bool lr = false;
        while(stream >> p){
            if(k % 2 != 0){
                string sx;
                string sy;
                int i=0;
                while(p[i] != ',') sx += p[i++];
                while(i < p.length()){
                    if(p[i] != ',') sy += p[i];
                    i++;
                }
                int x = stoi(sx);
                int y = stoi(sy);
                if(lr){
                    if(x != get<0>(last_rock)){
                        if(x < get<0>(last_rock)){
                            for(int j=x; j<=get<0>(last_rock); j++){
                                grid[y][j] = '#';
                            }
                        }
                        else{
                            for(int j=get<0>(last_rock); j<=x; j++){
                                grid[y][j] = '#';
                            }
                        }
                    }
                    else{
                        if(y < get<1>(last_rock)){
                            for(int j=y; j<=get<1>(last_rock); j++){
                                grid[j][x] = '#';
                            }
                        }
                        else{
                            for(int j=get<1>(last_rock); j<=y; j++){
                                grid[j][x] = '#';
                            }
                        }
                    }
                }
                last_rock = make_tuple(x, y);
                lr = true;
                max_x = max(max_x, x);
                min_x = min(min_x, x);
                max_y = max(max_y, y);
                min_y = min(min_y, y);
            }
            k++;
        }
    }

    max_y += 2;

    for(int i=0; i<N; i++){
        grid[max_y][i] = '#';
    }
    
    /* for(int i=0; i<=max_y; i++){
        for(int j=min_x-5; j<=max_x+5; j++){
            cout << grid[i][j];
        }
        cout << endl;
    } */

    int ans = 0;
    tuple<int,int> sand_start = make_tuple(0, 500);
    bool voided = false;
    while(!voided){
        tuple<int,int> sand_grain_pos = sand_start;
        while(1){
            if(grid[get<0>(sand_grain_pos)+1][get<1>(sand_grain_pos)] == '.'){
                get<0>(sand_grain_pos)++;
            }
            else if(grid[get<0>(sand_grain_pos)+1][get<1>(sand_grain_pos)-1] == '.'){
                get<0>(sand_grain_pos)++;
                get<1>(sand_grain_pos)--;
            }
            else if(grid[get<0>(sand_grain_pos)+1][get<1>(sand_grain_pos)+1] == '.'){
                get<0>(sand_grain_pos)++;
                get<1>(sand_grain_pos)++;
            }
            else{
                ans++;
                grid[get<0>(sand_grain_pos)][get<1>(sand_grain_pos)] = 'o';
                if(get<0>(sand_grain_pos) == 0 && get<1>(sand_grain_pos) == 500) voided = true;
                break;
            }
        }
    }

    /* for(int i=0; i<=max_y; i++){
        for(int j=min_x-5; j<=max_x+8; j++){
            cout << grid[i][j];
        }
        cout << endl;
    } */

    cout << ans << endl;
    return 0;
}