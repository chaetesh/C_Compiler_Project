#pragma once
#include <string>
#include <map>

using namespace std;

// reserved words
#define MAIN 0   // main
#define INT 1    // int
#define RETURN 2 // return
#define IF 3     // if
#define ELSE 4   // else
#define KEY_DESC "Reserved Word"

// identifier
#define IDENTIFIER 5
#define IDENTIFIER_DESC "identifier"

// operator
#define ADD 6         // +
#define SUB 7         // -
#define MUL 8         // *
#define DIV 9         // /
#define EQUAL 10      // ==
#define LESS_THAN 11  // <
#define LESS_EQUAL 12 // <=
#define GRT_THAN 13   // >
#define GRT_EQUAL 14  // >=
#define NOT_EQUAL 15  // !=
#define ASSIGN 16     // =
#define OPE_DESC "operator"

// limit mark
#define LEFT_BRACKET 17  // (
#define RIGHT_BRACKET 18 // )
#define LEFT_BOUNDER 19  // {
#define RIGHT_BOUNDER 20 // }
#define SEMICOLON 21     // ;
#define DOLLAR 22        // $
#define CLE_OPE_DESC "limit mark"

// constant
#define CONSTANT 23 // Unsigned integer constant
#define CONSTANT_DESC "Constant"

// error type
#define INT_ERROR "Not a constant"
#define INT_ERROR_NUM 1
#define EXCLAMATION_ERROR "!Illegal symbol"
#define EXCLAMATION_ERROR_NUM 2
#define SYMBOL_ERROR "Illegal symbol"
#define SYMBOL_ERROR_NUM 3
#define LEFT_BRACKET_ERROR "'('No corresponding item"
#define LEFT_BRACKET_ERROR_NUM 4
#define RIGHT_BRACKET_ERROR "')' has no corresponding entry"
#define RIGHT_BRACKET_ERROR_NUM 5
#define LEFT_BOUNDER_ERROR "'{' has no corresponding item"
#define LEFT_BOUNDER_ERROR_NUM 6
#define RIGHT_BOUNDER_ERROR "'}' has no corresponding item"
#define RIGHT_BOUNDER_ERROR_NUM 7
#define END_ERROR "Does not end with $"
#define END_ERROR_NUM 8

#define _NULL "null"

map<string, int> keyMap;
map<string, int> operMap;
map<string, int> limitMap;

// Reserved words | identifiers | operators | constants
struct NormalNode
{
    string content;   // content
    string describe;  // Is the description a reserved word or an identifier?
    int type;         // category code
    string iden_type; // identifier type
    int line;         // number of lines
    NormalNode *next; // Next node
} *normalHead;        // Head node

// error node
struct ErrorNode
{
    string content;  // error content
    string describe; // error description
    int type;
    int line;        // number of lines
    ErrorNode *next; // Next node
} *errorHead;        // First node

void initKeyMap();                                                                 // Initialize the reserved word dictionary
void initOperMap();                                                                // Initialize operator dictionary
void initLimitMap();                                                               // Initialize limiter dictionary
void initNode();                                                                   // Initialize node
void createNewNode(string content, string descirbe, int type, int addr, int line); // Insert a node
void createNewError(string content, string descirbe, int type, int line);          // Insert an error node
void scanner();                                                                    // Word scanning
void printNodeLink();                                                              // Output node information
void outputNodeLink();                                                             // Export node information
void printErrorLink();                                                             // Output error node information
void clear();                                                                      // Recycle node chain and error chain