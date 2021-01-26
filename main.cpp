#include "redblacktree.h"

int main() {
	Node *root = new Node(11, 12, Color::RED);
	RedBlackTree tree(root);
	tree.put(21, 23);
	tree.put(22, 245);
	tree.put(1, 22);
	return 0;
}
