//
//  main.cpp
//  hw8
//
//  Created by Tanya Sharma on 4/27/19.
//  Copyright © 2019 Tanya Sharma. All rights reserved.
//

#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <list>
#include <limits>
#include <set>
#include <utility>
#include <queue>
#include <algorithm>
#include <iterator>
#include "ArgumentManager.h"



using namespace std;

typedef int ver_t;
typedef double weight_t;

const weight_t max_weight = numeric_limits<double>::infinity();

struct neighbor {
    ver_t target;
    weight_t weight;
    neighbor(ver_t arg_target, weight_t arg_weight)
    : target(arg_target), weight(arg_weight) { }
};

typedef vector<vector<neighbor> > adj_list_t;


void DijkstraComputePaths(ver_t source,
                          const adj_list_t &adjacency_list,
                          vector<weight_t> &min_distance,
                          vector<ver_t> &previous)
{
    int n = adjacency_list.size();
    min_distance.clear();
    min_distance.resize(n, max_weight);
    min_distance[source] = 0;
    previous.clear();
    previous.resize(n, -1);
    set<pair<weight_t, ver_t> > vertex_queue;
    vertex_queue.insert(make_pair(min_distance[source], source));
    
    while (!vertex_queue.empty())
    {
        weight_t dist = vertex_queue.begin()->first;
        ver_t u = vertex_queue.begin()->second;
        vertex_queue.erase(vertex_queue.begin());
        
        // Visit each edge exiting u
        const vector<neighbor> &neighbors = adjacency_list[u];
        for (vector<neighbor>::const_iterator neighbor_iter = neighbors.begin();
             neighbor_iter != neighbors.end();
             neighbor_iter++)
        {
            ver_t v = neighbor_iter->target;
            weight_t weight = neighbor_iter->weight;
            weight_t distance_through_u = dist + weight;
            if (distance_through_u < min_distance[v]) {
                vertex_queue.erase(make_pair(min_distance[v], v));
                
                min_distance[v] = distance_through_u;
                previous[v] = u;
                vertex_queue.insert(make_pair(min_distance[v], v));
                
            }
            
        }
    }
}


list<ver_t> DijkstraGetShortestPathTo(ver_t vertex, const vector<ver_t> &previous)
{
    list<ver_t> path;
    for ( ; vertex != -1; vertex = previous[vertex])
        path.push_front(vertex);
    return path;
}

int main(int argc, char *argv[]){
    ArgumentManager am(argc, argv);
    string input = am.get("input");
    string output = am.get("output");
    const string path = am.get("path");
    
    ifstream inFile(input);
    ifstream pathFile(path);
    ofstream outputFile(output);
    
    
    
    if (inFile.is_open())
        cout << "FILE OPEN" << endl;
    if (pathFile.is_open())
        cout << "PATH FILE OPEN" << endl;
   
    
    if (inFile.fail() || pathFile.fail())
    {
        cout << "FILE NOT OPEN" << endl;
    }
    
    string line = "";
    string pathline = "";
    
    bool empty = false;
    bool pathEmpty = false;
    
    int graphsize;
    graphsize = -1;
    int start,end;
    double weight;
    
    if (inFile.peek() == ifstream::traits_type::eof()){
        empty = true;
    }
    
    if (pathFile.peek() == ifstream::traits_type::eof()){
        pathEmpty = true;
    }
    
    if(!empty){
        while(inFile >> start){
            if(start > graphsize){
                graphsize = start;
            }
            inFile >>end;
            if(end > graphsize){
                graphsize = end;
            }
            inFile >> weight;
        }
    }
    
    inFile.clear();
    inFile.seekg(0, ios::beg);
    
    adj_list_t adjacency_list(graphsize + 1);
    if(!empty){
        while(inFile >> start){
            inFile >> end;
            inFile >> weight;
            adjacency_list[start].push_back(neighbor(end, weight));
        }
    }
    
    vector<weight_t> minimumDistance;
    vector<ver_t> previous;
    
    int pathStart;
    pathStart = 0;
    
    int pathEnd;
    pathEnd=0;
    
    if(!pathEmpty){
        while(pathFile >> pathStart){
            pathFile >>pathEnd;
        }
    }
    
    if(empty && !pathEmpty){
        cout<< "Infinite" <<endl;
        outputFile << "Infinite"<<endl;
    }
    if(!empty && pathEmpty){
        cout<< "Infinite" <<endl;
        outputFile << "Infinite"<<endl;
    }
    
    if(!empty){
        if(pathStart < graphsize + 1){
            DijkstraComputePaths(pathStart, adjacency_list, minimumDistance, previous);
        }
        else{
            cout<< "Infinite" <<endl;
            outputFile<< "Infinite" <<endl;
            exit(1);
            
        }
        if(pathEnd < graphsize + 1){
            if(minimumDistance[pathEnd] == max_weight){
                cout<< "Infinite" <<endl;
                outputFile<< "Infinite" <<endl;
                
            }
            
            else{
                cout<< setprecision(1) << fixed << minimumDistance[pathEnd]<<endl;
                outputFile << setprecision(1) << fixed << minimumDistance[pathEnd]<<endl;
            }
        }
        else{
            cout<< "Infinite" <<endl;
            outputFile<< "Infinite" <<endl;
            exit(1);
            
        }
    }

    system("pause");
    
    return 0;
}
