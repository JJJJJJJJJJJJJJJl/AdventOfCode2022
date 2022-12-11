#include "../bits/stdc++.h"
using namespace std;

#define MAX_ROUNDS 10000

class Monkey{
    public:
        int id;
        vector<int> items;
        tuple<string, string> op;
        tuple<int, tuple<int,int>> test;
};

int gcd(int a, int b){
    for(;;){
        if(a == 0) return b;
        b %= a;
        if(b == 0) return a;
        a %= b;
    }
}

int lcm(int a, int b){
    int temp = gcd(a, b);
    return temp ? (a / temp * b) : 0;
}

int main(){
    vector<Monkey> monkeys;
    vector<int> div_tests;
    string line;
    int k = 0;
    int cur_monkey_id = 0;
    Monkey m;
    while(getline(cin, line)){
        stringstream stream(line);
        // monkey id
        if(k == 0){
            m.id = cur_monkey_id++;
        }
        // monkey items
        else if(k == 1){
            string consume;
            stream >> consume; stream >> consume;
            while(stream >> consume){
                if(consume[consume.length()-1] == ','){
                    consume = consume.substr(0,consume.length()-1);
                }
                m.items.push_back(stoi(consume));
            }
        }
        // monkey op
        else if(k == 2){
            string consume;
            stream >> consume; stream >> consume;
            stream >> consume; stream >> consume;
            string oprt; stream >> oprt;
            string value; stream >> value;
            m.op = make_tuple(oprt, value);
        }
        else if(k == 3){
            // monkey test statement
            string consume;
            stream >> consume; stream >> consume;
            stream >> consume;
            string sdiv; stream >> sdiv;
            int div = stoi(sdiv);
            div_tests.push_back(div);

            // monkey test true
            getline(cin, line);
            stringstream streamtrue(line);
            streamtrue >> consume; streamtrue >> consume;
            streamtrue >> consume; streamtrue >> consume;
            streamtrue >> consume;
            string strue; streamtrue >> strue;
            int true_monkey_id = stoi(strue);
            k++;

            // monkey test false
            getline(cin, line);
            stringstream streamfalse(line);
            streamfalse >> consume; streamfalse >> consume;
            streamfalse >> consume; streamfalse >> consume;
            streamfalse >> consume;
            string sfalse; streamfalse >> sfalse;
            int false_monkey_id = stoi(sfalse);
            k++;

            m.test = make_tuple(div, make_tuple(true_monkey_id, false_monkey_id));
        }
        k++;
        if(k == 7){
            monkeys.push_back(m);
            m.items.clear();
            k = 0;
        }
    }
    monkeys.push_back(m);
    m.items.clear();

    int keep_worry_good = 1;
    for(int i=0; i<div_tests.size(); i++){
        keep_worry_good *= div_tests[i];
    }

    int round = 1;
    int n = monkeys.size();
    int inspections[n];
    memset(inspections, 0, sizeof(inspections));
    while(round < MAX_ROUNDS+1){
        for(int i=0; i<n; i++){
            int items_n = monkeys[i].items.size();
            if(items_n == 0) continue;
            inspections[i] += items_n;
            long long worry_level;
            for(int j=0; j<items_n; j++){
                int item = monkeys[i].items[j];
                worry_level = item;
                if(get<0>(monkeys[i].op) == "*"){
                    if(get<1>(monkeys[i].op) == "old"){
                        worry_level *= worry_level;
                    }
                    else{
                        worry_level *= stoi(get<1>(monkeys[i].op));
                    }
                }
                else{
                    if(get<1>(monkeys[i].op) == "old"){
                        worry_level += worry_level;
                    }
                    else{
                        worry_level += stoi(get<1>(monkeys[i].op));
                    }
                }
                worry_level %= keep_worry_good;
                if(worry_level % get<0>(monkeys[i].test) == 0){
                    monkeys[get<0>(get<1>(monkeys[i].test))].items.push_back(worry_level);
                }
                else{
                    monkeys[get<1>(get<1>(monkeys[i].test))].items.push_back(worry_level);
                }
            }
            monkeys[i].items.clear();
        }
        round++;
    }
    sort(inspections, inspections+n);
    cout << (long long)(inspections[n-1]*inspections[n-2]) << endl;
    return 0;
}