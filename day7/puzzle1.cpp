#include "../bits/stdc++.h"
using namespace std;

class Directory{
    public:
        string name;
        vector<string> child_dirs;
        long total_size;
};

map<string, Directory> jjjjjj_filesystem;
stack<string> fs_dir_tracker;

// dfs
int propagate(Directory &root){
    vector<string> child_dirs = root.child_dirs;
    for(int i=0; i<child_dirs.size(); i++){
        root.total_size += propagate(jjjjjj_filesystem[child_dirs[i]]);
    }
    jjjjjj_filesystem[root.name] = root;
    return root.total_size;
}

string get_dir_path(string cur_dir){
    string dir_path = "";
    vector<string> path;
    stack<string> temp = fs_dir_tracker;
    while(!temp.empty()){
        path.push_back(temp.top());
        temp.pop();
    }
    if(cur_dir == ""){
        for(int i=path.size()-1; i>-1; i--){
            dir_path += path[i];
            if(path[i] != "/" && i != 0){
                dir_path += "/";
            }
        }
    }
    else{
        for(int i=path.size()-1; i>-1; i--){
            dir_path += path[i];
            if(path[i] != "/"){
                dir_path += "/";
            }
        }
    }
    dir_path += cur_dir;
    return dir_path;
}

int main(){
    
    // reading input & creating filesystem structure
    string line;
    while(getline(cin, line)){
        // command
        if(line[0] == '$'){
            line = line.substr(2,line.length()-1);
            stringstream stream(line);
            string command;
            stream >> command;
            // cd command
            if(command == "cd"){
                string cur_dir;
                stream >> cur_dir;
                if(cur_dir == ".."){
                    fs_dir_tracker.pop();
                }
                else if(cur_dir == "/"){
                    if (jjjjjj_filesystem.find(cur_dir) == jjjjjj_filesystem.end()){
                        Directory d;
                        d.name = cur_dir;
                        d.total_size = 0;
                        jjjjjj_filesystem[d.name] = d;
                    }
                    while(!fs_dir_tracker.empty()){
                        fs_dir_tracker.pop();
                    }
                    fs_dir_tracker.push(cur_dir);
                }
                else{
                    string dir_name = cur_dir;
                    cur_dir = get_dir_path(cur_dir);
                    if (jjjjjj_filesystem.find(cur_dir) == jjjjjj_filesystem.end()){
                        Directory d;
                        d.name = cur_dir;
                        d.total_size = 0;
                        jjjjjj_filesystem[d.name] = d;
                    }
                    fs_dir_tracker.push(dir_name);
                }
            }
        }
        // ls command output
        else{
            string parent_dir = get_dir_path("");
            stringstream stream(line);
            string first;
            stream >> first;
            
            // child directory
            if(first == "dir"){
                string directory_name;
                stream >> directory_name;
                string a = get_dir_path(directory_name);
                jjjjjj_filesystem[parent_dir].child_dirs.push_back(a);
            }
            // file
            else{
                long file_size = stoi(first);
                string file_name; stream >> file_name;
                jjjjjj_filesystem[parent_dir].total_size += file_size;
            }
        }
    }

    // propagating directory sizes upwards in filesystem tree
    propagate(jjjjjj_filesystem["/"]);

    int ans = 0;
    for(auto e = jjjjjj_filesystem.begin(); e != jjjjjj_filesystem.end(); e++){
        Directory d = e->second;
        d.total_size <= 100000 ? ans += d.total_size : NULL; 
    }
    cout << ans << endl;
    return 0;
}