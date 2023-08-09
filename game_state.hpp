#ifndef GAME_STATE_H
#define GAME_STATE_H
#include <boost/graph/adjacency_matrix.hpp>
#include <vector>
#include <iostream>
typedef boost::adjacency_matrix<boost::undirectedS> Graph;
class Game_State {
public:
    using node_type = int;
    
    void addBlueEdge(node_type nodeA, node_type nodeB){
        boost::add_edge(nodeA, nodeB, B_);
        boost::add_edge(nodeA, nodeB, Built_Edges_);
    }
    void addRedEdge(node_type nodeA, node_type nodeB){
        boost::add_edge(nodeA,nodeB,R_);
        boost::add_edge(nodeA,nodeB,Built_Edges_);
    }
    bool isPaintersTurn() {return paintersTurn_;}
    bool isBuildersTurn() {return buildersTurn_;}
    void swapTurn() { paintersTurn_ = !paintersTurn_; buildersTurn_ = !buildersTurn_; }
    
    void DFS_Path(const node_type& start, int path_length, std::vector<bool>& visited, std::vector<node_type>& path,bool &path_found) {
        visited[start] = true;
        path.push_back(start);

    
        if (path.size() == path_length) {
    	      path_found = true;
            for (const auto& node : path)
                std::cout << node << ' ';
            //std::cout << '\n';
            //std::cout<<"PATH"<<"\n";
        } else {
            // If not found, continue 
            auto neighbors = boost::adjacent_vertices(start, R_);
            for (auto it = neighbors.first; it != neighbors.second; ++it) {
		const auto& neighbor = *it;            
                if (!visited[neighbor])
                    DFS_Path(neighbor, path_length, visited, path,path_found);
            }
        }
        path.pop_back();
        visited[start] = false;
    }

    bool DFS_Check_Red() {
        std::vector<bool> visited(boost::num_vertices(R_), false);
        std::vector<node_type> path;
        bool path_found = false;

        for (int v = 0; v < boost::num_vertices(R_); ++v) {
            DFS_Path(v, path_length, visited, path,path_found);
        }
        return path_found;
    }

    void setG1Size(int size){path_length = size;}
    //void setG2Size(int size){cycle_length = size;}
    
private:
    bool paintersTurn_ = false; //starts false
    bool buildersTurn_ = true; //game starts on builders turn
    int turnNumber = 1;
    int path_length;
    int cycle_length;
    Graph R_{6};
    Graph B_{6};
    Graph Built_Edges_{6};

};
#endif // GAME_STATE_H
