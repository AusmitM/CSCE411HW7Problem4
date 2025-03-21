#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;



int main(){
    ifstream inputFile;
    inputFile.open("escapeMap.txt");
    string fileLine;
    int totalNodes = 22;
    int graph [totalNodes][totalNodes];
    for(int i =0;i<totalNodes;i++){
        for(int j = 0;j<totalNodes;j++){
            graph[i][j] = 0;
        }
    }
    //get data from input file
    while(getline(inputFile,fileLine)){
        stringstream ss(fileLine);
        string token;
        int counter = 0;
        int node1;
        int node2;
        int dist;
        while(getline(ss,token, ' ')){
            // cout<<token<<endl;
            if(counter==0){
                node1 = stoi(token);
            }else if(counter==1){
                node2 = stoi(token);
            }else if(counter==2){
                dist = stoi(token);
            }
            counter++;
        }
        graph[node1-1][node2-1] = dist;
        graph[node2-1][node1-1] = dist;
    }

    // for(int i =0;i<totalNodes;i++){
    //     for(int j = 0;j<totalNodes;j++){
    //         cout<<graph[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    // inputFile.close();
    

}

