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
    int scores[N][N];
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            scores[i][j] = 1;
        }
    }
    // corner trees already counted
    int ans = INT_MIN;

    // bro fck this im going the stupid way...I'm sure my M1 mac will take care of it xDDD
    for(int i=1; i<N-1; i++){
        for(int j=1; j<N-1; j++){
            // upwards
            int ti = i-1;
            while(ti > -1){
                if(grid[ti][j] >= grid[i][j]){
                    scores[i][j] *= abs(i-ti);
                    break;
                }
                ti--;
            }
            ti++;
            if(ti == 0){
                scores[i][j] *= abs(i-ti);
            }

            // downwards
            ti = i+1;
            while(ti < N){
                if(grid[ti][j] >= grid[i][j]){
                    scores[i][j] *= abs(i-ti);
                    break;
                }
                ti++;
            }
            ti--;
            if(ti == N-1){
                scores[i][j] *= abs(i-ti);
            }

            // leftwards
            int tj = j-1;
            while(tj > -1){
                if(grid[i][tj] >= grid[i][j]){
                    scores[i][j] *= abs(j-tj);
                    break;
                }
                tj--;
            }
            tj++;
            if(tj == 0){
                scores[i][j] *= abs(j-tj);
            }

            // rightwards
            tj = j+1;
            while(tj < N){
                if(grid[i][tj] >= grid[i][j]){
                    scores[i][j] *= abs(j-tj);
                    break;
                }
                tj++;
            }
            tj--;
            if(tj == N-1){
                scores[i][j] *= abs(j-tj);
            }
        }
    }

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            ans = max(ans, scores[i][j]);
        }
    }

    cout << ans << endl;
    return 0;
}