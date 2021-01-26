//
// Created by sasuke on 1/26/21.
//

#ifndef REDBLACKTREE_REDBLACKTREE_H
#define REDBLACKTREE_REDBLACKTREE_H

#include <algorithm>
#include <iostream>

typedef int Value;
typedef int Leaf;
typedef int Key;
enum Color {
	BLACK = 0, RED
};

int isEqualTo(Key k1, Key k2);

class Node;

/**
 * @brief basic node. implement rotate, flip and so on.
 */
class Node {
	friend Node *rotateLeft(Node *root);

	friend Node *rotateRight(Node *root);

	friend void flipColors(Node *root);

public:
	explicit Node(Key k, Value val, Color col);

	~Node() = default;

	bool isRed();

	Value getVal() { return this->value; }

	void setVal(Value val) { this->value = val; }

	void setLchild(Node *child) {
		this->lchild = child;
	}

	void setRchild(Node *child) {
		this->rchild = child;
	}

	Key getKey() { return this->key; }

	Node *getLchild() { return this->lchild; }

	Node *getRchild() { return this->rchild; }

	void setColor(Color col) { this->color = col; }

private:
	Value value;
	Color color;
	Key key;
	Node *lchild, *rchild;
};

class RedBlackTree {
public:

	RedBlackTree(Node *t);

	~RedBlackTree() = default;

	Node *put(Key k, Value val);

private:
	Node *root;

	Node *put(Node *node, Key k, Value val);

};


#endif //REDBLACKTREE_REDBLACKTREE_H
