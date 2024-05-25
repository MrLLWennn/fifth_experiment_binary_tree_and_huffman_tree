#include"binary_tree.h"
#include"huffman_tree.h"

using std::cin;
using std::cout;
using std::endl;

int main() {
//    Tree<size_t> tree;
//    tree.insertAsRoot(1);
//    TreeNode<size_t>* node1 = tree.insert(2, tree.root());
//    TreeNode<size_t>* node2 = tree.insert(tree.root(), 3);
//    tree.insert(node1, 4);
//    tree.insert(5, node1);
//    tree.insert(node2, 6);
//    tree.insert(7, node2);
//    std::cout << tree.remove(node1) <<std::endl;
//    std::cout << tree.size() << std::endl;
//    tree.displayTree();
//    tree.traversePre(tree.root());
//    tree.traverseIn(tree.root());
//    tree.traversePost(tree.root());

    vector<int> weight = {1, 2, 3, 4, 5};
    vector<char> value = {'a', 'b', 'c', 'd', 'e'};

    huffmanTree tree(weight, value);
    string str;
    cin >> str;
    string result;
    result = tree.encode(str);
    cout << result << endl;

    string result1 = tree.decode(str);
    cout << result1 << endl;

    return 0;
}
