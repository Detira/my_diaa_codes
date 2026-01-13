#include <iostream>
#include <vector>   // std::vector
#include <bit>  // bit_ceil
#include <algorithm>    // std::ranges::copy

namespace my{
    class SegmentTree{
        public:
            SegmentTree(std::vector<int> v): data(std::bit_ceil(v.size()) << 1), lazy(std::bit_ceil(v.size()) << 1){
                std::ranges::copy(v, data.begin() + (data.size() >> 1));
                for(int i = (data.size() >> 1) - 1; i > 0; i--)
                    data[i] = data[i*2] + data[i*2+1];
            }
            ~SegmentTree(){}
            
            int point_query(int index){
                return range_query(index, index);
            }
            
            int range_query(int range_left, int range_right){
                return range_query_recursive(range_left + (data.size() >> 1), range_right + (data.size() >> 1), 1, data.size() >> 1, data.size() - 1);
            }
            
            void point_update(int index, int operand){
                return range_update(index, index, operand);
            }
            
            void range_update(int range_left, int range_right, int operand){
                range_update_recursive(range_left + (data.size() >> 1), range_right + (data.size() >> 1), operand, 1, data.size() >> 1, data.size() - 1);
            }
           /* 
            void print(){
                for(auto it : data)
                    std::cout << it << " ";
                std::cout << std::endl;
                for(auto it : lazy)
                    std::cout << it << " ";
                std::cout << std::endl;
            }
            */
        private:
            std::vector<int> data;
            std::vector<int> lazy;
            
            int range_query_recursive(int range_left, int range_right, int index, int index_left, int index_right){
                // update start
                data[index] += lazy[index] * (index_right - index_left + 1);
                if(index_left != index_right){
                    lazy[index*2] += lazy[index];
                    lazy[index*2+1] += lazy[index];
                }
                lazy[index] = 0;
                // update end
                if(range_left <= index_left && index_right <= range_right){
                    return data[index];
                } else if(range_right < index_left || range_left > index_right){
                    return 0;
                } else {
                    return range_query_recursive(range_left, range_right, index * 2, index_left, (index_right + index_left) / 2) + range_query_recursive(range_left, range_right, index * 2 + 1, (index_left + index_right) / 2 + 1, index_right);
                }
            }
            
            void range_update_recursive(int range_left, int range_right, int operand, int index, int index_left, int index_right){
                // update start
                data[index] += lazy[index] * (index_right - index_left + 1);
                if(index_left != index_right){
                    lazy[index*2] += lazy[index];
                    lazy[index*2+1] += lazy[index];
                }
                lazy[index] = 0;
                // update end
                if(range_left <= index_left && index_right <= range_right){
                    data[index] += (index_right - index_left + 1) * operand;
                    if(index_left != index_right){
                        lazy[index*2] += operand;
                        lazy[index*2+1] += operand;
                    }
                } else if(range_right < index_left || range_left > index_right){
                    //return;
                } else {
                    range_update_recursive(range_left, range_right, operand, index * 2, index_left, (index_right + index_left) / 2);
                    range_update_recursive(range_left, range_right, operand, index * 2 + 1, (index_left + index_right) / 2 + 1, index_right);
                    data[index] = data[index*2] + data[index*2+1];
                }
            }
    };
}

int main(){
    
    auto st = my::SegmentTree({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13});
    
    //st.print();
    for(int i = 0; i <= 13; i++)
        std::cout << st.point_query(i) << " ";
    std::cout << std::endl;
    
    st.point_update(5, -10);
    //st.print();
    for(int i = 0; i <= 13; i++)
        std::cout << st.point_query(i) << " ";
    std::cout << std::endl;
    
    st.point_update(5, 10);
    //st.print();
    for(int i = 0; i <= 13; i++)
        std::cout << st.point_query(i) << " ";
    std::cout << std::endl;
    
    st.range_update(5, 8, 100);
    //st.print();
    for(int i = 0; i <= 13; i++)
        std::cout << st.point_query(i) << " ";
    std::cout << std::endl;
    
    std::cout << st.range_query(0, 15) << std::endl;
    //st.print();
    for(int i = 0; i <= 13; i++)
        std::cout << st.point_query(i) << " ";
    std::cout << std::endl;
    
    
    return 0;
}