#pragma once
#include "LexAnalyse.h"
#include <string>
#include <map>
#include <list>

using namespace std;

#define MAXT 100

//��ʶ�����
struct IdentifierNode
{
    string content;   //����
    string describe;  //����
    int type;         //�ֱ���
    string iden_type; //��ʶ������
    int line;         //��������

    IdentifierNode() {}
    IdentifierNode(string c, string d, int t, string i, int l) : content(c), describe(d), type(t), iden_type(i), line(l) {}
};

//��ʶ����
map<string, IdentifierNode> iden_map;

//�м��
struct mid_type
{
    NormalNode *node; //����Ǳ�ʶ������, ��ָ����
    int T_num;        //������м����, ������м�������
    int isT;          //1: �м����; 0: ���ʽ��(��ʶ��/����/�����); -1:error; 2: ��

} error, null;

bool T[MAXT]; //�м����ռ��

//��Ԫʽ�м�����м����
struct CodeNode
{
    int line;
    string opt;
    string arg1, arg2;
    string result;
    CodeNode(int l, string o, string a1, string a2, string r) : line(l), opt(o), arg1(a1), arg2(a2), result(r) {}
};

//��Ԫʽ������
list<CodeNode> code;

string mid2string(mid_type m);     //mid_type�ṹ��ȡ�����ṩ��gen()������Ԫʽ�м����
void createNewIden(NormalNode *p); //�����µı�ʶ�����
void printIdentLink();             //�����ʶ����
void outputIdenLink();             //������ʶ����

/*����Ϊ�������ս���ĵݹ��ӳ���*/
void program(NormalNode *&p);                              //<����>
void main_fun(NormalNode *&p);                             //<main����>
void return_type(NormalNode *&p);                          //<��������>
void var_type(NormalNode *&p);                             //<��������>
void struct_statement(NormalNode *&p);                     //<�������>
void statements_list(NormalNode *&p);                      //<�������>
void statement(NormalNode *&p);                            //<���>
void statements_recursive(NormalNode *&p);                 //<���ݹ�>
void define_statement(NormalNode *&p);                     //<�������>
mid_type assign_default(NormalNode *&p);                   //<����ֵ>
void assign_statement(NormalNode *&p);                     //<��ֵ���>
void condition_statement(NormalNode *&p);                  //<�������>
mid_type bool_expression(NormalNode *&p);                  //<�������ʽ>
mid_type expression(NormalNode *&p);                       //<���ʽ>
mid_type items_recursive(NormalNode *&p, mid_type front);  //<��ݹ�>
mid_type item(NormalNode *&p);                             //<��>
mid_type factor_recursive(NormalNode *&p, mid_type front); //<��ʽ�ݹ�>
mid_type factor(NormalNode *&p);                           //<��ʽ>
mid_type relation_operator(NormalNode *&p);                //<��ϵ�����>
string _identifier(NormalNode *&p);                        //<��ʶ��>
void unsigned_const(NormalNode *&p);                       //<�������ų���>

mid_type newTemp();                                                 //��ȡ�µ��м����Ti
void emit(mid_type m);                                              //�����м����Ti
CodeNode &gen(string opt, string arg1, string arg2, string result); //������Ԫʽ�м����
void printCode();                                                   //�����Ԫʽ�м����
void outputCode();                                                  //������Ԫʽ�м����
