#include <iostream>
#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;

struct Node {
    int data;
    float priority;
    Node* left, * right;
    Node* parent;
};

typedef Node* NodePtr;

class Treap {
private:
	NodePtr root;

	NodePtr searchTreeHelper(NodePtr node, int key) {
		if (node == nullptr || key == node->data) {
			return node;
		}

		if (node->left == nullptr && node->right == nullptr)
			return node;

		if (key < node->data) {
			NodePtr n = searchTreeHelper(node->left, key);

			return (n == nullptr) ? node : n;
		}

		return searchTreeHelper(node->right, key);
	}

	void printHelper(NodePtr root, string indent, bool last) {
		if (root != nullptr) {
			cout << indent;
			if (last) {
				cout << ">----";
				indent += "     ";
			}
			else {
				cout << "|----";
				indent += "|    ";
			}

			cout << root->data << "(" << root->priority << ")" << endl;

			printHelper(root->left, indent, false);
			printHelper(root->right, indent, true);
		}
	}

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
		if (x->parent == nullptr) {
			return;
		}
		if (x->parent != nullptr && x->priority >= x->parent->priority) {
			return;
		}

		if (x == x->parent->left) {
			rightRotate(x->parent);
		}
		else {
			leftRotate(x->parent);
		}

		moveUp(x);
	}

	void deleteNodeHelper(NodePtr node, int k) {
		NodePtr x = nullptr;
		while (node != nullptr) {
			if (node->data == k) {
				x = node;
				break;
			}

			if (node->data <= k) {
				node = node->right;
			}
			else {
				node = node->left;
			}
		}

		if (x == nullptr) {
			return;
		}

		moveDown(x);

		if (x == x->parent->left) {
			x->parent->left = nullptr;
		}
		else {
			x->parent->right = nullptr;
		}
		delete x;
		x = nullptr;
	}

	void moveDown(NodePtr x) {
		if (x->left == nullptr && x->right == nullptr) {
			return;
		}

		if (x->left != nullptr && x->right != nullptr) {
			if (x->left->priority < x->right->priority) {
				rightRotate(x);
			}
			else {
				leftRotate(x);
			}
		}
		else if (x->left != nullptr) {
			rightRotate(x);
		}
		else {
			leftRotate(x);
		}

		moveDown(x);
	}

public:
	Treap() {
		root = nullptr;
	}

	NodePtr searchTree(int k) {
		return searchTreeHelper(this->root, k);
	}

	NodePtr minimum(NodePtr node) {
		while (node->left != nullptr) {
			node = node->left;
		}
		return node;
	}

	NodePtr maximum(NodePtr node) {
		while (node->right != nullptr) {
			node = node->right;
		}
		return node;
	}

	NodePtr successor(NodePtr x) {
		if (x->right != nullptr) {
			return minimum(x->right);
		}

		NodePtr y = x->parent;
		while (y != nullptr && x == y->right) {
			x = y;
			y = y->parent;
		}
		return y;
	}

	void insert(int key, float priority) {
		NodePtr y = nullptr;
		NodePtr x = this->root;

		while (x != nullptr) {
			y = x;
			if (key < x->data) {
				x = x->left;
			}
			else if(key > x->data) {
				x = x->right;
			}
			else {
				return;
			}
		}

		NodePtr node = new Node;
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
	}

	void split(int x, Treap* t1, Treap* t2) {
		this->insert(x, -99);

		t1->root = this->root->left;
		t2->root = this->root->right;

		this->root->left = nullptr;
		this->root->right = nullptr;
		delete this->root;
		this->root = nullptr;
	}

	void merge(Treap t1, Treap t2) {
		NodePtr largest = t1.maximum(t1.root);
		NodePtr smallest = t2.minimum(t2.root);

		NodePtr newRoot = new Node();
		newRoot->data = (largest->data + smallest->data) / 2;
		newRoot->left = t1.root;
		newRoot->right = t2.root;
		newRoot->parent = nullptr;
		newRoot->priority = 99;

		moveDown(newRoot);

		NodePtr currPtr = newRoot;
		while (currPtr->parent != nullptr) {
			currPtr = currPtr->parent;
		}

		this->root = currPtr;

		if (newRoot == newRoot->parent->left) {
			newRoot->parent->left = nullptr;
		}
		else {
			newRoot->parent->right = nullptr;
		}

		delete(newRoot);
		newRoot = nullptr;

	}

	NodePtr getRoot() {
		return this->root;
	}

	void deleteNode(int data) {
		deleteNodeHelper(this->root, data);
	}

	void prettyPrint() {
		printHelper(this->root, "", true);
	}
};

int main() {
    srand(time(NULL));

    int n;
    cin >> n;

	Treap root;
    int y = 0;
    bool last_op_plus = true;

	NodePtr yNode;

    for (int i = 0; i < n; i++) {
        char sym;
        cin >> sym;
        int x;
        cin >> x;

        if (sym == '+') {
            if (last_op_plus)
                root.insert(x, rand() % 100);
            else
				root.insert((y + x) % INF, rand() % 100);
            last_op_plus = true;
        } else if (sym == '?') {
            yNode = root.searchTree(x);
            if (yNode == nullptr)
                cout << -1 << endl;
            else {
				if (yNode->data < x)
					yNode = root.successor(yNode);
				if (yNode == nullptr) {
					cout << -1 << endl;
				}
				else {
					y = yNode->data;
					cout << y << endl;
				}
            }
            last_op_plus = false;
		}
    }
}