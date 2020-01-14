#include "LexAnalyse.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <string>

using namespace std;

//��ʼ���������ֵ�
void initKeyMap()
{
    keyMap.clear();
    keyMap["main"] = MAIN;
    keyMap["int"] = INT;
    keyMap["return"] = RETURN;
    keyMap["if"] = IF;
    keyMap["else"] = ELSE;
}

//��ʼ��������ֵ�
void initOperMap()
{
    operMap.clear();
    operMap["+"] = ADD;
    operMap["-"] = SUB;
    operMap["*"] = MUL;
    operMap["/"] = DIV;
    operMap[">"] = GRT_THAN;
    operMap[">="] = GRT_EQUAL;
    operMap["<"] = LESS_THAN;
    operMap["<="] = LESS_EQUAL;
    operMap["!="] = NOT_EQUAL;
    operMap["=="] = EQUAL;
    operMap["="] = ASSIGN;
}

//��ʼ�����Ʒ��ֵ�
void initLimitMap()
{
    limitMap["{"] = LEFT_BOUNDER;
    limitMap["}"] = RIGHT_BOUNDER;
    limitMap["("] = LEFT_BRACKET;
    limitMap[")"] = RIGHT_BRACKET;
    limitMap[";"] = SEMICOLON;
}

//��ʼ�����
void initNode()
{
    normalHead = new NormalNode();
    normalHead->content = "";
    normalHead->describe = "";
    normalHead->type = -1;
    normalHead->iden_type = "";
    normalHead->line = -1;
    normalHead->next = NULL;

    errorHead = new ErrorNode();
    errorHead->content = "";
    errorHead->describe = "";
    errorHead->line = -1;
    errorHead->next = NULL;

    cout << "��ʼ�����ʽ�㡢���������" << endl;
}

//����һ�����
void createNewNode(string content, string descirbe, int type, int line)
{
    NormalNode *p = normalHead;
    NormalNode *temp = new NormalNode();

    while (p->next)
    {
        p = p->next;
    }

    temp->content = content;
    temp->describe = descirbe;
    temp->type = type;
    temp->iden_type = "";
    temp->line = line;
    temp->next = NULL;

    p->next = temp;
}

//����һ��������
void createNewError(string content, string descirbe, int type, int line)
{
    ErrorNode *p = errorHead;
    ErrorNode *temp = new ErrorNode();

    temp->content = content;
    temp->describe = descirbe;
    temp->type = type;
    temp->line = line;
    temp->next = NULL;
    while (p->next)
    {
        p = p->next;
    }
    p->next = temp;
}

//��������Ϣ
void printNodeLink()
{
    cout << "*****************************������******************************" << endl
         << endl;
    cout << setw(15) << "����"
         << setw(15) << "����"
         << "\t"
         << setw(3) << "�ֱ���"
         << "\t"
         << setw(8) << "��ʶ������"
         << "\t"
         << "�к�" << endl;
    NormalNode *p = normalHead;
    p = p->next;
    while (p)
    {
        cout << setw(15) << p->content
             << setw(15) << p->describe << "\t"
             << setw(3) << p->type << "\t"
             << setw(8) << p->iden_type << "\t"
             << p->line << endl;

        p = p->next;
    }
    cout << endl;
}

//���������Ϣ
void outputNodeLink()
{
    ofstream fout("words.txt");
    if (!fout)
    {
        cout << "words.txt��ʧ��!" << endl;
        return;
    }
    fout << "*****************************������******************************" << endl
         << endl;
    fout << "����"
         << "\t"
         << setw(10) << "����"
         << "\t"
         << setw(3) << "�ֱ���"
         << "\t"
         << setw(8) << "��ʶ������"
         << "\t"
         << "�к�" << endl;
    NormalNode *p = normalHead;
    p = p->next;
    while (p)
    {
        fout << p->content << "\t"
             << setw(10) << p->describe << "\t"
             << setw(3) << p->type << "\t"
             << setw(8) << p->iden_type << "\t\t"
             << p->line << endl;

        p = p->next;
    }
    fout << endl;

    cout << "words.txt�������!" << endl;
    fout.close();
}

//�����������Ϣ
void printErrorLink()
{
    cout << "*****************************�����******************************" << endl
         << endl;
    cout << setw(15) << "����" << setw(15) << "����"
         << "\t"
         << "����"
         << "\t"
         << "�к�" << endl;
    ErrorNode *p = errorHead;
    p = p->next;
    while (p)
    {
        cout << setw(15) << p->content << setw(15) << p->describe << "\t" << p->type << "\t" << p->line << endl;
        p = p->next;
    }
    cout << endl
         << endl;
}

//����ɨ��
void scanner()
{
    string filename;
    string word;
    int i;
    int line = 1; //����

    fstream fin("test.txt", ios::in);
    if (!fin)
    {
        cout << "���ļ�ʧ�ܣ�" << endl;
        return;
    }
    else
    {
        cout << "���ļ��ɹ���" << endl;
    }

    char ch;
    fin.get(ch);
    while (!fin.eof() && ch != '$')
    {
        i = 0;
        word.clear();
        //����ĸ��ͷ, ����ؼ��ֻ��߱�ʶ��
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
        {
            while ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9'))
            {
                word += ch;
                fin.get(ch);
            }

            //����Ǳ�����
            map<string, int>::iterator it = keyMap.find(word);
            if (it != keyMap.end())
            {
                createNewNode(word, KEY_DESC, it->second, line);
            }
            //����Ǳ�ʶ��
            else
            {
                // int addr_tmp = createNewIden(word, IDENTIFIER_DESC, IDENTIFIER, -1, line);
                createNewNode(word, IDENTIFIER_DESC, IDENTIFIER, line);
            }
            fin.seekg(-1, ios::cur);
        }
        //�����ֿ�ͷ
        else if (ch >= '0' && ch <= '9')
        {
            while (ch >= '0' && ch <= '9')
            {
                word += ch;
                fin.get(ch);
            }
            createNewNode(word, CONSTANT_DESC, CONSTANT, line);
            fin.seekg(-1, ios::cur);
        }
        else if (ch == '+')
        {
            createNewNode("+", OPE_DESC, ADD, line);
        }
        else if (ch == '-')
        {
            createNewNode("-", OPE_DESC, SUB, line);
        }
        else if (ch == '*')
        {
            createNewNode("*", OPE_DESC, MUL, line);
        }
        else if (ch == '/')
        {
            createNewNode("/", OPE_DESC, DIV, line);
        }
        else if (ch == '<')
        {
            fin.get(ch);
            if (ch == '=')
            {
                createNewNode("<=", OPE_DESC, LESS_EQUAL, line);
            }
            else
            {
                createNewNode("<", OPE_DESC, LESS_THAN, line);
                fin.seekg(-1, ios::cur);
            }
        }
        else if (ch == '>')
        {
            fin.get(ch);
            if (ch == '=')
            {
                createNewNode(">=", OPE_DESC, GRT_EQUAL, line);
            }
            else
            {
                createNewNode(">", OPE_DESC, GRT_THAN, line);
                fin.seekg(-1, ios::cur);
            }
        }
        else if (ch == '!')
        {
            fin.get(ch);
            if (ch == '=')
            {
                createNewNode("!=", OPE_DESC, NOT_EQUAL, line);
            }
            else
            {
                createNewError("!", EXCLAMATION_ERROR, EXCLAMATION_ERROR_NUM, line);
                fin.seekg(-1, ios::cur);
            }
        }
        else if (ch == '=')
        {
            fin.get(ch);
            if (ch == '=')
            {
                createNewNode("==", OPE_DESC, EQUAL, line);
            }
            else
            {
                createNewNode("=", OPE_DESC, ASSIGN, line);
                fin.seekg(-1, ios::cur);
            }
        }
        else if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n')
        {
            if (ch == '\n')
            {
                line++;
            }
        }
        else if (ch == '(')
        {
            createNewNode("(", CLE_OPE_DESC, LEFT_BRACKET, line);
        }
        else if (ch == ')')
        {
            createNewNode(")", CLE_OPE_DESC, RIGHT_BRACKET, line);
        }
        else if (ch == '{')
        {
            createNewNode("{", CLE_OPE_DESC, LEFT_BOUNDER, line);
        }
        else if (ch == '}')
        {
            createNewNode("}", CLE_OPE_DESC, RIGHT_BOUNDER, line);
        }
        else if (ch == ';')
        {
            createNewNode(";", CLE_OPE_DESC, SEMICOLON, line);
        }
        else if (ch == '$')
        {
            createNewNode(";", CLE_OPE_DESC, DOLLAR, line);
        }
        else
        {
            createNewError(word, SYMBOL_ERROR, SYMBOL_ERROR_NUM, line);
        }

        fin.get(ch);
    }
    if (ch == '$')
    {
        word.clear();
        word += ch;
        createNewNode(word, CLE_OPE_DESC, DOLLAR, line);
    }

    fin.close();
}

//���ս�����������
void clear()
{
    while (normalHead)
    {
        NormalNode *next = normalHead->next;
        delete normalHead;
        normalHead = next;
    }
    while (errorHead)
    {
        ErrorNode *next = errorHead->next;
        delete errorHead;
        errorHead = next;
    }
}
