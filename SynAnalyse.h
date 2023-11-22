#pragma once
#include "LexAnalyse.h"
#include <string>
#include <map>
#include <list>

using namespace std;

#define MAXT 100

// Identifier node
struct IdentifierNode
{
    string content;   // content
    string describe;  // description
    int type;         // category code
    string iden_type; // identifier type
    int line;         // number of lines

    IdentifierNode() {}
    IdentifierNode(string c, string d, int t, string i, int l) : content(c), describe(d), type(t), iden_type(i), line(l) {}
};

// Identifier table
map<string, IdentifierNode> iden_map;

// middle point
struct mid_type
{
    NormalNode *node; // If it is an identifier or constant, it points to the node
    int T_num;        // If it is an intermediate variable, it represents the intermediate variable serial number
    int isT;          // 1: intermediate variable; 0: word node (identifier/constant/operator); -1:error; 2: empty

} error, null;

bool T[MAXT]; // Intermediate variable occupation

// Quaternary intermediate code intermediate code
struct CodeNode
{
    int line;
    string opt;
    string arg1, arg2;
    string result;
    CodeNode(int l, string o, string a1, string a2, string r) : line(l), opt(o), arg1(a1), arg2(a2), result(r) {}
};

// quaternary code chain
list<CodeNode> code;

string mid2string(mid_type m);     // The extracted content of the mid_type structure is provided to gen() to generate the quaternary intermediate code
void createNewIden(NormalNode *p); // Create a new identifier node
void printIdentLink();             // Output identifier table
void outputIdenLink();             // Export identifier table

/*The following are recursive subroutines for each non-terminal symbol*/
void program(NormalNode *&p);                              //<program>
void main_fun(NormalNode *&p);                             //<main function>
void return_type(NormalNode *&p);                          //<return type>
void var_type(NormalNode *&p);                             //<variable type>
void struct_statement(NormalNode *&p);                     //<compound statement>
void statements_list(NormalNode *&p);                      //<statement sequence>
void statement(NormalNode *&p);                            //<statement>
void statements_recursive(NormalNode *&p);                 //<Statement recursive>
void define_statement(NormalNode *&p);                     //<definition statement>
mid_type assign_default(NormalNode *&p);                   //<Assign initial value>
void assign_statement(NormalNode *&p);                     //<assignment statement>
void condition_statement(NormalNode *&p);                  //<conditional statement>
mid_type bool_expression(NormalNode *&p);                  //<Boolean expression>
mid_type expression(NormalNode *&p);                       //<expression>
mid_type items_recursive(NormalNode *&p, mid_type front);  //<item recursive>
mid_type item(NormalNode *&p);                             //<item>
mid_type factor_recursive(NormalNode *&p, mid_type front); //<factor recursive>
mid_type factor(NormalNode *&p);                           //<factor>
mid_type relation_operator(NormalNode *&p);                //<relational operator>
string _identifier(NormalNode *&p);                        //<identifier>
void unsigned_const(NormalNode *&p);                       //<Constant without sign>

mid_type newTemp();                                                 // Get the new intermediate variable Ti
void emit(mid_type m);                                              // Recycle intermediate variable Ti
CodeNode &gen(string opt, string arg1, string arg2, string result); // Generate quaternary intermediate code
void printCode();                                                   // Output the quaternary intermediate code
void outputCode();                                                  // Export quaternary intermediate code