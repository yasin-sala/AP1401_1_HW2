#ifndef TRIE_H
#define TRIE_H
#include <functional>
#include <initializer_list>
#include <iostream>
#include <list>
#include <string>
#include <vector>

class Trie {
public:
    class Node {
    public:
        std::vector<Node*> children;
        char data;
        bool is_finished;

        Node(char data, bool is_finished);
    };
    Node* root;

    Trie(); // default constructor
    void insert(std::string);
    void bfs(std::function<void(Node*& node)> func);
    bool search(std::string query);
    ~Trie(); // destructor
    Trie(std::initializer_list<std::string>); // initializer constructor
    Trie(const Trie&); // copy constructor
    Trie(Trie&& trie); // move constructor
    void operator=(const Trie& trie); // operator =
    void operator=(Trie&& trie); // operator = move version

private:
};

#endif // TRIE_H