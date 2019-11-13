#include <map>

using namespace std;
class Trie;

class Node{
private:
    friend class Trie;
    bool state;
    map<char,Node*> children;
public:
    Node();
    Node(bool state);
    ~Node();
};

Node::Node(){
    this->state = false;
}

Node::Node(bool state){
    this->state = state;
}

Node::~Node(){
}
