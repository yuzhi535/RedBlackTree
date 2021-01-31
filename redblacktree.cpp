//
// Created by sasuke on 1/26/21.
//

#include "redblacktree.h"

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
	if (root == nullptr)
		return false;
	return root->color == Color::RED;
}

/**
 * @brief 翻转颜色
 * @param root
 */
void flipColors(Node *root) {
	Node *nodes[3] = {root, root->lchild, root->rchild};

	for (auto i : nodes) {
		i->color = i->color ? Color::BLACK : Color::RED;
	}
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

Node *moveRedRight(Node *h) {
	flipColors(h);
	if (isRed(h->getLchild()->getLchild())) {
		h = rotateRight(h);
		flipColors(h);
	}
	return h;
}

Node *moveRedLeft(Node *h) {
	flipColors(h);
	if (isRed(h->getRchild()->getLchild())) {
		h->setRchild(rotateRight(h->getRchild()));
		h = rotateLeft(h);
		flipColors(h);
	}
	return h;
}

int isEqualTo(Key k1, Key k2) {
	if (k1 < k2) {
		return LESS;
	} else if (k1 > k2) {
		return BIGGER;
	} else {
		return EQUAL;
	}
}

/**
 * @brief to fix up the node to the standard llrb
 * @param h
 * @return
 */
Node *fixup(Node *h) {

	if (isRed(h->getRchild())) {
		h = rotateLeft(h);
	}

	if (isRed(h->getLchild()) &&
	    isRed((h->getLchild()->getLchild()))) {
		h = rotateRight(h);
	}

	if (isRed(h->getLchild()) &&
	    isRed(h->getRchild())) {
		flipColors(h);
	}

	return h;
}

Node *RedBlackTree::put(Key k, Value val) {
	root = put(this->root, k, val);
	root->setColor(Color::BLACK);
	return root;
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
	if (isRed(node->getRchild()) && isRed(node->getLchild()))
	{
		flipColors(node);
	}
#endif

	if (isEqualTo(k, node->getKey()) == LESS) {
		node->setLchild(put(node->getLchild(), k, val));
	} else if (isEqualTo(k, node->getKey()) == BIGGER) {
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
	if (isRed(node->getRchild()) && isRed(node->getLchild())) {
		flipColors(node);
	}
#endif

	return node;
}


void RedBlackTree::deletemin() {
	root = deletemin(root);
	root->setColor(Color::BLACK);
}

void RedBlackTree::deletemax() {
	this->root = deletemax(this->root);
	this->root->setColor(Color::BLACK);
}

/**
 * @brief
 * @param h
 * @return
 */
Node *RedBlackTree::deletemax(Node *h) {
	if (isRed(h->getLchild())) {
		h = rotateRight(h);
	}

	if (!h->getRchild()) {
		delete h;
		return nullptr;
	}

	if (!isRed(h->getRchild()) && !isRed(h->getRchild()->getLchild())) {
		h = moveRedRight(h);
	}

	//-------------------------------------------
	// h.right = deletemax(h.right)
	h->setRchild(deletemax(h->getRchild()));

	return fixup(h);
}

Node *RedBlackTree::deletemin(Node *h) {
	if (nullptr == h->getLchild()) {
		delete h;
		return nullptr;
	}

	if (!isRed(h->getLchild()) &&
	    !isRed(h->getLchild()->getLchild())) {
		h = moveRedLeft(h);
	}
	h->setLchild(deletemin(h->getLchild()));
	return fixup(h);
}

bool RedBlackTree::find(Key key, Value &val) {
	Node *ans = find(this->root, key);
	if (ans) {
		val = ans->getVal();
		return true;
	} else
		return false;
}

Node *RedBlackTree::find(Node *h, Key k) {
	if (nullptr == h) {
		return nullptr;
	}
	auto cmp = isEqualTo(k, h->getKey());
	if (EQUAL == cmp) {
		return h;
	} else if (BIGGER == cmp) {
		return find(h->getRchild(), k);
	} else {
		return find(h->getLchild(), k);
	}
}

void RedBlackTree::del(Key k) {
	del(this->root, k);
}

/**
 * @brief
 * @param h
 * @param k
 * @return
 */
Node *RedBlackTree::del(Node *h, Key k) {
	int cmp = isEqualTo(k, h->getKey());
	if (LESS == cmp) {
		if (!isRed(h->getLchild()) && !isRed(h->getLchild()->getLchild())) {
			h = moveRedLeft(h);
		}
		h->setLchild(del(h->getLchild(), k));
	} else {
		if (isRed(h->getLchild())) {
			h = rotateRight(h);
		}
		if (EQUAL == cmp && (nullptr == h->getRchild())) {
			delete h;
			return nullptr;
		}
		if (!isRed(h->getRchild()) && !isRed(h->getRchild()->getLchild())) {
			h = moveRedRight(h);
		}

		if (EQUAL == cmp) {
			h->setKey(getminKey(h));
			h->setVal(h->getRchild()->getVal());
			h->setRchild(deletemin(h->getRchild()));
		} else {
			h->setRchild(del(h->getRchild(), k));
		}
	}
	return fixup(h);
}

Key RedBlackTree::getminKey(Node *node) {
	if (node->getLchild()) {
		return getminKey(node->getLchild());
	} else {
		return node->getKey();
	}
}
