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

enum STatus {
	EQUAL = 0, LESS = -1, BIGGER = 1
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

	Node *getLchild() const { return this->lchild; }

	Node *getRchild() const { return this->rchild; }

	void setColor(Color col) { this->color = col; }

	Color getColor() const { return this->color; }

	void setKey(Key k) { this->key = k; }

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

	void deletemin();

	void deletemax();

	bool find(Key key, Value &val);

	void del(Key k);

	Key getminKey(Node *node);

private:
	Node *root;

	Node *deletemin(Node *h);

	Node *deletemax(Node *h);

	Node *find(Node *h, Key k);

	Node *put(Node *node, Key k, Value val);

	Node *del(Node *h, Key k);
};


#endif //REDBLACKTREE_REDBLACKTREE_H
