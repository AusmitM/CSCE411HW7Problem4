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
        vector<Node*> path;
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
    vector<Node*> nodes;
    vector<vector<AJNode*>> AL;
    for(int i =1;i<=totalNodes;i++){
        nodes.push_back(new Node(i, __INT32_MAX__));
        vector<AJNode*> temp;
        AL.push_back(temp);
    }
    while(getline(inputFile,fileLine)){
        stringstream ss(fileLine);
        string token;
        int counter = 0;
        int node1;
        int node2;
        int dist;
        while(getline(ss,token, ' ')){
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
    }

    priority_queue<Node*, vector<Node*>,greater<Node*>> pq; 

    nodes.at(0)->distance = 0;
    pq.push(nodes.at(0));
    while(pq.size()!=0){
        Node* min = pq.top();
        pq.pop();
        for(AJNode* temp: AL.at((min->label)-1)){
            int new_dist = min->distance+temp->edgeWeight;
            int old_dist = nodes.at((temp->label)-1)->distance;
            if(new_dist<old_dist){
                nodes.at((temp->label)-1)->distance=new_dist;
                nodes.at((temp->label)-1)->path = min->path;
                nodes.at((temp->label)-1)->path.push_back(min);
                pq.push(nodes.at((temp->label)-1));
            }
        }
    }

    for(int i =0;i<totalNodes;i++){
        for(int j = 0;j<AL.at(i).size();j++){
            delete AL.at(i).at(j);
        }
    }
    for(Node* temp: nodes){
        if(temp->label == 6||temp->label == 8||temp->label == 9||temp->label == 15||temp->label == 16||temp->label == 22){
            cout<<"Distance from Node 1 to Node "<<to_string(temp->label)<<": "<<to_string(temp->distance)<<endl;
            cout<<"Path:"<<endl;
            for(Node* n:temp->path){
                cout<<"Node " <<to_string(n->label)<<endl;
            }
            cout<<"Node "<<to_string(temp->label)<<endl;
        }
        
    }

    for(Node* temp: nodes){
        delete temp;
    }
    inputFile.close();
}

