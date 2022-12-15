#include "../bits/stdc++.h"
using namespace std;

#define Y 2000000

class SensorData{
    public:
        int x;
        int dist;
};

map<int, vector<SensorData>> jjjjjj_system;
set<int> Y_beacon;

int main(){
    int max_x = INT_MIN;
    int max_y = INT_MIN;
    int min_x = INT_MAX;
    int min_y = INT_MAX;
    string line;
    while(getline(cin, line)){
        stringstream stream(line);
        stream >> line >> line >> line;
        string sensor_sx;
        for(int i=2; line[i]!=','; i++) sensor_sx += line[i];
        stream >> line;
        string sensor_sy;
        for(int i=2; line[i]!=':'; i++) sensor_sy += line[i];
        stream >> line >> line >> line >> line >> line;
        string beacon_sx;
        for(int i=2; line[i]!=','; i++) beacon_sx += line[i];
        stream >> line;
        string beacon_sy;
        for(int i=2; i<line.length(); i++) beacon_sy += line[i];
        int sensor_x = stoi(sensor_sx);
        int sensor_y = stoi(sensor_sy);
        int beacon_x = stoi(beacon_sx);
        int beacon_y = stoi(beacon_sy);
        max_x = max(max(max_x, sensor_x), beacon_x);
        min_x = min(min(min_x, sensor_x), beacon_x);
        max_y = max(max(max_y, sensor_y), beacon_y);
        min_y = min(min(min_y, sensor_y), beacon_y);
        if(beacon_y == Y) Y_beacon.insert(beacon_x);
        SensorData sd;
        sd.x = sensor_x;
        sd.dist = abs(sensor_x-beacon_x) + abs(sensor_y-beacon_y);

        if(jjjjjj_system.find(sensor_y) == jjjjjj_system.end()){
            vector<SensorData> row_y_sensors;
            row_y_sensors.push_back(sd);
            jjjjjj_system[sensor_y] = row_y_sensors;
        }
        else jjjjjj_system[sensor_y].push_back(sd);
    }

    int a_y = Y-1;
    int b_y = Y+1;
    
    set<int> Y_row;

    //above Y row
    while(a_y >= min_y){
        if(jjjjjj_system.find(a_y) != jjjjjj_system.end()){
            int k = 0;
            vector<SensorData> row_y_sensor = jjjjjj_system[a_y];
            int n = row_y_sensor.size();
            for(int i=0; i<n; i++){
                SensorData sensor = row_y_sensor[i];
                if(a_y + sensor.dist >= Y){
                    int l_x = sensor.x-(sensor.dist-(abs(Y-a_y)));
                    int h_x = sensor.x+(sensor.dist-(abs(Y-a_y)));
                    for(int j=l_x; j<=h_x; j++) if(Y_beacon.find(j) == Y_beacon.end()) Y_row.insert(j);
                }
                else k++;
            }
            // stop when all a_y sensors dont reach Y
            if(n == k && n != 0 && k != 0){
                break;  
            }
        }
        a_y--;
    }

    //below Y row
    while(b_y <= max_y){
        if(jjjjjj_system.find(b_y) != jjjjjj_system.end()){
            int k = 0;
            vector<SensorData> row_y_sensor = jjjjjj_system[b_y];
            int n = row_y_sensor.size();
            for(int i=0; i<n; i++){
                SensorData sensor = row_y_sensor[i];
                if(b_y - sensor.dist <= Y){
                    int l_x = sensor.x-(sensor.dist-(abs(Y-b_y)));
                    int h_x = sensor.x+(sensor.dist-(abs(Y-b_y)));
                    for(int j=l_x; j<=h_x; j++) if(Y_beacon.find(j) == Y_beacon.end()) Y_row.insert(j);
                }
                else k++;
            }
            // stop when all b_y sensors dont reach Y
            if(n == k && n != 0 && k != 0){
                break;  
            }
        }
        b_y++;
    }

    cout << Y_row.size() << endl;
    return 0;
}