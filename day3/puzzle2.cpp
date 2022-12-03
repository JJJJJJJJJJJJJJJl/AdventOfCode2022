#include "../bits/stdc++.h"
using namespace std;

#define ASCIIREV 32 // Swap uppercase with lowercases characters in ASCII table (eg.: A_index <-> a_index )
#define VOCAB_ZIZE 52

// Get rucksack mistaken items
int group_badge(vector<string> &group_rucksacks){
    int group_badge = 0;
    int * item_occs = (int *)(size_t)malloc(sizeof(int) * VOCAB_ZIZE);
    bool * counted = (bool *)malloc(sizeof(bool) * VOCAB_ZIZE);
    memset(item_occs, 0, sizeof(int) * VOCAB_ZIZE);
    memset(counted, false, sizeof(bool) * VOCAB_ZIZE);
    for(int rucksack_index=0; rucksack_index<3; rucksack_index++){
        int n = group_rucksacks[rucksack_index].length();
        for(int j=0; j<n; j++){
            int item_index = group_rucksacks[rucksack_index][j]-65;
            isupper(group_rucksacks[rucksack_index][j]) ? item_index += ASCIIREV - 6 : item_index -= ASCIIREV;
            if(counted[item_index]) continue;
            item_occs[item_index]++; counted[item_index] = true;
            if(rucksack_index+1 == 3 && item_occs[item_index] == 3){
                group_badge = item_index+1;
                break;
            }
        }
        memset(counted, false, sizeof(bool) * VOCAB_ZIZE);
    }
    free(item_occs);
    free(counted);
    return group_badge;
}

int main(){
    int ans = 0;
    string line;
    int elf_group_elem = 0;
    vector<string> group_rucksacks;
    while (getline(cin, line)){
        group_rucksacks.push_back(line);
        elf_group_elem++;
        if(elf_group_elem == 3){
            ans += group_badge(group_rucksacks);
            group_rucksacks.clear();
            elf_group_elem = 0;
        }
    }
    cout << ans << endl;
    return 0;
}