//
// Created by sasuke on 1/26/21.
//

#include "redblacktree.h"

Node *RedBlackTree::put(Key k, Value val) {
	root = put(this->root, k, val);
	root->setColor(Color::BLACK);
	return root;
}

RedBlackTree::RedBlackTree(Node *t) {
	this->root = t;
}

Node *RedBlackTree::put(Node *node, Key k, Value val) {
	if (node == nullptr) {
		return new Node(k, val, Color::RED);
	} else {
		if (isEqualTo(k, node->getKey()) == -1) {
			node->setLchild(put(node->getLchild(), k, val));
		} else if (isEqualTo(k, node->getKey()) == 1) {
			node->setRchild(put(node->getRchild(), k, val));
		} else {
			node->setVal(val);
		}
	}

	// deal with special conditions
	// in this order!!!
	if (!isRed(node->getLchild()) && isRed(node->getRchild())) {
		node = rotateLeft(node);
	}
	if (isRed(node->getLchild()) && isRed(node->getLchild()->getLchild())) {
		node = rotateRight(node);
	}
	if (isRed(node->getRchild()) && isRed(node->getLchild())) {
		flipColors(node);
	}

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
 * @param root
 */
void flipColors(Node *root) {
	root->color = Color::RED;
	root->lchild->color = Color::BLACK;
	root->rchild->color = Color::BLACK;
}

/**
 * @brief 左旋
 * @param root
 * @return
 */
Node *rotateLeft(Node *root) {
	auto x = root->rchild;
	root->rchild = x->lchild;
	x->lchild = root;
	x->color = root->color;
	root->color = Color::RED;
	return x;
}


/**
 * @brief 右旋
 * @param root
 * @return
 */
Node *rotateRight(Node *root) {
	auto x = root->lchild;
	root->lchild = x->rchild;
	x->rchild = root;
	x->color = root->color;
	root->color = Color::RED;
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
