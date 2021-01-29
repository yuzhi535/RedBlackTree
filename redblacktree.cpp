//
// Created by sasuke on 1/26/21.
//

#include "redblacktree.h"

void RedBlackTree::put(Key k, Value val) {
	root = put(this->root, k, val);
	root->setColor(Color::BLACK);
}

RedBlackTree::RedBlackTree(Node *t) {
	this->root = t;
}

/**
 * @brief insert the node
 * @param node
 * @param k
 * @param val
 * @return
 */
Node *RedBlackTree::put(Node *node, Key k, Value val) {
	if (node == nullptr) {
		return new Node(k, val, Color::RED);
	}
#define DEV
#ifndef DEV
	if (isRed(node->getRchild()) && isRed(node->getLchild())) {
		flipColors(node);
	}
#endif

	if (isEqualTo(k, node->getKey()) == -1) {
		node->setLchild(put(node->getLchild(), k, val));
	} else if (isEqualTo(k, node->getKey()) == 1) {
		node->setRchild(put(node->getRchild(), k, val));
	} else {
		node->setVal(val);
	}

	// deal with special conditions
	// in this order!!!
	if (!isRed(node->getLchild()) && isRed(node->getRchild())) {
		node = rotateLeft(node);
	}
	if (isRed(node->getLchild()) && isRed(node->getLchild()->getLchild())) {
		node = rotateRight(node);
	}
#ifdef DEV
	// 分裂四叉树
	if (isRed(node->getRchild()) && isRed(node->getLchild())) {
		flipColors(node);
	}
#endif

	return node;
}

/**
 * @brief
 * @param val
 * @param col
 */
Node::Node(Key k, Value val, Color col) {
	this->value = val;
	this->color = col;
	this->key = k;
	this->lchild = this->rchild = nullptr;
}

bool isRed(Node *root) {
	if (root == nullptr) return false;
	return root->color == Color::RED;
}

/**
 * @brief 翻转颜色
 * @param h
 */
void flipColors(Node *h) {
	Node *arr[3] = {h, h->lchild, h->rchild};
	for (auto t : arr) {
		t->color = t->color ? Color::BLACK : Color::RED;
	}
}

/**
 * @brief 左旋
 * @param h
 * @return
 */
Node *rotateLeft(Node *h) {
	auto x = h->rchild;
	h->rchild = x->lchild;
	x->lchild = h;
	x->color = h->color;
	h->color = Color::RED;
	return x;
}


/**
 * @brief 右旋
 * @param h
 * @return
 */
Node *rotateRight(Node *h) {
	auto x = h->lchild;
	h->lchild = x->rchild;
	x->rchild = h;
	x->color = h->color;
	h->color = Color::RED;
	return x;
}

int isEqualTo(Key k1, Key k2) {
	if (k1 < k2) {
		return -1;
	} else if (k1 > k2) {
		return 1;
	} else {
		return 0;
	}
}
