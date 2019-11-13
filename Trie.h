#include <string>
#include <iostream>
#include <stack>
#include "Node.h"

using namespace std;

typedef pair<char,Node*> child;

class Trie{
private:
    Node* root;
    
public:
    Trie();
    ~Trie();

    Node* getRoot(){return root;}

    void insert(string word);
    void deleteWord(string word);
    bool prefix(string word);
    bool search(string word);
    void print();
    void print(Node* node);
};

Trie::Trie(){
    root = new Node();
}

Trie::~Trie(){
}

void Trie::insert(string word){
    Node* cur = root;
    int index = 0;
    while(index < word.size()){
        if(cur->children.count(word[index])){//key found
            cur = cur->children.at(word[index]);
        }
        else{
            //cout<<"Created new node for: "<<word[index]<<"\n";
            cur->children.insert(child(word[index],new Node()));
            cur = cur->children.at(word[index]);
        }
        index++;
    }
    cur->state = true;
}

void Trie::deleteWord(string word){
    Node* cur = root;
    int index = 0;
    stack<Node*> route;
    while(index < word.size()){
        if(cur->children.count(word[index])){//key found
            route.push(cur);
            cur = cur->children.at(word[index]);
        }
        else{
            cout<<"Word not found.\n";
            return;
        }
        index++;
    }

    index--;
    cur->state = false;

    while(!route.empty()){
        if(cur->state == false && cur->children.size() == 0){
            //cout<<"Deleting link to "<<word[index]<<"\n";
            delete cur;
            cur = route.top();
            route.pop();
            cur->children.erase(word[index]);
            index--;
        }
        if(cur->children.size() != 0){
            return;
        }
    }
    
}

bool Trie::prefix(string word){
    Node* cur = root;
    int index = 0;
    while(index < word.size()){
        if(cur->children.count(word[index])){//key found
            cur = cur->children.at(word[index]);
        }
        else{
            return false;
        }
        index++;
    }
    return !cur->state;
}

bool Trie::search(string word){
    Node* cur = root;
    int index = 0;
    while(index < word.size()){
        if(cur->children.count(word[index])){//key found
            cur = cur->children.at(word[index]);
        }
        else{
            return false;
        }
        index++;
    }
    return cur->state;
}

void Trie::print(){
    if(!root){
        cout<<"Empty tree.\n";
        return;
    }
    Node* node = root;
    for(const auto pair: node->children){
        cout<<pair.first<<" ";
    }
    cout<<"\n";
    for(const auto pair: node->children){
        print(node->children.at(pair.first));
    }
}

void Trie::print(Node* node){
    for(const auto pair: node->children){
        cout<<pair.first<<" ";
    }
    cout<<"\n";
    for(const auto pair: node->children){
        print(node->children.at(pair.first));
    }
}