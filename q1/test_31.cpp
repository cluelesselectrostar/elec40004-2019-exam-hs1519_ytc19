#include "tree.hpp"

int main()
{
  tree_node z {"z", nullptr, nullptr};
  tree_node y {"y", nullptr, nullptr};
  tree_node x {"x", nullptr, nullptr};
  tree_node d {"d", nullptr, nullptr};
  tree_node a {"a", &x, &y};
  tree_node c {"c", &z, &d};
  tree_node b {"b", &a, &c};

  vector<tree_node*> tre;
  tree_collect_nodes(tre, &b);

  /*tree_node* root = tree_rebuild_balanced(tre, 0, tre.size());
  vector<tree_node*> other;
  tree_collect_nodes_in_order(other, root);*/

  for(int i=0; i<tre.size(); i++){
    tree_node tmp = *tre[i];
    cout << tmp.value << endl;
  }
}
