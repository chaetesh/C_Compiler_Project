#include "LexAnalyse.h"
#include "SynAnalyse.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>

using namespace std;

int line_bak; // Backup line number before each movement of the normal node, specify the exact line number when an error occurs on the last line

// Extract content from mid_type structure to provide to gen() for generating intermediate code
string mid2string(mid_type m)
{
    if (m.isT == 1)
    {
        stringstream ss;
        ss << "T" << m.T_num;
        return ss.str();
    }
    else if (m.isT == 0)
    {
        return m.node->content;
    }
    else
    {
        return _NULL;
    }
}

// Create a new identifier node
void createNewIden(NormalNode *p)
{
    iden_map[p->content] = IdentifierNode(p->content, p->describe, p->type, "int", p->line);
}

// Print the identifier table
void printIdentLink()
{
    cout << "****************************Identifier Table*****************************" << endl
         << endl;
    cout << setw(15) << "Content"
         << setw(15) << "Description"
         << "\t"
         << setw(3) << "Type Code"
         << "\t"
         << setw(8) << "Identifier Type"
         << "\t"
         << "Line Number" << endl;

    for (map<string, IdentifierNode>::iterator it = iden_map.begin(); it != iden_map.end(); it++)
    {
        cout << setw(15) << it->second.content
             << setw(15) << it->second.describe << "\t"
             << setw(3) << it->second.type << "\t"
             << setw(8) << it->second.iden_type << "\t"
             << it->second.line << endl;
    }
    cout << endl
         << endl;
}

// Export the identifier table
void outputIdenLink()
{
    ofstream fout("identifiers.txt");
    if (!fout)
    {
        cout << "Failed to open identifiers.txt!" << endl;
        return;
    }
    fout << "*****************************Identifier Table******************************" << endl
         << endl;
    fout << "Content"
         << "\t"
         << setw(10) << "Description"
         << "\t"
         << setw(3) << "Type Code"
         << "\t"
         << setw(8) << "Identifier Type"
         << "\t"
         << "Line Number" << endl;

    for (map<string, IdentifierNode>::iterator p = iden_map.begin(); p != iden_map.end(); p++)
    {
        fout << p->second.content << "\t"
             << setw(10) << p->second.describe << "\t"
             << setw(3) << p->second.type << "\t"
             << setw(8) << p->second.iden_type << "\t\t"
             << p->second.line << endl;
    }
    fout << endl;

    cout << "identifiers.txt updated!" << endl;
    fout.close();
}

/* The following are recursive subprograms for each non-terminal symbol */
// <Program>
void program(NormalNode *&p)
{
    if (p)
    {
        // Matches the first set
        if (p->content == "int" || true)
        {
            main_fun(p);
            if (p)
            {
                if (p->content == "$")
                {
                    line_bak = p->line;
                    p = p->next;
                    cout << "Syntax analysis completed!" << endl;
                    return;
                }
            }
            else
            {
                cout << "Line " << line_bak << " Error: The program should end with $" << endl;
            }
        }
        else
        {
            cout << "Line " << p->line << " Error: The program should start with int" << endl;
        }
    }
    else
    {
        cout << "The program cannot be empty" << endl;
    }
}

// <Main Function>
void main_fun(NormalNode *&p)
{
    if (p)
    {
        if (p->content == "int")
        {
            return_type(p);
            if (p)
            {
                // Matches the first set
                if (p->content == "main")
                {
                main_fun2:
                    line_bak = p->line;
                    p = p->next;
                    if (p)
                    {
                        if (p->content == "(")
                        {
                        main_fun1:
                            line_bak = p->line;
                            p = p->next;
                            if (p)
                            {
                                if (p->content == ")")
                                {
                                    line_bak = p->line;
                                    p = p->next;
                                    struct_statement(p);
                                }
                                else
                                {
                                    cout << "Line " << p->line << " Error: " << p->content << " should be \")\"" << endl;
                                }
                            }
                            else
                            {
                                cout << "Line " << line_bak << " Error: ( should be paired with )" << endl;
                            }
                        }
                        else
                        {
                            cout << "Line " << p->line << " Error: The main function should be followed by \"(\"" << endl;
                        }
                    }
                    else
                    {
                        cout << "Line " << line_bak << " Error: The main function should be followed by (" << endl;
                    }
                }
                // Skips the error of omitting the main function name
                else if (p->content == "(")
                {
                    cout << "Line " << p->line << " Error: The main function should have the function name main" << endl;
                    goto main_fun1;
                }
                // Skips the error of misspelling the main function name
                else if (p->next && p->next->content == "(")
                {
                    cout << "Line " << p->line << " Error: The main function should have the function name main" << endl;
                    goto main_fun2;
                }
                else
                {
                    cout << "Line " << p->line << " Error: The main function should have the function name main" << endl;
                }
            }
            else
            {
                cout << "Line " << line_bak << " Error: The main function needs a function name" << endl;
            }
        }
        else
        {
            cout << "Line " << p->line << " Error: The main function should have the return type int" << endl;
        }
    }
    else
    {
        cout << "Line " << line_bak << " Error: The main function needs a return type" << endl;
    }
}

// <Return Type>
void return_type(NormalNode *&p)
{
    if (p)
    {
        if (p->content == "int")
        {
            var_type(p);
        }
        else
        {
            cout << "Line " << p->line << " Error: The return type should be int" << endl;
        }
    }
    else
    {
        cout << "Line " << line_bak << " Error: The function needs a return type" << endl;
    }
}

// <Variable Type>
void var_type(NormalNode *&p)
{
    if (p)
    {
        if (p->content == "int")
        {
            line_bak = p->line;
            p = p->next;
            return;
        }
        else
        {
            cout << "Line " << p->line << " Error: The variable type should be int" << endl;
        }
    }
    else
    {
        cout << "Line " << line_bak << " Error: The variable type is needed at this point" << endl;
    }
}

// <Compound Statement>
void struct_statement(NormalNode *&p)
{
    if (p)
    {
        if (p->content == "{")
        {
            line_bak = p->line;
            p = p->next;
            statements_list(p);
            if (p)
            {
                if (p->content == "}")
                {
                    line_bak = p->line;
                    p = p->next;
                    return;
                }
                else
                {
                    cout << "Line " << p->line << " Error: " << p->content << " should be \"}\"" << endl;
                }
            }
            else
            {
                cout << "Line " << line_bak << " Error: The symbol { is needed at this point" << endl;
            }
        }
        else
        {
            cout << "Line " << p->line << " Error: The compound statement should start with {" << endl;
        }
    }
    else
    {
        cout << "Line " << line_bak << " Error: The symbol { is needed at this point" << endl;
    }
}

// <Statement Sequence>
void statements_list(NormalNode *&p)
{
    if (p)
    {
        if (p->content == "int" || p->content == "if" || p->content == "{" || p->content == "return" || p->describe == IDENTIFIER_DESC)
        {
            statement(p);
            statements_recursive(p);
        }
        else if (p->content == "}")
        {
            return;
        }
        else
        {
            cout << p->content << endl;
            cout << "Line " << p->line << " Error: Invalid statement header" << endl;
        }
    }
    else
    {
        cout << "Line " << line_bak << " Error: Statement header is needed at this point" << endl;
    }
}

// <Statement>
void statement(NormalNode *&p)
{
    if (p)
    {
        if (p->content == "int")
        {
            define_statement(p);
        }
        else if (p->describe == IDENTIFIER_DESC)
        {
            assign_statement(p);
        }
        else if (p->content == "if")
        {
            condition_statement(p);
        }
        else if (p->content == "{")
        {
            struct_statement(p);
        }
        else if (p->content == "return")
        {
            line_bak = p->line;
            p = p->next;
            expression(p);
            if (p)
            {
                if (p->content == ";")
                {
                    line_bak = p->line;
                    p = p->next;
                    return;
                }
                else
                {
                    cout << "Line " << p->line << " Error: " << p->content << " should be \";\"" << endl;
                }
            }
            else
            {
                cout << "Line " << line_bak << " Error: \";\" is expected at this point" << endl;
            }
        }
        else
        {
            cout << "Line " << p->line << " Error: No valid statement header" << endl;
        }
    }
    else
    {
        cout << "Line " << line_bak << " Error: At least one statement is needed in the statement sequence" << endl;
    }
}

// <Statement Recursive>
void statements_recursive(NormalNode *&p)
{
    if (p)
    {
        if (p->content == "int" || p->describe == IDENTIFIER_DESC || p->content == "if" || p->content == "{" || p->content == "return" || p->describe == IDENTIFIER_DESC)
        {
            statement(p);
            statements_recursive(p);
        }
        else if (p->content == "}")
        {
            return;
        }
        else
        {
            cout << "Line " << p->line << " Error: " << p->content << " is not reasonable, it should be a statement header or }" << endl;
        }
    }
    else
    {
        cout << "Line " << line_bak << " Error: Incomplete program" << endl;
    }
}

// <Definition Statement>
void define_statement(NormalNode *&p)
{
    if (p)
    {
        if (p->content == "int")
        {
            var_type(p);

            NormalNode *bak = p; // Backup identifier position
            _identifier(p);

            if (bak)
            { // Declaration, assign identifier type
                if (iden_map.find(bak->content) == iden_map.end())
                {
                    createNewIden(bak);
                    bak->iden_type = "int";
                    // Declaration of identifier    Quadruple
                    gen("assign", "int", "_", bak->content);
                }
                else
                {
                    cout << "Line " << p->line << " Error: Identifier " << p->content << " has already been declared" << endl;
                }
            }
            else
            {
                cout << "Line " << line_bak << " Error: Identifier does not exist, cannot be declared" << endl;
            }

            mid_type _it;
            _it.isT = 0;
            _it.node = bak;

            mid_type _e = assign_default(p);
            if (_e.isT == -1)
                return;
            if (p)
            {
                if (p->content == ";")
                {
                    if (_e.isT != 2) // If the return intermediate is not empty
                    {
                        gen("=", mid2string(_e), "_", mid2string(_it));

                        // Recycle _e
                        emit(_e);
                    }
                    line_bak = p->line;
                    p = p->next;
                    return;
                }
                else
                {
                    cout << "Line " << p->line << " Error: " << p->content << " should be \";\"" << endl;
                }
            }
            else
            {
                cout << "Line " << line_bak << " Error: \";\" is expected at this point" << endl;
            }
        }
        else
        {
            cout << "Line " << p->line << " Error: No valid statement header" << endl;
        }
    }
    else
    {
        cout << "Line " << line_bak << " Error: Definition statement should start with a variable type" << endl;
    }
}

// <Assign Default Value>
mid_type assign_default(NormalNode *&p)
{
    if (p)
    {
        mid_type _e;
        if (p->content == "=")
        {
            line_bak = p->line;
            p = p->next;
            _e = expression(p);
            if (_e.isT == -1)
                return error;
            else
                return _e;
        }
        else if (p->content == ";")
        {
            return null;
        }
        else
        {
            cout << "Line " << p->line << " Error: At this point, an initial value should be assigned to the identifier or end with ;" << endl;
        }
    }
    else
    {
        cout << "Line " << line_bak << " Error: Incomplete program" << endl;
    }
    return error;
}

// <Assignment Statement>
void assign_statement(NormalNode *&p)
{
    if (p)
    {
        if (p->describe == IDENTIFIER_DESC)
        {
            // Check if the identifier has been declared
            if (iden_map.find(p->content) == iden_map.end())
            {
                cout << "Line " << p->line << " Error: Identifier " << p->content << " has not been declared" << endl;
            }

            string _i = _identifier(p); // Identifier parameter
            if (p)
            {
                if (p->content == "=")
                {
                    line_bak = p->line;
                    p = p->next;
                    mid_type _e = expression(p); // Expression parameter
                    if (_e.isT == -1)
                        return;
                    if (p)
                    {
                        if (p->content == ";")
                        {
                            line_bak = p->line;
                            p = p->next;

                            gen("=", mid2string(_e), "_", _i);

                            // Recycle _e
                            emit(_e);

                            return;
                        }
                        else
                        {
                            cout << "Line " << p->line << " Error: " << p->content << " should be \";\"" << endl;
                        }
                    }
                    else
                    {
                        cout << "Line " << line_bak << " Error: \";\" is expected at this point" << endl;
                    }
                }
                else
                {
                    cout << "Line " << p->line << " Error: " << p->content << " should be \"=\"" << endl;
                }
            }
            else
            {
                cout << "Line " << line_bak << " Error: + is expected at this point" << endl;
            }
        }
        else
        {
            cout << "Line " << p->line << " Error: Identifier is expected at this point" << endl;
        }
    }
    else
    {
        cout << "Line " << line_bak << " Error: Incomplete program" << endl;
    }
}

// <Conditional Statement>
void condition_statement(NormalNode *&p)
{
    if (p)
    {
        if (p->content == "if")
        {
            line_bak = p->line;
            p = p->next;
            if (p)
            {
                if (p->content == "(")
                {
                    line_bak = p->line;
                    p = p->next;
                    mid_type _b_e = bool_expression(p);
                    if (_b_e.isT == -1)
                        return;
                    if (p)
                    {
                        if (p->content == ")")
                        {
                            line_bak = p->line;
                            p = p->next;

                            CodeNode &else_from = gen("jne", mid2string(_b_e), "_", "");

                            // Recycle _b_e
                            emit(_b_e);

                            struct_statement(p);
                            CodeNode &if_end_to = gen("j", "_", "_", "");
                            if (p)
                            {
                                if (p->content == "else")
                                {
                                    // Backfill else_from
                                    stringstream ss;
                                    ss << "(" << code.back().line + 1 << ")";
                                    else_from.result = ss.str();

                                    line_bak = p->line;
                                    p = p->next;
                                    struct_statement(p);

                                    // Backfill if_end_to
                                    ss.str("");
                                    ss << "(" << code.back().line + 1 << ")";
                                    if_end_to.result = ss.str();
                                }
                                else
                                {
                                    cout << "Line " << p->line << " Error: " << p->content << " should be else" << endl;
                                }
                            }
                            else
                            {
                                cout << "Line " << line_bak << " Error: There should be else at this point" << endl;
                            }
                        }
                        else
                        {
                            cout << "Line " << p->line << " Error: " << p->content << " should be \")\"" << endl;
                        }
                    }
                    else
                    {
                        cout << "Line " << line_bak << " Error: There should be )" << endl;
                    }
                }
                else
                {
                    cout << "Line " << p->line << " Error: " << p->content << " should be \"(\"" << endl;
                }
            }
            else
            {
                cout << "Line " << line_bak << " Error: There should be (" << endl;
            }
        }
        else
        {
            cout << "Line " << p->line << " Error: " << p->content << " should be if" << endl;
        }
    }
    else
    {
        cout << "Line " << line_bak << " Error: There should be if at this point" << endl;
    }
}

// <Boolean Expression>
mid_type bool_expression(NormalNode *&p)
{
    if (p)
    {
        if (p->describe == IDENTIFIER_DESC || p->describe == CONSTANT_DESC || p->content == "(")
        {
            mid_type _e1 = expression(p);
            mid_type _r = relation_operator(p);
            mid_type _e2 = expression(p);
            if (_e1.isT == -1 || _r.isT == -1 || _e2.isT == -1)
                return error;

            mid_type res = newTemp();
            gen(mid2string(_r), mid2string(_e1), mid2string(_e2), mid2string(res));
            return res;
        }
        else
        {
            cout << "Line " << p->line << " Error: " << p->content << " should be an expression" << endl;
        }
    }
    else
    {
        cout << "Line " << line_bak << " Error: There should be an expression at this point" << endl;
    }
    return error;
}

// <Expression>
mid_type expression(NormalNode *&p)
{
    if (p)
    {
        if (p->describe == IDENTIFIER_DESC || p->describe == CONSTANT_DESC || p->content == "(")
        {
            mid_type _it = item(p);
            if (_it.isT == -1)
                return error;
            else
                return items_recursive(p, _it);
        }
        else
        {
            cout << "Line " << p->line << " Error: " << p->content << " should be a term" << endl;
        }
    }
    else
    {
        cout << "Line " << line_bak << " Error: There should be a term at this point" << endl;
    }
    return error;
}

// <Items Recursive>
mid_type items_recursive(NormalNode *&p, mid_type front)
{
    if (p)
    {
        if (p->content == "+" || p->content == "-")
        {
            string op_bak = p->content;
            line_bak = p->line;
            p = p->next;

            mid_type back = item(p);
            if (back.isT == -1)
                return error;

            mid_type res = newTemp();
            // Generate quadruple
            gen(op_bak, mid2string(front), mid2string(back), mid2string(res));

            // Recycle front and back
            emit(front);
            emit(back);

            return items_recursive(p, res);
        }
        else if (p->content == ";" || p->content == ")" || p->content == "==" || p->content == "<" || p->content == "<=" || p->content == ">" || p->content == ">=" || p->content == "!=")
        {
            return front;
        }
        else
        {
            cout << "Line " << p->line << " Error: There should be more terms or the end at this point" << endl;
        }
    }
    else
    {
        cout << "Line " << line_bak << " Error: The term is incomplete" << endl;
    }
    return error;
}

// <Term>
mid_type item(NormalNode *&p)
{
    if (p)
    {
        if (p->describe == IDENTIFIER_DESC || p->describe == CONSTANT_DESC || p->content == "(")
        {
            mid_type _it = factor(p);
            if (_it.isT == -1)
                return error;
            else
                return factor_recursive(p, _it);
        }
        else
        {
            cout << "Line " << p->line << " Error: " << p->content << " should be a factor" << endl;
        }
    }
    else
    {
        cout << "Line " << line_bak << " Error: There should be a factor at this point" << endl;
    }
    return error;
}

// <Factor Recursive>
mid_type factor_recursive(NormalNode *&p, mid_type front)
{
    if (p)
    {
        if (p->content == "*" || p->content == "/")
        {
            string op_bak = p->content;
            line_bak = p->line;
            p = p->next;
            mid_type back = factor(p);
            if (back.isT == -1)
                return error;

            mid_type res = newTemp();
            gen(op_bak, mid2string(front), mid2string(back), mid2string(res));

            // Recycle front and back
            emit(front);
            emit(back);

            return factor_recursive(p, res);
        }
        else if (p->content == "+" || p->content == "-" || p->content == ";" || p->content == ")" || p->content == "==" || p->content == "<" || p->content == "<=" || p->content == ">" || p->content == ">=" || p->content == "!=")
        {
            return front;
        }
        else
        {
            cout << "Line " << p->line << " Error: There should be more factors or the end of the polynomial (perhaps missing ;)" << endl;
        }
    }
    else
    {
        cout << "Line " << line_bak << " Error: The factor is incomplete" << endl;
    }
    return error;
}

// <Factor>
mid_type factor(NormalNode *&p)
{
    if (p)
    {
        if (p->describe == IDENTIFIER_DESC)
        {
            NormalNode *p_bak = p;

            // Check if the identifier has been declared
            if (iden_map.find(p->content) == iden_map.end())
            {
                cout << "Line " << p->line << " Error: Identifier " << p->content << " has not been declared" << endl;
            }

            _identifier(p);

            mid_type ans;
            ans.node = p_bak;
            ans.isT = 0;
            return ans;
        }
        else if (p->describe == CONSTANT_DESC)
        {
            NormalNode *p_bak = p;

            unsigned_const(p);

            mid_type ans;
            ans.node = p_bak;
            ans.isT = 0;
            return ans;
        }
        else if (p->content == "(")
        {
            line_bak = p->line;
            p = p->next;
            mid_type ans = expression(p);
            if (p)
            {
                if (p->content == ")")
                {
                    line_bak = p->line;
                    p = p->next;
                    return ans;
                }
                else
                {
                    cout << "Line " << p->line << " Error: " << p->content << " should be \")\"" << endl;
                }
            }
            else
            {
                cout << "Line " << line_bak << " Error: There should be )" << endl;
            }
        }
        else
        {
            cout << "Line " << p->line << " Error: " << p->content << " as a factor is not valid" << endl;
        }
    }
    else
    {
        cout << "Line " << line_bak << " Error: The factor is incomplete" << endl;
    }
    return error;
}

// <Relation Operator>
mid_type relation_operator(NormalNode *&p)
{
    if (p)
    {
        if (p->content == "==" || p->content == "<" || p->content == "<=" || p->content == ">" || p->content == ">=" || p->content == "!=")
        {
            mid_type res;
            res.isT = 0;
            res.node = p;

            line_bak = p->line;
            p = p->next;

            return res;
        }
        else
        {
            cout << "Line " << p->line << " Error: " << p->content << " should be a relational operator" << endl;
        }
    }
    else
    {
        cout << "Line " << line_bak << " Error: There should be a relational operator at this point" << endl;
    }
    return error;
}

// <Identifier>
string _identifier(NormalNode *&p)
{
    if (p)
    {
        if (p->describe == IDENTIFIER_DESC)
        {
            line_bak = p->line;
            NormalNode *p_bak = p;
            p = p->next;
            return p_bak->content;
        }
        else
        {
            cout << "Line " << p->line << " Error: " << p->content << " should be an identifier" << endl;
        }
    }
    else
    {
        cout << "Line " << line_bak << " Error: There should be an identifier at this point" << endl;
    }
    return _NULL;
}

// <Unsigned Constant>
void unsigned_const(NormalNode *&p)
{
    if (p)
    {
        if (p->describe == CONSTANT_DESC)
        {
            line_bak = p->line;
            p = p->next;
            return;
        }
        else
        {
            cout << "Line " << p->line << " Error: " << p->content << " should be a constant" << endl;
        }
    }
    else
    {
        cout << "Line " << line_bak << " Error: There should be a constant at this point" << endl;
    }
}

// Get a new temporary variable Ti
mid_type newTemp()
{
    for (int i = 0; i < MAXT; i++)
    {
        if (T[i] == false)
        {
            T[i] = true;
            mid_type ans;
            ans.node = NULL;
            ans.isT = 1;
            ans.T_num = i;
            return ans;
        }
    }
    return error;
}

// Recycle temporary variable Ti
void emit(mid_type m)
{
    // If it is a temporary variable
    if (m.isT == 1)
    {
        T[m.T_num] = false;
    }
}

// Generate quadruple intermediate code
CodeNode &gen(string opt, string arg1, string arg2, string result)
{
    static int static_line = 0;
    code.push_back(CodeNode(++static_line, opt, arg1, arg2, result));
    return code.back();
}

// Print quadruple intermediate code
void printCode()
{
    cout << "Intermediate code is as follows: " << endl;
    for (list<CodeNode>::iterator it = code.begin(); it != code.end(); ++it)
    {
        cout << "(" << it->line << ")"
             << "\t" << it->opt << "\t" << it->arg1 << "\t" << it->arg2 << "\t" << it->result << endl;
    }
}

// Export quadruple intermediate code
void outputCode()
{
    ofstream fout("midCode.txt");
    if (!fout)
    {
        cout << "Failed to open midCode.txt!" << endl;
        return;
    }
    for (list<CodeNode>::iterator it = code.begin(); it != code.end(); ++it)
    {
        fout << "(" << it->line << ")"
             << "\t" << it->opt << "\t" << it->arg1 << "\t" << it->arg2 << "\t" << it->result << endl;
    }

    fout.close();
}