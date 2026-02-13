#include <iostream>
#include <vector>
#include <queue>

namespace my{
    class Graph{
        public:
            Graph(bool directed): directed(directed){}
            ~Graph(){}
            
            void add_vertex(){
                neighbours.emplace_back();
            }
            
            void add_edge(int x, int y){
                if(neighbours.size() <= x || neighbours.size() <= y){
                    std::cout << "Provided vertexes don't exist." << std::endl;
                    return;
                }
                
                neighbours[x].emplace_back(y);
                
                if(!directed)
                    neighbours[y].emplace_back(x);
            }
            
            void bfs(std::vector<int> x){
                std::vector<bool> visited(neighbours.size());
                
                std::queue<int> q;
                
                auto t = x.size();
                x.resize(t + neighbours.size());
                for(int i=0; i<neighbours.size(); i++)
                    x[t+i] = i;
                
                t = x.size();
                for(int i = 0; i < t; i++){
                    if(!visited[x[i]])
                        q.emplace(x[i]);
                    while(!q.empty()){
                        int v = q.front();
                        q.pop();
                        
                        if(!visited[v]){
                            visited[v] = true;
                            // processing START
                            std::cout << "Processing: " << v << std::endl;
                            // processing END
                            for(auto it = neighbours[v].begin(); it != neighbours[v].end(); ++it)
                                q.emplace(*it);
                        }
                    }
                }
            }
        
        private:
            bool directed = false;
            std::vector<std::vector<int>> neighbours;
    };
}

int main(){
    
    my::Graph graf(true);
    
    for(int i=0; i<12; i++)
        graf.add_vertex();
    
    graf.add_edge(0, 1);
    graf.add_edge(0, 2);
    graf.add_edge(0, 3);
    graf.add_edge(1, 2);
    graf.add_edge(1, 4);
    graf.add_edge(1, 5);
    graf.add_edge(2, 5);
    graf.add_edge(3, 6);
    graf.add_edge(6, 10);
    graf.add_edge(7, 5);
    graf.add_edge(7, 8);
    graf.add_edge(8, 9);
    graf.add_edge(8, 10);
    graf.add_edge(8, 11);
    graf.add_edge(11, 3);
    graf.add_edge(11, 9);
    
    graf.bfs({1, 7});
    
    return 0;
}