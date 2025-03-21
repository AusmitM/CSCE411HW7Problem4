#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
using namespace std;


class Node{
    public:
        int label;
        int distance;
    Node(int lab, int dist){
        label = lab;
        distance = dist;
    }
    bool operator<(const Node& n){
        return distance<n.distance;
    }
};

struct CloserNode{
    bool operator()(const Node&n1, const Node& n2)const{
        return n1.distance<n2.distance;
    }
};

class AJNode{
    public:
        int label;
        int edgeWeight;
    AJNode(int lab, int weight){
        label = lab;
        edgeWeight = weight;
    }
};

int main(){
    ifstream inputFile;
    inputFile.open("escapeMap.txt");
    string fileLine;
    int totalNodes = 22;
    // int graph [totalNodes][totalNodes];
    // for(int i =0;i<totalNodes;i++){
    //     for(int j = 0;j<totalNodes;j++){
    //         graph[i][j] = 0;
    //     }
    // }
    vector<Node*> nodes;
    vector<vector<AJNode*>> AL;
    for(int i =1;i<=totalNodes;i++){
        nodes.push_back(new Node(i, __INT32_MAX__));
        vector<AJNode*> temp;
        AL.push_back(temp);
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
        AL.at(node1-1).push_back(new AJNode(node2, dist));
        AL.at(node2-1).push_back(new AJNode(node1, dist));

        // graph[node1-1][node2-1] = dist;
        // graph[node2-1][node1-1] = dist;
    }

    // for(int i =0;i<totalNodes;i++){
    //     for(int j = 0;j<totalNodes;j++){
    //         cout<<graph[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    
    // for(int i =0;i<totalNodes;i++){
    //     for(int j = 0;j<AL.at(i).size();j++){
    //         cout<<AL.at(i).at(j)->label<<" "<<AL.at(i).at(j)->edgeWeight<<" | ";
    //     }
    //     cout<<endl;
        
    // }

    priority_queue<Node*, vector<Node*>,greater<Node*>> pq; 
    // for(int i =1;i<=totalNodes;i++){
    //     pq.push(nodes.at(i-1));
    // }
    //setting source node
    nodes.at(0)->distance = 0;
    pq.push(nodes.at(0));
    while(pq.size()!=0){
        Node* min = pq.top();
        pq.pop();
        // cout<<to_string(min->distance)<<" "<<to_string(nodes.at(1)->distance)<<endl;
        // cout<<"Node "<<min->label<<": "<<min->distance<<endl;
        for(AJNode* temp: AL.at((min->label)-1)){
        //     // cout<<"AT "<<to_string(temp->label)<<endl;
            int new_dist = min->distance+temp->edgeWeight;
            int old_dist = nodes.at((temp->label)-1)->distance;
            // cout<<"NEW DIST "<<to_string(new_dist)<<endl;
            // cout<<"OLD DIST "<<to_string(old_dist)<<endl;
            if(new_dist<old_dist){
                nodes.at((temp->label)-1)->distance=new_dist;
                pq.push(nodes.at((temp->label)-1));
            }
            // cout<<":::Node "<<nodes.at((temp->label)-1)->label<<": "<<nodes.at((temp->label)-1)->distance<<endl;
        }
        
        // cout<<"TOP:"<<pq.top()->label<<endl;
    }


    
    for(int i =0;i<totalNodes;i++){
        for(int j = 0;j<AL.at(i).size();j++){
            delete AL.at(i).at(j);
        }
    }
    for(Node* temp: nodes){
        cout<<"Node "<<to_string(temp->label)<<"| Dist: "<<to_string(temp->distance)<<endl;
        delete temp;
    }
    inputFile.close();
}

