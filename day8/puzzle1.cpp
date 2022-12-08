#include "../bits/stdc++.h"
using namespace std;

int main(){
    string tree_row;
    vector<vector<int>> grid;
    while(getline(cin, tree_row)){
        vector<int> row;
        int n = tree_row.length();
        for(int i=0; i<n; i++){
            row.push_back(tree_row[i]-'0');
        }
        grid.push_back(row);
    }

    int N = grid.size();
    bool visible[N][N];
    memset(visible, false, sizeof(visible));
    // corner trees already counted
    int ans = 4;

    // left
    for(int i=1; i<N-1; i++){
        int cur_max = INT_MIN;
        for(int j=0; j<N; j++){
            if(grid[i][j] > cur_max && !visible[i][j]){
                visible[i][j] = true;
                ans++;
            }
            cur_max = max(cur_max, grid[i][j]);
        }
    }

    // right
    for(int i=1; i<N-1; i++){
        int cur_max = INT_MIN;
        for(int j=N-1; j>-1; j--){
            if(grid[i][j] > cur_max && !visible[i][j]){
                visible[i][j] = true;
                ans++;
            }
            cur_max = max(cur_max, grid[i][j]);
        }
    }

    // top
    for(int i=1; i<N-1; i++){
        int cur_max = INT_MIN;
        for(int j=0; j<N; j++){
            if(grid[j][i] > cur_max && !visible[j][i]){
                visible[j][i] = true;
                ans++;
            }
            cur_max = max(cur_max, grid[j][i]);
        }
    }

    // bottom
    for(int i=1; i<N-1; i++){
        int cur_max = INT_MIN;
        for(int j=N-1; j>-1; j--){
            if(grid[j][i] > cur_max && !visible[j][i]){
                visible[j][i] = true;
                ans++;
            }
            cur_max = max(cur_max, grid[j][i]);
        }
    }

    cout << ans << endl;
    return 0;
}