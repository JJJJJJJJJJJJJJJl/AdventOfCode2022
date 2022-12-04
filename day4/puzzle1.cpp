#include "../bits/stdc++.h"
using namespace std;

tuple<int,int> process_elf_range_assignment(string range_assignment){
    tuple<int,int> elf_range_assignment = make_tuple(-1, -1);
    char range_delim = '-';
    int n = range_assignment.length();
    string cur_range_value;
    for(int i=0; i<n; i++){
        char cur_c = range_assignment[i];
        if(cur_c == range_delim){
            get<0>(elf_range_assignment) = stoi(cur_range_value);
            cur_range_value = "";
            continue;
        }
        cur_range_value += cur_c;
    }
    get<1>(elf_range_assignment) = stoi(cur_range_value);
    return elf_range_assignment;
}

vector<int> process_pair_assignment(string pair_assignment){
    char pair_delim = ',';
    bool seen_pair_delim = false;
    int n = pair_assignment.length();
    string first_elf_assignment;
    string second_elf_assignment;
    for(int i=0; i<n; i++){
        char cur_c = pair_assignment[i];
        if(cur_c == pair_delim){
            seen_pair_delim = true;
            continue;
        }
        !seen_pair_delim ? first_elf_assignment += cur_c : second_elf_assignment += cur_c;
    }
    /* 
        pair_assignment_ranges <- [a, b, c, d], where 'a' and 'b' represent the sections range assigned to the first elf, 
        while 'c' and 'd' mean the same for the second elf.
     */
    vector<int> pair_assignment_ranges;
    tuple<int,int> first_elf_processed_range = process_elf_range_assignment(first_elf_assignment);
    pair_assignment_ranges.push_back(get<0>(first_elf_processed_range));
    pair_assignment_ranges.push_back(get<1>(first_elf_processed_range));
    tuple<int,int> second_elf_processed_range = process_elf_range_assignment(second_elf_assignment);
    pair_assignment_ranges.push_back(get<0>(second_elf_processed_range));
    pair_assignment_ranges.push_back(get<1>(second_elf_processed_range));
    return pair_assignment_ranges;
}

bool fully_overlapping(string pair_assignment){
    vector<int> pair_assignment_ranges = process_pair_assignment(pair_assignment);
    if(
    (pair_assignment_ranges[0] <= pair_assignment_ranges[2] 
        && pair_assignment_ranges[1] >= pair_assignment_ranges[3])
        || 
    (pair_assignment_ranges[2] <= pair_assignment_ranges[0]
        && pair_assignment_ranges[3] >= pair_assignment_ranges[1])){
        return true;
    }
    return false;
}

int main(){
    int ans = 0;
    string pair_assignment;
    while(getline(cin, pair_assignment)){
        fully_overlapping(pair_assignment) ? ans++ : NULL;
    }
    cout << ans << endl;
    return 0;
}