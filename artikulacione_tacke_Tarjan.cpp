#include <iostream>
#include <vector>
#include <stack>
#include <tuple>

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
            
            void find_articulation_points(){
                std::vector<bool> visited(neighbours.size());
                std::vector<int> pre(neighbours.size());
                std::vector<int> lowlink(neighbours.size());
                std::vector<bool> articulation_points(neighbours.size());
                std::vector<int> number_of_children(neighbours.size());
                
                int pre_counter = 0;
                
                std::stack<std::tuple<int, bool, int>> s;
                for(int i = neighbours.size() - 1; i>=0; i--)
                    s.emplace(i, false, i);
                
                while(!s.empty()){
                    int v = std::get<0>(s.top());
                    bool backtracking = std::get<1>(s.top());
                    int parent = std::get<2>(s.top());
                    s.pop();
                    
                    if(visited[v]){
                        if(backtracking){
                            // output processing/on completion START
                            //std::cout << "Leaving (Backtracking): " << v << std::endl;
                            // updating lowlink (recursion)
                            if(lowlink[v] < lowlink[parent]){
                                lowlink[parent] = lowlink[v];
                                //std::cout << "lowlink[" << parent << "] = lowlink[" << v << "]; (= " << lowlink[v] << ")" << std::endl;
                            }
                            // articulation points logic START
                            number_of_children[parent]++;
                            if(lowlink[v] >= pre[parent])
                                articulation_points[parent] = true;
                            if((v == parent) && (number_of_children[v] < (2+1)))
                            // +1 cuz I count root as it's own child
                                articulation_points[v] = false;
                            // articulation points logic END
                            // output processing/on completion END
                        } else {
                            // revisting START
                            //std::cout << "Revisiting: " << v << std::endl;
                            // updating lowlink (direct/return branch)
                            if(pre[v] < lowlink[parent]){
                                lowlink[parent] = pre[v];
                                //std::cout << "lowlink[" << parent << "] = lowlink[" << v << "]; (= " << lowlink[v] << ")" << std::endl;
                            }
                            // revisiting END
                        }
                    } else {
                        visited[v] = true;
                        // input processing/on discovery START
                        //std::cout << "Entering: " << v << std::endl;
                        // initialising lowlink
                        lowlink[v] = (pre[v] = pre_counter++);
                        //std::cout << "lowlink[" << v << "] = pre[" << v << "]; (= " << lowlink[v] << ")" << std::endl;
                        // input processing/on discovery END
                        s.emplace(v, true, parent);
                        for(auto it = neighbours[v].rbegin(); it != neighbours[v].rend(); ++it)
                            if(*it != parent)   // don't wanna inverse dfs tree branch
                                s.emplace(*it, false, v);
                    }
                }
                /*
                std::cout << "lowlink: ";
                std::vector<int> inverted_pre(pre.size());
                for(int i=0; i<pre.size(); i++)
                    inverted_pre[pre[i]] = i;
                for(int ll : lowlink)
                    std::cout << inverted_pre[ll] << " ";
                std::cout << std::endl;
                */
                std::cout << "articulation points: ";
                for(int i=0; i<articulation_points.size(); i++)
                    if(articulation_points[i])
                        std::cout << i << " ";
                std::cout << std::endl;
            }
        
        private:
            bool directed = false;
            std::vector<std::vector<int>> neighbours;
    };
}

int main(){
    
    my::Graph graf(true);
    
    for(int i=0; i<16; i++)
        graf.add_vertex();
    
    graf.add_edge(0, 1);
    graf.add_edge(0, 5);
    graf.add_edge(1, 0);
    graf.add_edge(1, 6);
    graf.add_edge(2, 3);
    graf.add_edge(2, 6);
    graf.add_edge(2, 7);
    graf.add_edge(3, 2);
    graf.add_edge(4, 5);
    graf.add_edge(5, 0);
    graf.add_edge(5, 4);
    graf.add_edge(5, 6);
    graf.add_edge(5, 10);
    graf.add_edge(6, 1);
    graf.add_edge(6, 2);
    graf.add_edge(6, 5);
    graf.add_edge(6, 7);
    graf.add_edge(6, 9);
    graf.add_edge(7, 2);
    graf.add_edge(7, 6);
    graf.add_edge(8, 9);
    graf.add_edge(8, 12);
    graf.add_edge(8, 13);
    graf.add_edge(9, 6);
    graf.add_edge(9, 8);
    graf.add_edge(9, 12);
    graf.add_edge(9, 13);
    graf.add_edge(10, 5);
    graf.add_edge(10, 11);
    graf.add_edge(10, 15);
    graf.add_edge(11, 10);
    graf.add_edge(12, 8);
    graf.add_edge(12, 9);
    graf.add_edge(13, 8);
    graf.add_edge(13, 9);
    graf.add_edge(13, 14);
    graf.add_edge(14, 13);
    graf.add_edge(15, 10);
    
    graf.find_articulation_points();
    
    return 0;
}