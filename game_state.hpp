#ifndef GAME_STATE_H
#define GAME_STATE_H
#include <boost/graph/adjacency_matrix.hpp>
#include <vector>
#include <iostream>
#include <string>
typedef boost::adjacency_matrix<boost::undirectedS> Graph;
class Game_State {
public:
    using node_type = int;
    /*Adds edge to the blue edge set, and built edge set*/
    void addBlueEdge(node_type nodeA, node_type nodeB){
        boost::add_edge(nodeA, nodeB, B_);
        boost::add_edge(nodeA, nodeB, Built_Edges_);
    }
    /*Adds edge to the red edge set, and built edge set*/
    void addRedEdge(node_type nodeA, node_type nodeB){
        boost::add_edge(nodeA,nodeB,R_);
        boost::add_edge(nodeA,nodeB,Built_Edges_);
    }
    bool isEdgeBuilt(node_type nodeA, node_type nodeB){
    	std::pair<boost::adjacency_matrix<boost::undirectedS>::edge_descriptor, bool> e = boost::edge(nodeA, nodeB, Built_Edges_);
        return e.second;	 
    }
    /*Returns true on painters turn, false otherwise*/
    bool isPaintersTurn() {return paintersTurn_;}
    /*Returns true on builders turn, false otherwise*/
    bool isBuildersTurn() {return buildersTurn_;}
    /*Swaps the turn of builder and painter*/
    void swapTurn() { paintersTurn_ = !paintersTurn_; buildersTurn_ = !buildersTurn_;}
    /*Recursive DFS function checking for path of size path_length in red set*/
    void DFS_Path(const node_type& start, int path_length, std::vector<bool>& visited, std::vector<node_type>& path,bool &path_found) {
        visited[start] = true;
        path.push_back(start);
  
        if (path.size() == path_length) {
    	      path_found = true;
	      endGameString = "Path Found Along Nodes: ";
	      for (const auto& node : path)
 	          endGameString += std::to_string(node + 1) + " -> ";
              endGameString += " End";
        } else {
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
    /*Function that calls DFS_Path on all nodes since there can be disjoint paths in red set, returns true when path of size path_length is found*/
    bool DFS_Check_Red() {
        std::vector<bool> visited(boost::num_vertices(R_), false);
        std::vector<node_type> path;
        bool path_found = false;

        for (int v = 0; v < boost::num_vertices(R_); ++v) {
            DFS_Path(v, path_length, visited, path,path_found);
        }
        return path_found;
    }
    /*Recursive DFS function checking for cycle of size cycle_length in blue set*/
    void DFS_Cycle(const node_type& start, int cycle_length, std::vector<bool>& visited, std::vector<node_type>& path,bool &cycle_found) {
        visited[start] = true;
        path.push_back(start);

        if (path.size() == cycle_length) {
            auto neighbors = boost::adjacent_vertices(start, B_);
            for (auto it = neighbors.first; it != neighbors.second; ++it) {
            	 const auto& neighbor = *it;
           	    if (neighbor == path[0]) {
           	        cycle_found = true;
			endGameString = "Cycle Found Along Nodes: ";
			for(const auto& node : path)
			    endGameString += std::to_string(node+1) + " -> ";
			endGameString +=std::to_string(path[0]+1);  
            	 }	
            }
        } else if (path.size() < cycle_length) {
            auto neighbors = boost::adjacent_vertices(start, B_);
            for (auto it = neighbors.first; it != neighbors.second; ++it) {
			    	const auto& neighbor = *it;            
               if (!visited[neighbor])
                   DFS_Cycle(neighbor, cycle_length, visited, path,cycle_found);
            }
        }    
        path.pop_back();
        visited[start] = false;
    }
    /*Function that calls DFS_Cycle on all nodes since there can be disjoint edges in blue set, returns true when a cycle of size cycle_length is found*/
    bool DFS_Check_Blue() {
        std::vector<bool> visited(boost::num_vertices(B_), false);
        std::vector<node_type> path;
        bool cycle_found = false;

        for (int v = 0; v < boost::num_vertices(B_); ++v) {
            DFS_Cycle(v, cycle_length, visited, path,cycle_found);
        }
        return cycle_found;
    }
    /*Increments turn*/
    void incrementTurn() { ++turnNumber; }
    /*Returns the current turn number*/
    int getTurnNumber() { return turnNumber;}
    /*Returns a string containing either the path or cycle that caused the game to end*/
    std::string getEndGameString() { return endGameString;}
    /*Sets the number of nodes the path of edges must contain to end the game*/
    void setG1Size(int size){path_length = size + 1;} 
    /*Sets the number of edges the cycle must contain to end the game*/
    void setG2Size(int size){cycle_length = size;}
    /*Resets the state of the game to the intitial values*/
    void resetGameState(){
        paintersTurn_ = false;
	buildersTurn_ = true;
	turnNumber = 1;
	path_length = 0;
	cycle_length = 0;
	B_ = Graph(6);
	R_ = Graph(6);
	Built_Edges_ = Graph(6);
    }
    
private:
    bool paintersTurn_ = false; 
    bool buildersTurn_ = true; //game starts on builders turn
    int turnNumber = 1;
    int path_length;
    int cycle_length;
    Graph R_{6};
    Graph B_{6};
    Graph Built_Edges_{6};
    std::string endGameString; // string that holds which path or cycle caused a loss

};
#endif // GAME_STATE_H
