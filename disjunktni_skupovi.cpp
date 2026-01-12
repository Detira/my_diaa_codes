#include <iostream>
#include <vector>

namespace my{
    class UnionFind{
        public:
            UnionFind(int x): parents(x), sizes(x, 1){
                for(int i = 0; i < x; i++)
                    parents[i] = i;
            }
            ~UnionFind(){}
            
            int f(int x){
                while(x != parents[x])
                    x = (parents[x] = parents[parents[x]]);
                return x;
            }
            
            void u(int x, int y){
                while(x != parents[x])
                    x = (parents[x] = parents[parents[x]]);
                while(y != parents[y])
                    y = (parents[y] = parents[parents[y]]);
                
                if(sizes[x] > sizes[y]){
                    parents[y] = x;
                    sizes[x] += sizes[y];
                } else {
                    parents[x] = y;
                    sizes[y] += sizes[x];
                }
            }
        private:
            std::vector<int> parents;
            std::vector<int> sizes;
    };
}

int main(){
    
    my::UnionFind uf(10);
    
    uf.u(0, 1);
    uf.u(2, 3);
    uf.u(6, 8);
    uf.u(0, 3);
    uf.u(8, 7);
    uf.u(9, 5);
    
    for(int i = 0; i < 10; i++)
        std::cout << uf.f(i) << " ";
    std::cout << std::endl;
    
    return 0;
}