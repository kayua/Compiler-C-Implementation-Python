#include <stdio.h>    // Standard input/output functions
#include <stdlib.h>   // Standard library for memory allocation, process control, etc.
#include <assert.h>   // Provides the assert macro for debugging
#include <stdarg.h>   // Supports variable argument lists for functions
#include "node.h"     // Custom header file for Node structure

// Defines the data type for the Node
typedef int Node_type;

// Global variable for the root of the syntax tree
Node *syntax_tree;

/**
 * @brief Creates a new node in the syntax tree.
 * 
 * This function dynamically allocates memory for a new node, initializes its fields, and adds any number of child nodes 
 * passed as arguments. The function supports variable arguments (child nodes) using the `stdarg` library.
 * 
 * @param nl The line number where the node appears in the source code.
 * @param t The type of the node (defined as Node_type).
 * @param lexeme A string representing the lexeme associated with this node.
 * @param ... A variable number of child nodes (of type Node*), terminated by NULL.
 * 
 * @return A pointer to the newly created node.
 */
Node* create_node(int nl, Node_type t, char* lexeme,  /* Node* children */ ...)
{
    // Allocate memory for a new node
    Node* new_node = (Node *)malloc(sizeof(Node));
    new_node->line_num = nl;        // Set the line number
    new_node->type = t;             // Set the node type
    new_node->lexeme = lexeme;      // Set the lexeme
    new_node->n_child = 0;          // Initialize the number of children to 0
    new_node->children = NULL;      // Initialize the children array to NULL

    // Process the variable argument list (child nodes)
    va_list ap;
    va_start(ap, NULL);             // Initialize variable argument list
    Node* arg = va_arg(ap, Node*);  // Get the first child node

    // Loop through the child nodes and add them to the new node's children array
    for (; arg != NULL; arg = va_arg(ap, Node*)) {
        if (new_node->children == NULL)
            // Allocate memory for the first child
            new_node->children = (Node**) malloc(sizeof(Node*));
        else
            // Reallocate memory to accommodate additional children
            new_node->children = (Node**) realloc(new_node->children, (new_node->n_child + 1) * sizeof(Node*));

        // Add the current child to the children array
        new_node->children[new_node->n_child] = arg;
        new_node->n_child++;  // Increment the number of children
    }

    va_end(ap);  // Clean up the variable argument list
    return new_node;  // Return the newly created node
}

/**
 * @brief Returns the number of children a node has.
 * 
 * @param n A pointer to the node.
 * @return The number of children of the node.
 */
int nb_of_children(Node* n) {
    assert(n != NULL);  // Ensure the node is not NULL
    return n->n_child;  // Return the number of children
}

/**
 * @brief Checks if a node is a leaf (i.e., has no children).
 * 
 * @param n A pointer to the node.
 * @return 1 if the node is a leaf, 0 otherwise.
 */
int is_leaf(Node* n) {
    assert(n != NULL);  // Ensure the node is not NULL
    return n->n_child == 0;  // Return 1 if no children, 0 otherwise
}

/**
 * @brief Retrieves the i-th child of a node.
 * 
 * @param n A pointer to the node.
 * @param i The index of the child to retrieve.
 * @return A pointer to the i-th child.
 */
Node* child(Node* n, int i) {
    assert(n != NULL);  // Ensure the node is not NULL
    assert((0 <= i) && ((unsigned int)i < n->n_child));  // Ensure i is a valid index
    return n->children[i];  // Return the i-th child
}

/**
 * @brief Recursively frees a node and all of its children.
 * 
 * This function performs a deep free, recursively deallocating memory for the node and its children.
 * 
 * @param n A pointer to the node to free.
 * @return Always returns 0.
 */
int deep_free_node(Node* n) {
    int i;
    int size_children;

    if (n->n_child == 0) {
        // If the node has no children, free the node itself
        free(n);
    } else if (n->n_child > 0) {
        // If the node has children, recursively free each child
        size_children = n->n_child;
        for (i = 0; i < size_children; i++) {
            deep_free_node(n->children[n->n_child - 1]);  // Free the last child
            n->children = (Node**) realloc(n->children, (n->n_child - 1) * sizeof(Node*));  // Reallocate memory for the remaining children
            n->n_child--;  // Decrement the child count
        }
        free(n->children);  // Free the children array
        free(n);  // Free the node itself
    }
    return 0;
}

/**
 * @brief Computes the height of a node in the syntax tree.
 * 
 * The height of a node is the length of the longest path from the node to a leaf.
 * 
 * @param n A pointer to the node.
 * @return The height of the node.
 */
int height(Node* n) {
    int i = 0;
    int _height = 0;
    int _height_child = 0;
    assert(n != NULL);  // Ensure the node is not NULL

    if (n->n_child != 0) {
        // If the node has children, compute the height of each child
        for (i = 0; i < n->n_child; i++) {
            _height_child = height(n->children[i]);  // Recursively compute child height
            if (_height < _height_child) {
                _height = _height_child;  // Keep track of the maximum height
            }
        }
        return 1 + _height;  // Add 1 for the current node and return the height
    } else {
        return 1;  // Leaf nodes have height 1
    }
}

/**
 * @brief Recursively prints the lexemes of a node and its children in post-order.
 * 
 * @param n A pointer to the node.
 */
void uncompile(Node *n) {
    assert(n != NULL);  // Ensure the node is not NULL

    // Recursively print lexemes of all children
    for (int i = 0; i < n->n_child; i++) {
        uncompile(n->children[i]);
    }

    // Print the lexeme of the current node
    printf("%s \n", n->lexeme);
}
