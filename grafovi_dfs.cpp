#include <iostream>
#include <vector>
#include <stack>

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
            
            void dfs(std::vector<int> x){
                std::vector<bool> visited(neighbours.size());
                
                std::stack<std::pair<int, bool>> s;
                for(int i = neighbours.size() - 1; i>=0; i--)
                    s.emplace(i, false);
                for(auto it = x.rbegin(); it != x.rend(); ++it)
                    s.emplace(*it, false);
                
                while(!s.empty()){
                    int v = s.top().first;
                    bool backtracking = s.top().second;
                    s.pop();
                    
                    if(visited[v]){
                        if(backtracking){
                            // output processing/on completion START
                            std::cout << "Leaving (Backtracking): " << v << std::endl;
                            // output processing/on completion END
                        }
                    } else {
                        visited[v] = true;
                        // input processing/on discovery START
                        std::cout << "Entering: " << v << std::endl;
                        // input processing/on discovery END
                        s.emplace(v, true);
                        for(auto it = neighbours[v].rbegin(); it != neighbours[v].rend(); ++it)
                            s.emplace(*it, false);
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
    
    for(int i=0; i<7; i++)
        graf.add_vertex();
    
    graf.add_edge(0, 1);
    graf.add_edge(0, 2);
    graf.add_edge(0, 3);
    graf.add_edge(1, 4);
    graf.add_edge(2, 0);
    graf.add_edge(2, 5);
    graf.add_edge(3, 2);
    graf.add_edge(5, 1);
    graf.add_edge(5, 6);
    graf.add_edge(6, 5);
    
    graf.dfs({1, 6});
    
    return 0;
}