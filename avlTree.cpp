#include <iostream>

using namespace std;

//Struct for Binary Search Tree Node
struct AVLNode {
	int data;
	int height;
	AVLNode* left;
	AVLNode* right;
};

//Get max between two numbers
int max(int a, int b) {
	return (a > b)? a : b;
}

//Return height of root
int height(AVLNode* root) {
	if (root == NULL)
		return 0;
	return root->height;
}

//get balance value of left - right
int getBalance(AVLNode* root) {
	if (root == NULL) {
		return 0;
	}
	return height(root->left) - height(root->right);
}

//Create a new Node Function
AVLNode* CreateNewNode(int data) {
	AVLNode* newNode = new AVLNode();
	newNode->data = data;
	newNode->height = 1;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

//Right Rotate Function
AVLNode* rightRotate(AVLNode* root) {
	AVLNode* temp = root->left;
	AVLNode* temp2 = temp->right;

	temp->right = root;
	root->left = temp2;

	root->height =  max(height(root->left), height(root->right)) + 1;
	temp->height =  max(height(root->left), height(root->right)) + 1;

	return temp;
}

//Left Rotate Function
AVLNode* leftRotate(AVLNode* root) {
	AVLNode* temp = root->right;
	AVLNode* temp2 = temp->left;

	temp->left = root;
	root->right = temp2;

	root->height =  max(height(root->left), height(root->right)) + 1;
	temp->height = max(height(root->left), height(root->right)) + 1;

	return temp;
}

//Insert a Node into the BST
AVLNode* Insert(AVLNode* root, int data) {
	if (root == NULL) {
		return CreateNewNode(data);
	}

	if (data < root->data) {
		root->left = Insert(root->left, data);
	} else if (data > root->data){
		root->right = Insert(root->right, data);
	} else {
		return root;
	}

	root->height = 1 + max(height(root->left), height(root->right));

	int balance = getBalance(root); //difference between left branch heigh and right branch

	//Checking for balance cases
	//Left Left Case
	if (balance > 1 && data < root->left->data)
		return rightRotate(root);
	

	//Right Right Case
	if (balance < -1 && data > root->right->data)
		return leftRotate(root);
	
	//Left Right Case
	if (balance > 1 && data > root->left->data) {
		root->left = leftRotate(root);
		return rightRotate(root);
	}

	//Right Left Case
	if (balance < -1 && data < root->right->data) {
		root->right = rightRotate(root);
		return leftRotate(root);
	}

	return root;

}

void preOrderPrint(AVLNode* root) {
	if (root != NULL) {
		cout << root->data << " ";
		preOrderPrint(root->left);
		preOrderPrint(root->right);
	}
}

void inOrderPrint(AVLNode* root) {
	if (root != NULL) {
		inOrderPrint(root->left);
		cout << root->data << " ";
		inOrderPrint(root->right);
	}
}

void postOrderPrint(AVLNode* root) {
	if (root != NULL) {
		postOrderPrint(root->left);
		postOrderPrint(root->right);
		cout << root->data << " ";
	}
}

int main() {

	int inputs [] = {6,17,20,41,45,52,57,65,71,76,79,87,92,95,99};
	int size = *(&inputs + 1) - inputs;
	
	AVLNode* root;
	for (int i = 0; i < size; i++) {
		root = Insert(root,inputs[i]);
	}

	cout << "inOrderPrint: \n";
	inOrderPrint(root);

	cout << "\npreOrderPrint: \n";
	preOrderPrint(root);

	cout << "\npostOrderPrint: \n";
	postOrderPrint(root);

	cout << endl;

	return 0;
}