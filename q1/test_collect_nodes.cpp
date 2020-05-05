#include "tree.hpp"
#include <iostream>

int main() {

    tree_node *t;

    t = tree_insert(t, "alpha");
    t = tree_insert(t, "bravo");
    t = tree_insert(t, "charlie");
    t = tree_insert(t, "delta");

    vector<tree_node*> vec_tree_nodes;
    tree_collect_nodes(vec_tree_nodes, t);

    cerr << endl << "collect_nodes (made by dt)" << endl;
    for (int i=0; i<vec_tree_nodes.size(); i++) {
        cout << (vec_tree_nodes[i])->value << endl;
    }

    vector<tree_node*> vec_tree_ordered_nodes;
    tree_collect_nodes(vec_tree_ordered_nodes, t);

    cerr << endl << "collect_nodes_in_order" << endl;
    for (int i=0; i<vec_tree_ordered_nodes.size(); i++) {
        cout << (vec_tree_ordered_nodes[i])->value << endl;
    }

}