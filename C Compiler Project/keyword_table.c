
#include "interface.h"
#include "keyword_table.h"
#include <string.h>
#define NUMBER_KEYWORDS 24

// Re-enabling this line due to compile-time errors despite the keyword table being declared global in the header file
// Uncomment if needed

int hashFunction(char* str) {
    // Using djb2 hash function and modulo operation
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    return (hash % NUMBER_KEYWORDS);
}

void addEntry(KeywordTable* kt, TokenName tn, char* lexeme) {
    int hash = hashFunction(lexeme);
    // printf("Hash is %d for the keyword %s\n", hash, lexeme);
    kt->KEYWORDS[hash].keywords = addToList(kt->KEYWORDS[hash].keywords, tn, lexeme);
}

Node* lookUp(KeywordTable* kt, char* lexeme) {
    int hash = hashFunction(lexeme);
    Node* trav = kt->KEYWORDS[hash].keywords;
    while (trav != NULL) {
        if (strcmp(lexeme, trav->LEXEME) == 0)
            return trav;
        trav = trav->next;
    }
    return NULL;
}

KeywordTable* initializeTable() {
    KeywordTable* kt = (KeywordTable*)malloc(sizeof(KeywordTable));
    kt->KEYWORDS = (KeywordNode*)malloc(NUMBER_KEYWORDS * sizeof(KeywordNode));

    // Initialize each keyword slot as NULL initially
    for (int i = 0; i < NUMBER_KEYWORDS; i++) {
        kt->KEYWORDS[i].keywords = NULL;
    }

    addEntry(kt, TK_WITH, "with");
    addEntry(kt, TK_PARAMETERS, "parameters");
    addEntry(kt, TK_END, "end");
    addEntry(kt, TK_WHILE, "while");
    addEntry(kt, TK_TYPE, "type");
    addEntry(kt, TK_MAIN, "_main");
    addEntry(kt, TK_GLOBAL, "global");
    addEntry(kt, TK_PARAMETER, "parameter");
    addEntry(kt, TK_LIST, "list");
    addEntry(kt, TK_INPUT, "input");
    addEntry(kt, TK_OUTPUT, "output");
    addEntry(kt, TK_INT, "int");
    addEntry(kt, TK_REAL, "real");
    addEntry(kt, TK_ENDWHILE, "endwhile");
    addEntry(kt, TK_IF, "if");
    addEntry(kt, TK_THEN, "then");
    addEntry(kt, TK_ENDIF, "endif");
    addEntry(kt, TK_READ, "read");
    addEntry(kt, TK_WRITE, "write");
    addEntry(kt, TK_RETURN, "return");
    addEntry(kt, TK_CALL, "call");
    addEntry(kt, TK_RECORD, "record");
    addEntry(kt, TK_ENDRECORD, "endrecord");
    addEntry(kt, TK_ELSE, "else");

    return kt;
}

/*** List functions ***/

// Adds a new node to the list and returns the new head of the list
Node* addToList(Node* ls, TokenName tn, char* lexeme) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->LEXEME = lexeme;
    n->TOKEN_NAME = tn;
    n->next = ls;
    return n;
}

// Searches for a lexeme in a list and returns 1 if found, otherwise 0
int searchList(Node* ls, char* lexeme) {
    Node* trav = ls;
    while (trav != NULL) {
        if (strcmp(lexeme, trav->LEXEME) == 0)
            return 1;
        trav = trav->next;
    }
    return 0;
}

/** Temporary Utility functions **/

// Prints a list and returns the number of elements in the list
int printList(Node* ls) {
    Node* trav = ls;
    int len = 0;
    if (ls == NULL) {
        printf("This slot is not occupied!\n");
        printf("\n");
        return 0;
    }

    while (trav != NULL) {
        printf("Keyword: %s ", trav->LEXEME);
        trav = trav->next;
        len++;
    }
    printf("\n\n");
    return len;
}

// Prints the hash table and calculates load factor and collisions
void printHashTable(KeywordTable* kt) {
    int empty = 0;
    int collisions = 0;
    for (int i = 0; i < NUMBER_KEYWORDS; i++) {
        int len = printList(kt->KEYWORDS[i].keywords);
        if (len == 0)
            empty++;
        if (len > 1)
            collisions += len - 1;
    }

    // Aim for as low a load factor as possible, JAVA 10 specs recommend 0.75
    printf("\nCalculating load-factor\n");
    printf("%f\n", ((float)empty) / NUMBER_KEYWORDS);

    // Aim for as few collisions as possible
    printf("\nCalculating total collisions\n");
    printf("%d\n", collisions);
}
