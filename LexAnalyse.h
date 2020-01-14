#pragma once
#include <string>
#include <map>

using namespace std;

// ������
#define MAIN 0   // main
#define INT 1    // int
#define RETURN 2 // return
#define IF 3     // if
#define ELSE 4   // else
#define KEY_DESC "������"

// ��ʶ��
#define IDENTIFIER 5
#define IDENTIFIER_DESC "��ʶ��"

// �����
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
#define OPE_DESC "�����"

// �޽��
#define LEFT_BRACKET 17  // (
#define RIGHT_BRACKET 18 // )
#define LEFT_BOUNDER 19  // {
#define RIGHT_BOUNDER 20 // }
#define SEMICOLON 21     // ;
#define DOLLAR 22        // $
#define CLE_OPE_DESC "�޽��"

// ����
#define CONSTANT 23 // �����������γ���
#define CONSTANT_DESC "����"

// ��������
#define INT_ERROR "���ǳ���"
#define INT_ERROR_NUM 1
#define EXCLAMATION_ERROR "!���Ų��Ϸ�"
#define EXCLAMATION_ERROR_NUM 2
#define SYMBOL_ERROR "���Ų��Ϸ�"
#define SYMBOL_ERROR_NUM 3
#define LEFT_BRACKET_ERROR "'('û�ж�Ӧ��"
#define LEFT_BRACKET_ERROR_NUM 4
#define RIGHT_BRACKET_ERROR "')'û�ж�Ӧ��"
#define RIGHT_BRACKET_ERROR_NUM 5
#define LEFT_BOUNDER_ERROR "'{'û�ж�Ӧ��"
#define LEFT_BOUNDER_ERROR_NUM 6
#define RIGHT_BOUNDER_ERROR "'}'û�ж�Ӧ��"
#define RIGHT_BOUNDER_ERROR_NUM 7
#define END_ERROR "δ��$��β"
#define END_ERROR_NUM 8

#define _NULL "null"

map<string, int> keyMap;
map<string, int> operMap;
map<string, int> limitMap;

//������ | ��ʶ�� | ����� | ����
struct NormalNode
{
    string content;   //����
    string describe;  //�����Ǳ����ֻ��Ǳ�ʶ��
    int type;         //�ֱ���
    string iden_type; //��ʶ������
    int line;         //��������
    NormalNode *next; //��һ�����
} * normalHead;       //�׽��

//������
struct ErrorNode
{
    string content;  //��������
    string describe; //��������
    int type;
    int line;        //��������
    ErrorNode *next; //��һ�����
} * errorHead;       //�׽��

void initKeyMap();                                                                 //��ʼ���������ֵ�
void initOperMap();                                                                //��ʼ��������ֵ�
void initLimitMap();                                                               //��ʼ�����Ʒ��ֵ�
void initNode();                                                                   //��ʼ�����
void createNewNode(string content, string descirbe, int type, int addr, int line); //����һ�����
void createNewError(string content, string descirbe, int type, int line);          //����һ��������
void scanner();                                                                    //����ɨ��
void printNodeLink();                                                              //��������Ϣ
void outputNodeLink();                                                             //���������Ϣ
void printErrorLink();                                                             //�����������Ϣ
void clear();                                                                      //���ս�����������