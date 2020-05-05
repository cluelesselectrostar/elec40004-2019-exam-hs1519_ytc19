#include "tree.hpp"

int main()
{
  tree_node z {"z", nullptr, nullptr};
  tree_node y {"y", nullptr, &z};
  tree_node x {"x", nullptr, &y};
  tree_node d {"d", nullptr, &x};
  tree_node a {"a", nullptr, nullptr};
  tree_node c {"c", nullptr, &d};
  tree_node b {"b", &a, &c};

  vector<tree_node*> tre;
  tree_collect_nodes_in_order(tre, &b);

  tree_node* root = tree_rebuild_balanced(tre, 0, tre.size());
  vector<tree_node*> other;
  
  tree_collect_nodes_in_order(other, root);
  cerr << endl << "collecting nodes in order" << endl;
  for(int i=0; i<other.size(); i++){
    tree_node tmp = *other[i];
    cout << tmp.value << endl;
  }

  tree_collect_nodes (other, root);
  cerr << endl << "collecting nodes not in order" << endl;
  for(int i=0; i<other.size(); i++){
    tree_node tmp = *other[i];
    cout << tmp.value << endl;
  }

}
