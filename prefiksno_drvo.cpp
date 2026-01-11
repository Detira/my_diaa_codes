#include <iostream>
#include <vector>

namespace my{
    class Trie{
        public:
            Trie(): niz(26){}
            ~Trie(){}
            
            bool find(std::string_view s){
                if(!s.empty()){
                    if(nullptr != niz[s[0]-'a']){
                        return niz[s[0]-'a']->find(s.substr(1));
                    } else {
                        return false;
                    }
                } else {
                    return indikator;
                }
            }
            
            void add(std::string_view s){
                if(!s.empty()){
                    if(nullptr != niz[s[0]-'a']){
                        niz[s[0]-'a']->add(s.substr(1));
                    } else {
                        niz[s[0]-'a'] = new my::Trie();
                        niz[s[0]-'a']->add(s.substr(1));
                    }
                } else {
                    indikator = true;
                }
            }
            
            void remove(std::string_view s){
                if(!s.empty()){
                    if(nullptr != niz[s[0]-'a']){
                        niz[s[0]-'a']->remove(s.substr(1));
                    } else {
                        std::cout << "already not in" << std::endl;
                    }
                } else {
                    indikator = false;
                }
            }
        private:
            std::vector<Trie*> niz;
            bool indikator;
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