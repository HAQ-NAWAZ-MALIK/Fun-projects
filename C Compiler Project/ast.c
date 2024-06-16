#include "interface.h"
#include "parser.h"
#include "ast.h"

int astNodeCount = 0;
int astMemory = 0;

// Array to store labels for AST node types
char* LabelMap[] = {
    "astProgram",
    "astFunction",
    "astInputParams",
    "astOutputParams",
    // ... (other labels)
};

// Function to get the label string for a given label enum
char* getLabel(int label) {
    return LabelMap[label];
}

// Function to create a new AST node
ASTNode* createASTNode(int isLeaf, Label label) {
    ASTNode* astNode = (ASTNode*)malloc(sizeof(ASTNode));
    astNode->IS_LEAF = isLeaf;
    astNode->LABEL = label;
    astNode->CHILDREN_COUNT = 0;
    astNode->next = NULL;
    astNode->parent = NULL;
    astNode->children = NULL;
    astNode->tail = NULL;

    astNodeCount++;
    astMemory += sizeof(ASTNode);
    return astNode;
}

// Function to add a single child node to a parent node
void addASTChild(ASTNode* parent, ASTNode* newChild) {
    // If the parent has no children
    if (parent->children == NULL) {
        newChild->parent = parent;
        parent->children = newChild;
        parent->tail = newChild;
        parent->CHILDREN_COUNT++;
        return;
    }

    // If the parent has one child
    if (parent->children->next == NULL) {
        newChild->parent = parent;
        parent->children->next = newChild;
        parent->tail = newChild;
        parent->CHILDREN_COUNT++;
        return;
    }

    // If the parent has multiple children, insert at the end
    newChild->parent = parent;
    parent->tail->next = newChild;
    parent->tail = newChild;
    parent->CHILDREN_COUNT++;
}

// Function to add a list of child nodes to a parent node
void addASTChildren(ASTNode* parent, ASTNode* childList) {
    ASTNode* traversal = childList;
    while (traversal != NULL) {
        addASTChild(parent, traversal);
        traversal = traversal->next;
    }
}

// Function to initialize the AST
AST* initializeAST() {
    astNodeCount = *((int*)malloc(sizeof(int)));
    astMemory = *((int*)malloc(sizeof(int)));
    AST* ast = (AST*)malloc(sizeof(AST));
    ast->root = NULL;
    return ast;
}

// Function to get the data type from a parse tree node
Token* getType(NaryTreeNode* parseTreeNode) {
    // ... (implementation omitted for brevity)
}

// Function to check if a declaration is global
int isGlobal(NaryTreeNode* parseTreeNode) {
    // ... (implementation omitted for brevity)
}

// Function to check if an identifier is a single or record type
int isSingleOrRecord(NaryTreeNode* parseTreeNode) {
    // ... (implementation omitted for brevity)
}

// Function to get an identifier from a parse tree node
Token* getIdentifier(NaryTreeNode* parseTreeNode) {
    // ... (implementation omitted for brevity)
}

// Function to get the operator from a parse tree node
Token* getOperator(NaryTreeNode* parseTreeNode) {
    // ... (implementation omitted for brevity)
}

// Function to construct the AST from a parse tree
AST* constructAST(ParseTree* parseTree) {
    AST* ast = initializeAST();
    ast->root = constructASTHelper(parseTree->root);
    return ast;
}

// Helper function to construct the AST recursively
ASTNode* constructASTHelper(NaryTreeNode* parseTreeNode) {
    // ... (implementation omitted for brevity)
}

// Helper function to construct the AST with inherited attributes
ASTNode* constructASTHelperInherited(NaryTreeNode* parseTreeNode, ASTNode* inherited) {
    // ... (implementation omitted for brevity)
}

// Function to print the AST
void printAST(ASTNode* root) {
    if (root->IS_LEAF == 1) {
        printf("Label of Node is %s\n", LabelMap[root->LABEL]);
        return;
    }

    ASTNode* traversal = root->children;
    if (traversal != NULL) {
        printAST(root->children);
        traversal = traversal->next;
    }
    printf("Label of Node is %s\n", LabelMap[root->LABEL]);

    while (traversal != NULL) {
        printAST(traversal);
        traversal = traversal->next;
    }
}

// Function to get the number of AST nodes created
int getASTNodeCount() {
    return astNodeCount;
}

// Function to get the memory consumed by the AST
int getASTMemory() {
    return astMemory;
}