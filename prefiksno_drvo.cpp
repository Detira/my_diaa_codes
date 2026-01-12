#include <iostream>
#include <vector>

namespace my{
    class Trie{
        public:
            Trie(): pointers(26){}
            ~Trie(){}
            
            bool find(std::string_view s){
                if(!s.empty()){
                    if(nullptr != pointers[s[0]-'a']){
                        return pointers[s[0]-'a']->find(s.substr(1));
                    } else {
                        return false;
                    }
                } else {
                    return indicator;
                }
            }
            
            void add(std::string_view s){
                if(!s.empty()){
                    if(nullptr != pointers[s[0]-'a']){
                        pointers[s[0]-'a']->add(s.substr(1));
                    } else {
                        pointers[s[0]-'a'] = new my::Trie();
                        pointers[s[0]-'a']->add(s.substr(1));
                    }
                } else {
                    indicator = true;
                }
            }
            
            void remove(std::string_view s){
                if(!s.empty()){
                    if(nullptr != pointers[s[0]-'a']){
                        pointers[s[0]-'a']->remove(s.substr(1));
                    } else {
                        std::cout << "already not in" << std::endl;
                    }
                } else {
                    indicator = false;
                }
            }
        private:
            std::vector<Trie*> pointers;
            bool indicator;
    };
}

int main(){
    
    my::Trie trie;
    trie.add("milos");
    trie.add("tanja");
    trie.add("bojan");
    trie.add("milka");
    trie.add("milbona");
    trie.add("tanjir");
    trie.add("bojana");
    trie.add("doktor");
    
    trie.remove("doktor");
    trie.remove("sheldon");
    
    std::cout << trie.find("milos") << std::endl;
    std::cout << trie.find("milbona") << std::endl;
    std::cout << trie.find("milka") << std::endl;
    std::cout << trie.find("doktor") << std::endl;
    std::cout << trie.find("tanja") << std::endl;
    std::cout << trie.find("milosa") << std::endl;
    std::cout << trie.find("bojan") << std::endl;
    std::cout << trie.find("bojana") << std::endl;
    
    return 0;
}