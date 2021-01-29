#include "redblacktree.h"

int main() {
	Node *root = new Node(11, 12, Color::RED);
	RedBlackTree tree(root);
	tree.put(21, 23);
	tree.put(25, 245);
	tree.put(1, 22);
	tree.put(2, 22);
	tree.put(3, 33);
	return 0;
}
