#include "../bits/stdc++.h"
using namespace std;

vector<vector<char>> grid;
vector<vector<int>> visits;
vector<vector<bool>> visited;

void memset_things(){
    for(int i=0; i<grid.size(); i++){
        for(int j=0; j<grid[0].size(); j++){
            visits[i][j] = 0;
            visited[i][j] = false;
        }
    }
    return;
}

void flood_fill(int x, int y){
    visited[x][y] = true;
    int xy_visits = visits[x][y];
    if(x - 1 >= 0 && grid[x-1][y] - grid[x][y] <= 1){
        if(visits[x-1][y] > 0){
            if(xy_visits + 1 < visits[x-1][y]){
                visits[x-1][y] = xy_visits + 1;
                flood_fill(x-1, y);
            }
        }
        else visits[x-1][y] = xy_visits + 1;
        if(!visited[x-1][y]) flood_fill(x-1, y);
    }
    if(x + 1 < grid.size() && grid[x+1][y] - grid[x][y] <= 1) {
        if(visits[x+1][y] > 0){
            if(xy_visits + 1 < visits[x+1][y]){
                visits[x+1][y] = xy_visits + 1;
                flood_fill(x+1, y);
            }
        }
        else visits[x+1][y] = xy_visits + 1;
        if(!visited[x+1][y]) flood_fill(x+1, y);
    }
    if(y - 1 >= 0 && grid[x][y-1] - grid[x][y] <= 1) {
        if(xy_visits + 1 < visits[x][y-1]){
            visits[x][y-1] = xy_visits + 1;
            flood_fill(x, y-1);
        }
        else visits[x][y-1] = xy_visits + 1;
        if(!visited[x][y-1]) flood_fill(x, y-1);
    }
    if(y + 1 < grid[0].size() && grid[x][y+1] - grid[x][y] <= 1) {
        if(xy_visits + 1 < visits[x][y+1]){
            visits[x][y+1] = xy_visits + 1;
            flood_fill(x, y+1);
        }
        else visits[x][y+1] = xy_visits + 1;
        if(!visited[x][y+1]) flood_fill(x, y+1);
    }
    return;
}

int main(){

    string line;
    vector<tuple<int,int>> start;
    tuple<int,int> finish;
    while(getline(cin, line)){
        vector<char> row;
        vector<int> row_visits;
        vector<bool> row_visited;
        int n = line.length();
        for(int i=0; i<n; i++){
            if(line[i] == 'S' || line[i] == 'a'){
                start.push_back(make_tuple(grid.size(), i));
                row.push_back('a');
            }
            else if(line[i] == 'E'){
                get<0>(finish) = grid.size();
                get<1>(finish) = i;
                row.push_back('z');
            }
            else row.push_back(line[i]);
            row_visits.push_back(0);
            row_visited.push_back(false);
        }
        grid.push_back(row);
        visits.push_back(row_visits);
        visited.push_back(row_visited);
    }

    int ans = INT_MAX;
    for(int i=0; i<start.size(); i++){
        flood_fill(get<0>(start[i]), get<1>(start[i]));
        if(visits[get<0>(finish)][get<1>(finish)] >= 26) ans = min(ans, visits[get<0>(finish)][get<1>(finish)]);
        if(ans == 26){
            // because path can get no shorter than this (I think)
            break;
        }
        memset_things();

    }

    cout << ans << endl;
    return 0;
}