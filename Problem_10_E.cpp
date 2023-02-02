#include <iostream>
#include <bits/stdc++.h>

using namespace std;

struct Node {
	int index;
	int data;
	float priority;
	Node* left, * right;
	Node* parent;
};

typedef Node* NodePtr;

class Treap {
private:
	NodePtr root;

	void leftRotate(NodePtr x) {
		NodePtr y = x->right;
		x->right = y->left;
		if (y->left != nullptr) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		}
		else if (x == x->parent->left) {
			x->parent->left = y;
		}
		else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	void rightRotate(NodePtr x) {
		NodePtr y = x->left;
		x->left = y->right;
		if (y->right != nullptr) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		}
		else if (x == x->parent->right) {
			x->parent->right = y;
		}
		else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}

	void moveUp(NodePtr x) {
		while (x->parent != nullptr && !(x->parent != nullptr && x->priority >= x->parent->priority)) {
			if (x == x->parent->left) {
				rightRotate(x->parent);
			}
			else {
				leftRotate(x->parent);
			}
		}
	}

public:
	Treap() {
		root = nullptr;
	}

	NodePtr insert(int index, int key, float priority) {
		NodePtr node = new Node;
		NodePtr y = nullptr;
		NodePtr x = this->root;

		while (x != nullptr) {
			y = x;
			if (key < x->data) {
				x = x->left;
			}
			else {
				x = x->right;
			}
		}

		node->index = index;
		node->parent = nullptr;
		node->left = nullptr;
		node->right = nullptr;
		node->data = key;
		node->priority = priority;

		node->parent = y;
		if (y == nullptr) {
			root = node;
		}
		else if (node->data < y->data) {
			y->left = node;
		}
		else {
			y->right = node;
		}

		if (node->parent != nullptr) {
			moveUp(node);
		}

		return node;
	}
};

int main() {
    Treap root;

    int n;
    cin >> n;

	vector<NodePtr> nodesTmp(n);

    for (int i = 0; i < n; i++) {
		int a, b;
        cin >> a >> b;
        nodesTmp[i] = root.insert((i + 1), a, b);
    }

    cout << "YES" << endl;
    
    for (int i = 0; i < n; i++) {
		NodePtr parent = nodesTmp[i]->parent;
		NodePtr left = nodesTmp[i]->left;
		NodePtr right = nodesTmp[i]->right;
        cout << ((parent == nullptr) ? 0 : parent->index) << " " 
			 << ((left == nullptr) ? 0 : left->index) << " " 
			 << ((right == nullptr) ? 0 : right->index) << endl;
    }

    return 0;
}