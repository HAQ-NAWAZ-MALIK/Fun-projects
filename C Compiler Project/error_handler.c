// This file manages errors during semantic analysis

#include "interface.h"
#include "error_handler.h"
#include "type_checker.h"
#include <string.h>

// Function to initialize an error list
ErrorList* initializeErrorList() {
    ErrorList* errorList = (ErrorList*)malloc(sizeof(ErrorList));
    errorList->head = NULL;
    errorList->tail = NULL;
    errorList->MESSAGE_MAX_LENGTH = ERROR_MAX_LENGTH;
    return errorList;
}

// Function to create an error with a specific line number and message
Error* generateError(int lineNumber, int iterativeLineEnd, char* errorMessage) {
    Error* error = (Error*)malloc(sizeof(Error));
    error->LINE_NUMBER = lineNumber;
    error->ITERATIVE_LINE_END = iterativeLineEnd;
    error->ERROR_MESSAGE = errorMessage;
    error->next = NULL;
    return error;
}

// Function to add an error to the error list
void addErrorToList(ErrorList* errorList, int lineNumber, char* errorMessage) {
    // Ensure the error has not been reported previously
    Error* current = errorList->head;
    while (current != NULL) {
        if (strcmp(current->ERROR_MESSAGE, errorMessage) == 0 && current->LINE_NUMBER == lineNumber) {
            return;
        }
        current = current->next;
    }

    Error* error = generateError(lineNumber, -1, errorMessage);

    // Add the error to the list if it's empty
    if (errorList->head == NULL) {
        errorList->head = error;
        errorList->tail = error;
    } else {
        errorList->tail->next = error;
        errorList->tail = errorList->tail->next;
    }
}

void addIterativeErrorToList(ErrorList* errorList, int lineStart, int lineEnd, char* errorMessage) {
    Error* error = generateError(lineStart, lineEnd, errorMessage);

    // Add the error to the list if it's empty
    if (errorList->head == NULL) {
        errorList->head = error;
        errorList->tail = error;
    } else {
        errorList->tail->next = error;
        errorList->tail = errorList->tail->next;
    }
}

// Function to print all errors in the error list
void printErrors(ErrorList* errorList) {
    Error* current = errorList->head;

    if (current == NULL) {
        printf("No errors reported during Semantic Analysis\n");
        printf("Code compiles successfully\n");
        return;
    }

    while (current != NULL) {
        if (current->ITERATIVE_LINE_END == -1) {
            printf("Line %d: %s\n", current->LINE_NUMBER, current->ERROR_MESSAGE);
        } else {
            printf("Line %d-%d: %s\n", current->LINE_NUMBER, current->ITERATIVE_LINE_END, current->ERROR_MESSAGE);
        }
        current = current->next;
    }
}

// Function to report a type mismatch error
void throwTypeMismatchError(Token* lhsType, Token* rhsType, ErrorList* errorList, int lineNumber) {
    char* message = (char*)malloc(sizeof(char) * errorList->MESSAGE_MAX_LENGTH);
    sprintf(message, "Types %s and %s are not compatible for this operation\n", getDataType(lhsType), getDataType(rhsType));
    addErrorToList(errorList, lineNumber, message);
}

// Function to report a missing declaration error
void throwMissingDeclarationError(Token* errorVariable, ErrorList* errorList) {
    char* message = (char*)malloc(sizeof(char) * errorList->MESSAGE_MAX_LENGTH);
    sprintf(message, "The variable %s is not declared\n", errorVariable->LEXEME);
    addErrorToList(errorList, errorVariable->LINE_NO, message);
}

// Function to report multiple definitions of an identifier
void throwMultipleDefinitionsError(Token* errorIdentifier, ErrorList* errorList) {
    char* message = (char*)malloc(sizeof(char) * errorList->MESSAGE_MAX_LENGTH);
    sprintf(message, "The identifier %s is declared more than once\n", errorIdentifier->LEXEME);
    addErrorToList(errorList, errorIdentifier->LINE_NO, message);
}

// Function to report a global identifier conflict
void throwClashingGlobalDefinitionError(Token* errorIdentifier, ErrorList* errorList) {
    char* message = (char*)malloc(sizeof(char) * errorList->MESSAGE_MAX_LENGTH);
    sprintf(message, "The identifier %s is global and cannot be declared again\n", errorIdentifier->LEXEME);
    addErrorToList(errorList, errorIdentifier->LINE_NO, message);
}

// Function to report a missing function definition
void throwMissingFunctionDefinitionError(Token* errorFunCall, ErrorList* errorList) {
    char* message = (char*)malloc(sizeof(char) * errorList->MESSAGE_MAX_LENGTH);
    sprintf(message, "The function %s is undefined\n", errorFunCall->LEXEME);
    addErrorToList(errorList, errorFunCall->LINE_NO, message);
}

// Function to report a missing record definition
void throwMissingRecordDefinitionError(Token* errorRecord, ErrorList* errorList) {
    char* message = (char*)malloc(sizeof(char) * errorList->MESSAGE_MAX_LENGTH);
    sprintf(message, "The record %s is undefined\n", errorRecord->LEXEME);
    addErrorToList(errorList, errorRecord->LINE_NO, message);
}

// Function to report an incorrect number of input arguments
void throwInvalidNumberOfInputArgsError(Token* errorFunCall, int actualNumber, int expectedNumber, ErrorList* errorList) {
    char* message = (char*)malloc(sizeof(char) * errorList->MESSAGE_MAX_LENGTH);
    sprintf(message, "The number of input arguments passed is %d; it should be %d\n", actualNumber, expectedNumber);
    addErrorToList(errorList, errorFunCall->LINE_NO, message);
}

// Function to report an incorrect number of output arguments
void throwInvalidNumberOfOutputArgsError(Token* errorFunCall, int actualNumber, int expectedNumber, ErrorList* errorList) {
    char* message = (char*)malloc(sizeof(char) * errorList->MESSAGE_MAX_LENGTH);
    sprintf(message, "The number of output arguments passed is %d; it should be %d\n", actualNumber, expectedNumber);
    addErrorToList(errorList, errorFunCall->LINE_NO, message);
}

// Function to report a type mismatch in input arguments
void throwInputArgumentTypeMismatchError(Token* errorFunCall, Token* typeExpected, Token* typePassed, int index, ErrorList* errorList) {
    char* message = (char*)malloc(sizeof(char) * errorList->MESSAGE_MAX_LENGTH);
    sprintf(message, "In inputArgs, the type at index %d should be %s rather than %s\n", index, typeExpected->LEXEME, typePassed->LEXEME);
    addErrorToList(errorList, errorFunCall->LINE_NO, message);
}

// Function to report a type mismatch in output arguments
void throwOutputArgumentTypeMismatchError(Token* errorFunCall, Token* typeExpected, Token* typeReceived, int index, ErrorList* errorList) {
    char* message = (char*)malloc(sizeof(char) * errorList->MESSAGE_MAX_LENGTH);
    sprintf(message, "In outputArgs, the type at index %d should be %s rather than %s\n", index, typeExpected->LEXEME, typeReceived->LEXEME);
    addErrorToList(errorList, errorFunCall->LINE_NO, message);
}

// Function to report an incorrect number of return variables
void throwInvalidNumberOfReturnVariablesError(int lineNumber, int actualNumber, int expectedNumber, ErrorList* errorList) {
    char* message = (char*)malloc(sizeof(char) * errorList->MESSAGE_MAX_LENGTH);
    sprintf(message, "The number of variables being returned is %d, instead of %d\n", actualNumber, expectedNumber);
    addErrorToList(errorList, lineNumber, message);
}

// Function to report a return type mismatch
void throwReturnTypeMismatchError(Token* errorId, Token* typeReturned, Token* typeExpected, ErrorList* errorList) {
    char* message = (char*)malloc(sizeof(char) * errorList->MESSAGE_MAX_LENGTH);
    sprintf(message, "The type %s of the variable being returned %s does not match the expected type %s\n", typeReturned->LEXEME, errorId->LEXEME, typeExpected->LEXEME);
    addErrorToList(errorList, errorId->LINE_NO, message);
}

// Function to report a missing iteration update in a while loop
void throwNoIterationUpdateError(int lineStart, int lineEnd, ErrorList* errorList) {
    char* message = (char*)malloc(sizeof(char) * errorList->MESSAGE_MAX_LENGTH);
    sprintf(message, "None of the variables in the condition of the while loop are updated");
    addIterativeErrorToList(errorList, lineStart, lineEnd, message);
}

// Function to report a recursive function call
void throwRecursiveFunctionCallError(Token* errorFunCall, ErrorList* errorList) {
    char* message = (char*)malloc(sizeof(char) * errorList->MESSAGE_MAX_LENGTH);
    sprintf(message, "The function call is recursive\n");
    addErrorToList(errorList, errorFunCall->LINE_NO, message);
}
