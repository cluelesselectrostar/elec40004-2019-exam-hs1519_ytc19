#include "tree.hpp"
#include "string_set.hpp"

void render(const tree_node *r) {

    //string node = r->value;
    string label;

    if (r == nullptr) {
        return; 
    } 

    if (r->left != nullptr) {
        cout << "\"" << r->value << "\" -> \"" << r->left->value << "\" [label=\"L\"]" << endl ;
    }

    if (r->right !=nullptr) {
        cout << "\"" << r->value << "\" -> \"" << r->right->value << "\" [label=\"R\"]" << endl ;
    }
    
    render(r->left);
    render(r->right);
}


int main(int argc, char **argv)
{
    if(argc==1){
        cerr<<"Need to specify which set to use."<<endl;
        exit(1);
    }

    cerr<<"Creating string set of type "<<argv[1]<<endl;
    StringSet *s=create_string_set(argv[1]);

    string v;
    while( cin >> v ){
        s->insert(v);
    }

    s->optimise();

    const tree_node *r = s->root(); //this one is const (always the root node)

    cout << "digraph G { "<<endl; // TODO: render the links between nodes
    render(r);
    cout << "}" << endl;
}
