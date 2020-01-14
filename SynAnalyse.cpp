#include "LexAnalyse.h"
#include "SynAnalyse.h"
#include <iostream>
#include <sstream>

using namespace std;

int line_bak; //normal���ÿ���ƶ�ǰ��������������, ���1�г���ʱָ����������

//mid_type�ṹ��ȡ�����ṩ��gen()������Ԫʽ�м����
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

//�����µı�ʶ�����
void createNewIden(NormalNode *p)
{
    iden_map[p->content] = IdentifierNode(p->content, p->describe, p->type, "int", p->line);
}

//�����ʶ����
void printIdentLink()
{
    cout << "****************************��ʶ����*****************************" << endl
         << endl;
    cout << setw(15) << "����"
         << setw(15) << "����"
         << "\t"
         << setw(3) << "�ֱ���"
         << "\t"
         << setw(8) << "��ʶ������"
         << "\t"
         << "�к�" << endl;

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

//������ʶ����
void outputIdenLink()
{
    ofstream fout("identifiers.txt");
    if (!fout)
    {
        cout << "identifiers.txt��ʧ��!" << endl;
        return;
    }
    fout << "*****************************��ʶ����******************************" << endl
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

    for (map<string, IdentifierNode>::iterator p = iden_map.begin(); p != iden_map.end(); p++)
    {
        fout << p->second.content << "\t"
             << setw(10) << p->second.describe << "\t"
             << setw(3) << p->second.type << "\t"
             << setw(8) << p->second.iden_type << "\t\t"
             << p->second.line << endl;
    }
    fout << endl;

    cout << "identifiers.txt�������!" << endl;
    fout.close();
}

/*����Ϊ�������ս���ĵݹ��ӳ���*/
//<����>
void program(NormalNode *&p)
{
    if (p)
    {
        //����first
        if (p->content == "int")
        {
            main_fun(p);
            if (p)
            {
                if (p->content == "$")
                {
                    line_bak = p->line;
                    p = p->next;
                    cout << "�﷨�������!" << endl;
                    return;
                }
            }
            else
            {
                cout << "��" << line_bak << "�д���: ����Ӧ��$����" << endl;
            }
        }
        else
        {
            cout << "��" << p->line << "�д���: ����Ӧ��int��ʼ" << endl;
        }
    }
    else
    {
        cout << "������Ϊ��" << endl;
    }
}

//<main����>
void main_fun(NormalNode *&p)
{
    if (p)
    {
        if (p->content == "int")
        {
            return_type(p);
            if (p)
            {
                //����first
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
                                    cout << "��" << p->line << "�д���: " << p->content << "ӦΪ\")\"" << endl;
                                }
                            }
                            else
                            {
                                cout << "��" << line_bak << "�д���: (����Ҫ)���" << endl;
                            }
                        }
                        else
                        {
                            cout << "��" << p->line << "�д���: main������ӦΪ\"(\"" << endl;
                        }
                    }
                    else
                    {
                        cout << "��" << line_bak << "�д���: main��������Ҫ(" << endl;
                    }
                }
                //��������main�������Ĵ���
                else if (p->content == "(")
                {
                    cout << "��" << p->line << "�д���: main����Ӧ�к�����main" << endl;
                    goto main_fun1;
                }
                //����main������д��Ĵ���
                else if (p->next && p->next->content == "(")
                {
                    cout << "��" << p->line << "�д���: main����Ӧ��mainΪ������" << endl;
                    goto main_fun2;
                }
                else
                {
                    cout << "��" << p->line << "�д���: main����Ӧ��mainΪ������" << endl;
                }
            }
            else
            {
                cout << "��" << line_bak << "�д���: main������Ҫ������" << endl;
            }
        }
        else
        {
            cout << "��" << p->line << "�д���: main����Ӧ��intΪ��������" << endl;
        }
    }
    else
    {
        cout << "��" << line_bak << "�д���: main������Ҫ��������" << endl;
    }
}

//<��������>
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
            cout << "��" << p->line << "�д���: ��������ӦΪint" << endl;
        }
    }
    else
    {
        cout << "��" << line_bak << "�д���: ������Ҫ��������" << endl;
    }
}

//<��������>
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
            cout << "��" << p->line << "�д���: ��������ӦΪint" << endl;
        }
    }
    else
    {
        cout << "��" << line_bak << "�д���: ��ʱ��Ҫ��������" << endl;
    }
}

//<�������>
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
                    cout << "��" << p->line << "�д���: " << p->content << "ӦΪ\"}\"" << endl;
                }
            }
            else
            {
                cout << "��" << line_bak << "�д���: ��ʱ��Ҫ{" << endl;
            }
        }
        else
        {
            cout << "��" << p->line << "�д���: �������Ӧ��{��ʼ" << endl;
        }
    }
    else
    {
        cout << "��" << line_bak << "�д���: ��ʱ��Ҫ{" << endl;
    }
}

//<�������>
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
            cout << "��" << p->line << "�д���: ���ͷ���Ϸ�" << endl;
        }
    }
    else
    {
        cout << "��" << line_bak << "�д���: ��ʱ��Ҫ���ͷ" << endl;
    }
}

//<���>
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
                    cout << "��" << p->line << "�д���: " << p->content << "ӦΪ\";\"" << endl;
                }
            }
            else
            {
                cout << "��" << line_bak << "�д���: ��ʱӦ��\";\"" << endl;
            }
        }
        else
        {
            cout << "��" << p->line << "�д���: û�кϷ����ͷ" << endl;
        }
    }
    else
    {
        cout << "��" << line_bak << "�д���: �������������Ӧ��1�����" << endl;
    }
}

//<���ݹ�>
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
            cout << "��" << p->line << "�д���: " << p->content << "������, �˴�Ӧ�������ͷ��}" << endl;
        }
    }
    else
    {
        cout << "��" << line_bak << "�д���: ��������" << endl;
    }
}

//<�������>
void define_statement(NormalNode *&p)
{
    if (p)
    {
        if (p->content == "int")
        {
            var_type(p);

            NormalNode *bak = p; //���ݱ�ʶ��λ��
            _identifier(p);

            if (bak)
            { //����, ��ʶ�����͸�ֵ
                if (iden_map.find(bak->content) == iden_map.end())
                {
                    createNewIden(bak);
                    bak->iden_type = "int";
                    //������ʶ��    ��Ԫʽ
                    gen("assign", "int", "_", bak->content);
                }
                else
                {
                    cout << "��" << p->line << "�д���: ��ʶ��" << p->content << "������" << endl;
                }
            }
            else
            {
                cout << "��" << line_bak << "�д���: ��ʶ��������, �޷�����" << endl;
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
                    if (_e.isT != 2) //���緵���м��岻Ϊ��
                    {
                        gen("=", mid2string(_e), "_", mid2string(_it));

                        //����_e
                        emit(_e);
                    }
                    line_bak = p->line;
                    p = p->next;
                    return;
                }
                else
                {
                    cout << "��" << p->line << "�д���: " << p->content << "ӦΪ\";\"" << endl;
                }
            }
            else
            {
                cout << "��" << line_bak << "�д���: ��ʱӦ��\";\"" << endl;
            }
        }
        else
        {
            cout << "��" << p->line << "�д���: û�кϷ����ͷ" << endl;
        }
    }
    else
    {
        cout << "��" << line_bak << "�д���: �������Ӧ�Ա������Ϳ�ͷ" << endl;
    }
}

//<����ֵ>
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
            cout << "��" << p->line << "�д���: ��ʱ��Ҫ����ʶ������ֵ����;��β" << endl;
        }
    }
    else
    {
        cout << "��" << line_bak << "�д���: ��������" << endl;
    }
    return error;
}

//<��ֵ���>
void assign_statement(NormalNode *&p)
{
    if (p)
    {
        if (p->describe == IDENTIFIER_DESC)
        {
            //�жϱ�ʶ���Ƿ�������
            if (iden_map.find(p->content) == iden_map.end())
            {
                cout << "��" << p->line << "�д���: ��ʶ��" << p->content << "��δ����" << endl;
            }

            string _i = _identifier(p); //��ʶ������
            if (p)
            {
                if (p->content == "=")
                {
                    line_bak = p->line;
                    p = p->next;
                    mid_type _e = expression(p); //���ʽ����
                    if (_e.isT == -1)
                        return;
                    if (p)
                    {
                        if (p->content == ";")
                        {
                            line_bak = p->line;
                            p = p->next;

                            gen("=", mid2string(_e), "_", _i);

                            //����_e
                            emit(_e);

                            return;
                        }
                        else
                        {
                            cout << "��" << p->line << "�д���: " << p->content << "ӦΪ\";\"" << endl;
                        }
                    }
                    else
                    {
                        cout << "��" << line_bak << "�д���: ��ʱӦ��\";\"" << endl;
                    }
                }
                else
                {
                    cout << "��" << p->line << "�д���: " << p->content << "ӦΪ\"=\"" << endl;
                }
            }
            else
            {
                cout << "��" << line_bak << "�д���: ��ʱӦ��\"+\"��" << endl;
            }
        }
        else
        {
            cout << "��" << p->line << "�д���: ��ʱӦ�б�ʶ��" << endl;
        }
    }
    else
    {
        cout << "��" << line_bak << "�д���: ��������" << endl;
    }
}

//<�������>
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

                            //����_b_e
                            emit(_b_e);

                            struct_statement(p);
                            CodeNode &if_end_to = gen("j", "_", "_", "");
                            if (p)
                            {
                                if (p->content == "else")
                                {
                                    //����else_from
                                    stringstream ss;
                                    ss << "(" << code.back().line + 1 << ")";
                                    else_from.result = ss.str();

                                    line_bak = p->line;
                                    p = p->next;
                                    struct_statement(p);

                                    //����if_end_to
                                    ss.str("");
                                    ss << "(" << code.back().line + 1 << ")";
                                    if_end_to.result = ss.str();
                                }
                                else
                                {
                                    cout << "��" << p->line << "�д���: " << p->content << "ӦΪelse" << endl;
                                }
                            }
                            else
                            {
                                cout << "��" << line_bak << "�д���: ��ʱӦ��else" << endl;
                            }
                        }
                        else
                        {
                            cout << "��" << p->line << "�д���: " << p->content << "ӦΪ\")\"" << endl;
                        }
                    }
                    else
                    {
                        cout << "��" << line_bak << "�д���: ��ʱӦ��)" << endl;
                    }
                }
                else
                {
                    cout << "��" << p->line << "�д���: " << p->content << "ӦΪ\"(\"" << endl;
                }
            }
            else
            {
                cout << "��" << line_bak << "�д���: ��ʱӦ��(" << endl;
            }
        }
        else
        {
            cout << "��" << p->line << "�д���: " << p->content << "ӦΪif" << endl;
        }
    }
    else
    {
        cout << "��" << line_bak << "�д���: ��ʱӦ��if" << endl;
    }
}

//<�������ʽ>
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
            cout << "��" << p->line << "�д���: " << p->content << "ӦΪ���ʽ" << endl;
        }
    }
    else
    {
        cout << "��" << line_bak << "�д���: ��ʱӦ�б��ʽ" << endl;
    }
    return error;
}

//<���ʽ>
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
            cout << "��" << p->line << "�д���: " << p->content << "ӦΪ��" << endl;
        }
    }
    else
    {
        cout << "��" << line_bak << "�д���: ��ʱӦ����" << endl;
    }
    return error;
}

//<��ݹ�>
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
            //������Ԫʽ
            gen(op_bak, mid2string(front), mid2string(back), mid2string(res));

            //����front��back
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
            cout << "��" << p->line << "�д���: ��ʱӦ�и����������" << endl;
        }
    }
    else
    {
        cout << "��" << line_bak << "�д���: �����" << endl;
    }
    return error;
}

//<��>
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
            cout << "��" << p->line << "�д���: " << p->content << "ӦΪ��ʽ" << endl;
        }
    }
    else
    {
        cout << "��" << line_bak << "�д���: ��ʱӦ����ʽ" << endl;
    }
    return error;
}

//<��ʽ�ݹ�>
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

            //����front��back
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
            cout << "��" << p->line << "�д���: ��ʱӦ�и������ʽ���������ʽ(����������;)" << endl;
        }
    }
    else
    {
        cout << "��" << line_bak << "�д���: ��ʽ������" << endl;
    }
    return error;
}

//<��ʽ>
mid_type factor(NormalNode *&p)
{
    if (p)
    {
        if (p->describe == IDENTIFIER_DESC)
        {
            NormalNode *p_bak = p;

            //�жϱ�ʶ���Ƿ�������
            if (iden_map.find(p->content) == iden_map.end())
            {
                cout << "��" << p->line << "�д���: ��ʶ��" << p->content << "��δ����" << endl;
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
                    cout << "��" << p->line << "�д���: " << p->content << "ӦΪ\")\"" << endl;
                }
            }
            else
            {
                cout << "��" << line_bak << "�д���: ��ʱӦ��)" << endl;
            }
        }
        else
        {
            cout << "��" << p->line << "�д���: " << p->content << "��Ϊ��ʽ���Ϸ�" << endl;
        }
    }
    else
    {
        cout << "��" << line_bak << "�д���: ��ʽ������" << endl;
    }
    return error;
}

//<��ϵ�����>
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
            cout << "��" << p->line << "�д���: " << p->content << "ӦΪ��ϵ�����" << endl;
        }
    }
    else
    {
        cout << "��" << line_bak << "�д���: ��ʱӦ�й�ϵ�����" << endl;
    }
    return error;
}

//<��ʶ��>
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
            cout << "��" << p->line << "�д���: " << p->content << "ӦΪ��ʶ��" << endl;
        }
    }
    else
    {
        cout << "��" << line_bak << "�д���: ��ʱӦ�б�ʶ��" << endl;
    }
    return _NULL;
}

//<�������ų���>
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
            cout << "��" << p->line << "�д���: " << p->content << "ӦΪ����" << endl;
        }
    }
    else
    {
        cout << "��" << line_bak << "�д���: ��ʱӦ�г���" << endl;
    }
}

//��ȡ�µ��м����Ti
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

//�����м����Ti
void emit(mid_type m)
{
    //������м����
    if (m.isT == 1)
    {
        T[m.T_num] = false;
    }
}

//������Ԫʽ�м����
CodeNode &gen(string opt, string arg1, string arg2, string result)
{
    static int static_line = 0;
    code.push_back(CodeNode(++static_line, opt, arg1, arg2, result));
    return code.back();
}

//�����Ԫʽ�м����
void printCode()
{
    cout << "�м��������: " << endl;
    for (list<CodeNode>::iterator it = code.begin(); it != code.end(); ++it)
    {
        cout << "(" << it->line << ")"
             << "\t" << it->opt << "\t" << it->arg1 << "\t" << it->arg2 << "\t" << it->result << endl;
    }
}

//������Ԫʽ�м����
void outputCode()
{
    ofstream fout("midCode.txt");
    if (!fout)
    {
        cout << "midCode.txt��ʧ��!" << endl;
        return;
    }
    for (list<CodeNode>::iterator it = code.begin(); it != code.end(); ++it)
    {
        fout << "(" << it->line << ")"
             << "\t" << it->opt << "\t" << it->arg1 << "\t" << it->arg2 << "\t" << it->result << endl;
    }

    fout.close();
}