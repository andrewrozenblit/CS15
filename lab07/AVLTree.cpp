/*
 *      AVLTree.h
 *      AVL Trees
 *      CS 15 Lab 7
 *
 *      A class that represents an ordered sequence of elements.  This
 *      one is for strings.
 *
 *      2024-03-4 Modified by Skylar Gilfeather
 *                Rewrote documentation 
 *                Added ASCII AVL Trees to leftRotate() and rightRotate()
 *                Added and renamed local variables in leftRotate() and
 *                    rightRotate() to provide a template to students.
 *                Moved increment of node's height out of leftRotate() and
 *                    rightRotate() and into insert(), so that remove()
 *                    can properly update height with these rotation methods.
 */  


#include <iostream>
#include "AVLTree.h"

using namespace std;


/* 
 * Purpose: Creates a new AVL Tree Node on the heap.
 * Parameters:
 *      data - integer data stored in the Node
 *      height - height of the Node, i.e. max number of edges to a leaf
 *      left - left child Node of the Node, or nullptr
 *      right - right child Node of the Node, or nullptr
 * Returns: a new Node on the heap.
 */
static Node *newNode(int data, int height, Node *left, Node *right)
{
        Node *np = new Node();

        np->data  = data;
        np->height = height;
        np->left  = left;
        np->right = right;

        return np;
} 


/* 
 * Purpose: Creates a new AVL Tree Node on the heap. Creates a 'leaf' Node
 *          with a height of 0 and no children.
 * Parameters:
 *      data - integer data stored in the Node
 * Returns: a new Node on the heap.
 */
static Node *newNode(int data)
{
        return newNode(data, 0, nullptr, nullptr);
}


/* 
 * Purpose: Deletes an AVL Tree Node on the heap.
 * Parameters:
 *      node - Node on the heap to delete
 * Returns: None.
 */
static void deleteNode(Node *node)
{
        node->height = -1;  /* something that couldn't be in a real node */
        node->data  = -1;  /* arbitrary value */
        node->left  = nullptr;
        node->right = nullptr;
        delete node;
}


/*
 * Purpose: Creates a new, empty AVLTree.
 * Parameters: None.
 * Returns: A new AVLTree!
 */
AVLTree::AVLTree()
{
        root = nullptr;
}


/*
 * Purpose: Delete an AVL Tree using postOrderDelete()
 * Parameters: None.
 * Returns: None.
 */
AVLTree::~AVLTree()
{
        /* walk tree in post-order traversal and delete */
        postOrderDelete(root);
        root = nullptr;   /* not really necessary, since the tree is going 
                             away, but might want to guard against someone
                             using a pointer after deleting */
}


/*
 * Purpose: Delete the subtree rooted at node using a post-order traversal:
 *          delete the left subtree, right subtree, and then the node itself!
 * Parameters:
 *      node - Node at the root of the subtree to delete
 * Returns: None.
 */
void AVLTree::postOrderDelete(Node *node)
{
        if (node != nullptr) {
                postOrderDelete(node->left);
                postOrderDelete(node->right);
                deleteNode(node);
        }
}


/*
 * Purpose: Insert the value into the AVL Tree, using recursive insert()
 * Parameters:
 *      value - interger value to insert into the tree
 * Returns: None.
 */
void AVLTree::insert(int value)
{
        root = insert(root, value);
}


/*
 * Purpose: Insert the value into the subtree rooted at node Node.
 *          Recursively traverse the AVL tree to the leaf position where
 *          value should be inserted, and inserts it as a new Node.
 *          Balance the subtree rooted at node, if necessary, and return
 *          the Node now in node's position.
 * Parameters:
 *      node - currently visited Node
 *      value - interger value to insert into the tree
 * Returns: The Node now in the position of node in the AVL tree: node, if
 *          no rotations were performed, or one of node's children, if a 
 *          rotation was performed.       
 */
Node *AVLTree::insert(Node *node, int value)
{
        /* node is an empty position, a child of a leaf node: insert here! */
        if (node == nullptr) {
                return newNode(value);
        } 
        /* if value already exists in the AVL Tree, do not insert */
        else if (value == node->data) {
        	return node;
        }
        /* traverse to and insert value somewhere in node's left subtree */
        else if (value < node->data) {
                node->left = insert(node->left, value);
        } 
        /* traverse to and insert value somewhere in node's right subtree */
        else if (value > node->data) {
                node->right = insert(node->right, value);
        }

        /* AVL Tree rebalancing starts */
        node->height = 1 + max(nodeHeight(node->left), 
                               nodeHeight(node->right));

        Node *newNode = balance(node);
        /* AVL Tree rebalancing ends */

        return newNode;
}


/*
 * Purpose: Check if the subtree rooted at node is out of balance. Then,
 *          rebalance the subtree rooted at node if necessary, by calling
 *          leftRotate() and rightRotate() to perform rotations.
 * Parameters:
 *      node - Node at the root of the subtree to rebalance
 * Returns: The Node now in the position of node in the AVL tree: node, if
 *          no rotations were performed, or one of node's children, if a 
 *          rotation was performed.  
 */
Node *AVLTree::balance(Node *node) 
{
        int balanceFactor = heightDiff (node);


        /* TODO: evaluate the balance factor to see if node is balanced.
                 if not, handle the case: LL, LR, RR, or RL! */


        return node;
}


/*
 * Purpose: Perform a single right rotation on the subtree rooted at node
 * Parameters:
 *      node - Node at the root of the subtree to rebalance
 * Returns: The Node now in the position of node in the AVL tree: node, if
 *          no rotations were performed, or one of node's children, if a 
 *          rotation was performed.  
 * 
 * Visual: A single right rotation should convert this subtree:
 * 
 *              [ node ]
 *              /       \
 *        [ leftChild ] [ rightChild ]
 *         /         \
 *   [ llTree ] [ lrTree ]
 * 
 * Into this subtree:
 * 
 *               [ leftChild ]
 *                /          \
 *         [ llTree ]      [ node ]
 *                         /      \ 
 *                  [ lrTree ] [ rightChild ]
 */
Node *AVLTree::rightRotate(Node *node) 
{ 
        Node *leftChild = node->left;
        Node *rightChild = node->right;

        Node *llTree = node->left->left;
        Node *lrTree = node->left->right;


        // TODO: perform a single right rotation on node!
        leftChild->right = node; 
        node->left = lltree;
        // TODO: update heights of nodes that have moved!
        node->height = node->height+1;
        leftChild = leftChild->height-1;
        // TODO: return the Node that has replaced node!
        return node;
} 


/*
 * Purpose: Perform a left rotation on the subtree rooted at node
 * Parameters:
 *      node - Node at the root of the subtree to rebalance
 * Returns: The Node now in the position of node in the AVL tree: node, if
 *          no rotations were performed, or one of node's children, if a 
 *          rotation was performed.  
 * 
 * Visual: A single left rotation should convert this subtree:
 * 
 *              [ node ]
 *              /       \
 *        [ leftChild ] [ rightChild ]
 *                        /         \
 *                  [ rlTree ] [ rrTree ]
 * 
 * Into this subtree:
 * 
 *              [ rightChild ]
 *                /       \
 *           [ node ]   [ rrTree ]
 *          /       \         
 *   [ leftChild ]  [ rlTree ]
 */
Node *AVLTree::leftRotate(Node *node) 
{ 
        Node *leftChild = node->left;
        Node *rightChild = node->right;

        Node *rrTree = node->right->right;
        Node *rlTree = node->right->left;


        // TODO: perform a single left rotation on node!

        // TODO: update heights of nodes that have moved!

        // TODO: return the Node that has replaced node!
        return node;
} 


/*
 * Purpose: Calculate the difference between the height of node's left child
 *          and the height of node's right child.
 * Parameters:
 *      node - Node to calculate the height difference for its children
 * Returns: The integer height difference: greater than 0, if node's left
 *          subtree is heavier, and less than 0, if node's right subtree
 *          is heavier.
 */
int AVLTree::heightDiff(Node *node)
{
        int leftHeight = nodeHeight(node->left);
        int rightHeight = nodeHeight(node->right);
        return leftHeight - rightHeight;
}


/*
 * Purpose: Returns the height of the node, or -1 if the node doesn't exist.
 * Parameters:
 *      node - Node to retrieve the height of
 * Returns: The node's set height, or -1 is the node doesn't exist
 */
int AVLTree::nodeHeight(Node *node) 
{ 
        if (node == nullptr) {
                return -1; 
        }
        return node->height; 
} 


/*
 * Purpose: Delete the value if it's contained in the AVL Tree.
 * Parameters:
 *      value - The integer value to remove from the true
 * Returns: True, if value was contained within the AVL tree and deleted;
 *          false if value was not in the AVL tree.
 */
bool AVLTree::remove(int value)
{
        return remove(root, value);
}


/*
 * Purpose: Delete the value if it's contained in the subtree rooted at 
 *          node. Recursively traverse the AVL tree to the node containing
 *          value, delete the node, and rebalance the tree if necessary,
 *          returning true. Otherwise, if no node with value is found, return
 *          false.
 * Parameters:
 *      node - currently visited Node
 *      value - The integer value to remove from the true
 * Returns: True, if value was contained within the AVL tree and deleted;
 *          false if value was not in the AVL tree.
 */
bool AVLTree::remove(Node *node, int value)
{
        // SKYLAR TODO: write solution for remove!
}


/* 
 * Input: N/A
 * Returns: N/A
 * Does: uses a helper function to print a pretty tree.
*/
void AVLTree::print_tree() const
{
        printPretty(root, 1, 0, std::cout);
}
