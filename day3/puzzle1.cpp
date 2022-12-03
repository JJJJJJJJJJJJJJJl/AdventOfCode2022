#include "../bits/stdc++.h"
using namespace std;

#define ASCIIREV 32 // Swap uppercase with lowercases characters in ASCII table (eg.: A_index <-> a_index )
#define VOCAB_ZIZE 52

// Get rucksack mistaken items
int rucksack(string rucksack){
    int rucksack_value = 0; // Sum of mistaken items priority value
    bool * item_occs_fhalf = (bool *)(size_t)malloc(sizeof(bool) * VOCAB_ZIZE);
    bool * item_occs_shalf = (bool *)(size_t)malloc(sizeof(bool) * VOCAB_ZIZE);
    bool * counted = (bool *)(size_t)malloc(sizeof(bool) * VOCAB_ZIZE);
    memset(item_occs_fhalf, false, sizeof(bool) * VOCAB_ZIZE);
    memset(item_occs_shalf, false, sizeof(bool) * VOCAB_ZIZE);
    memset(counted, false, sizeof(bool) * VOCAB_ZIZE);
    int n = rucksack.length();
    for(int i=0; i<n; i++){
        int item_index = rucksack[i]-65;
        isupper(rucksack[i]) ? item_index += ASCIIREV - 6 : item_index -= ASCIIREV;
        if(i+1 <= n/2){
            item_occs_fhalf[item_index] = true;
        }
        else{
            item_occs_shalf[item_index] = true;
            if(item_occs_fhalf[item_index] && item_occs_shalf[item_index] && !counted[item_index]){
                rucksack_value += item_index+1;
                counted[item_index] = true;
            }
        }
    }
    free(item_occs_fhalf);
    free(item_occs_shalf);
    free(counted);
    return rucksack_value;
}

int main(){
    int ans = 0;
    string line;
    while (getline(cin, line)){
        ans += rucksack(line);
    }
    cout << ans << endl;
    return 0;
}