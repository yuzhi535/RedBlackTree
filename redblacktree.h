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
	friend Node *rotateLeft(Node *h);

	friend Node *rotateRight(Node *h);

	friend void flipColors(Node *h);

	friend bool isRed(Node *root);

public:
	explicit Node(Key k, Value val, Color col);

	~Node() = default;

	Value getVal() const { return this->value; }

	void setVal(Value val) { this->value = val; }

	void setLchild(Node *child) {
		this->lchild = child;
	}

	void setRchild(Node *child) {
		this->rchild = child;
	}

	Key getKey() const { return this->key; }

	Node *getLchild() { return this->lchild; }

	Node *getRchild() { return this->rchild; }

	void setColor(Color col) { this->color = col; }

	Color getColor() { return this->color; }

private:
	Value value;
	Color color;
	Key key;
	Node *lchild, *rchild;
};

/**
 * @brief
 * @todo implement the deletion
 */
class RedBlackTree {
public:

	explicit RedBlackTree(Node *t);

	~RedBlackTree() = default;

	void put(Key k, Value val);

private:
	Node *root;

	Node *put(Node *node, Key k, Value val);
};


#endif //REDBLACKTREE_REDBLACKTREE_H
