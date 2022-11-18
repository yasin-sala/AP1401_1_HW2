#include "trie.h"

Trie::Node::Node(char data, bool is_finished)
{
    this->data = data;
    this->is_finished = is_finished;
}

Trie::Trie()
{
    root = new Node('\0', false);
}
void Trie::insert(std::string str)

{
    Node* father { root };
    for (size_t i { 0 }; i < str.size(); i++) {
        int index { -1 };
        for (size_t j {}; j < father->children.size(); j++) {
            if (father->children[j]->data == str[i]) {
                index = j;
                break;
            }
        }
        if (index == -1) {
            father->children.push_back(new Node { str[i], false });
            father = father->children[father->children.size() - 1];
        } else {
            father = father->children[index];
        }
    }
    father->is_finished = true;
}

void Trie::bfs(std::function<void(Node*& node)> func)
{
    Node* father { root };
    std::vector<Node*> List { father };
    std::vector<Node*>::iterator delt;

    while (List.size() != 0) {
        for (size_t j {}; j < List[0]->children.size(); j++)
            List.push_back(List[0]->children[j]);
        func(List[0]);
        delt = List.begin();
        List.erase(delt);
    }
}

bool Trie::search(std::string query)
{
    Node* father(root);
    int index {};
    for (size_t i {}; i < query.size(); i++) {
        if (index == i) {
            for (size_t j {}; j < father->children.size(); j++) {
                if (father->children[j]->data == query[i]) {
                    father = father->children[j];
                    index++;
                    break;
                }
            }
        }
    }
    if (index == query.size() && father->is_finished == true)
        return true;
    else
        return false;
}

Trie::~Trie()
{
    if (root == nullptr)
        return;
    std::vector<Node*> nodes;
    this->bfs([&nodes](Trie::Node*& node) { nodes.push_back(node); });
    for (const auto& node : nodes)
        delete node;
}

Trie::Trie(std::initializer_list<std::string> str)
    : Trie()
{
    for (auto x : str)
        insert(x);
}

///////////////  we use below func for last 4 unit_test
void add_child(Trie::Node* new_node, Trie::Node* old_node)
{
    for (Trie::Node* old_node_child : old_node->children) {
        Trie::Node* new_node_child = new Trie::Node(old_node_child->data, old_node_child->is_finished);
        new_node->children.push_back(new_node_child);
        add_child(new_node_child, old_node_child);
    }
}

Trie::Trie(const Trie& trie)
{
    root = new Node(trie.root->data, trie.root->is_finished);
    add_child(root, trie.root);

    // Node* father { trie.root };
    // Node* new_father { root };
    // std::vector<Node*> List { father };
    // std::vector<Node*>::iterator delt;

    // while (List.size() != 0) {
    //     for (size_t j {}; j < List[0]->children.size(); j++)
    //         List.push_back(List[0]->children[j]);
    //     // func(List[0]);
    //     new_father->children.push_back(new Node { List[0]->data, List[0]->is_finished });

    //     father = father->children[father->children.size() - 1];

    //     delt = List.begin();
    //     List.erase(delt);
    // }
}

Trie::Trie(Trie&& trie)
    : root { trie.root }
{
    trie.root = nullptr;
}

void Trie::operator=(const Trie& trie)
{
    root = new Node(trie.root->data, trie.root->is_finished);
    add_child(root, trie.root);
}

void Trie::operator=(Trie&& trie)
{
    root = trie.root;
    trie.root = nullptr;
}