#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include<vector>
using namespace std;
string KEYWORD[32] = {                   //1-32
    "short", "int", "double", "char", "long", 
    "float","default", "volatile", "case", "else",
    "enum", "extern","continue", "void", "goto", 
    "if", "break", "const","register", "return",
    "auto", "signed", "sizeof", "static", "struct",
    "switch", "typedef", "union", "unsigned", "for",
    "do", "while"
};
string DANGER_FUC[4] = {  //201��ʼ 201��gets 202:strcpy
    "gets","strcpy","scanf","strcat"
};

char SEPARATER[8] = { ';',',','{','}','[',']','(',')' };  //�ָ���  51-60
char OPERATOR[8] = { '+','-','*','/','>','<','=','!' };   //�����  61-70
char FILTER[4] = { ' ','\t','\r','\n' };          //���˷�
const int dangerfucNum = 4;
const int keywordNum = 32;
const int CONSTANT = 100;      //����ֵ
const int IDENTIFIER_v = 101;     //��ʶ��-����
const int IDENTIFIER_f = 102;     //��ʶ��-����
const int FILTER_VALUE = 103;    //�����ַ�ֵ

//bool in_fuc = false;
int state = 0;  //״̬ 1:��ʶ������ 
                       //11:1��״̬�£��¸��ַ�Ϊ����������ʱ��11��˵����ʶ��Ϊ���� 
                           //111:11��״̬�£����� ��)�� 
                                //1111:111��״̬�£��¸��ַ�Ϊ��{�� ����ʱ��1111��˵������Ϊ����״̬,��in_fuc=true *** ֮�������Ƿ��й���ֲ�����������صݹ�
                                //1112:111��״̬�£��¸��ַ����� ��{����������Ϊ����������Ż�),��ʱ˵������Ϊ����״̬ *** �ж����Ƿ�Ϊ���⺯�������Ǿ��޸ģ����ǿ�in_fuc�Ƿ�Ϊtrue�����ǣ����Ƿ�Ϊ�ݹ�
                      //12:˵����ʶ��Ϊ��������ʱ��in_fuc�Ƿ�Ϊtrue,���ǣ����¸���Ч�ַ��Ƿ�Ϊ[
//float last_num; //��������ʱ����¼ǰһ������
//string last_identifier; //��¼��һ����ʶ������Ϊ֮�������Ϊ���������ж����Ƿ�Ϊ��Ǻ���

FILE* fpin, * fout;
//�ж��Ƿ�ΪΣ�պ���
int IsDangerFuc(string word) {
    for (int i = 0;i < dangerfucNum;i++) {
        if (DANGER_FUC[i] == word) {
            return i + 1;
        }
    }
    return dangerfucNum + 1;
}

/**�ж��Ƿ�Ϊ�ؼ���**/ //arr
int IsKeyword(string word) {
    for (int i = 0;i < keywordNum;i++) {
        if (KEYWORD[i] == word) {
            return i + 1;
        }
    }
    return keywordNum + 1;
}


/**�ж��Ƿ�Ϊ�ָ���**/
int IsSeparater(char ch) {
    for (int i = 0;i < 8;i++) {
        if (SEPARATER[i] == ch) {
            return 50 + i + 1;
        }
    }
    return 0;
}

/**�ж��Ƿ�Ϊ�����**/
int IsOperator(char ch) {
    for (int i = 0;i < 8;i++) {
        if (OPERATOR[i] == ch) {
            return 60 + i + 1;
        }
    }
    return 0;
}
/**�ж��Ƿ�Ϊ���˷�**/
bool IsFilter(char ch) {
    for (int i = 0;i < 4;i++) {
        if (FILTER[i] == ch) {
            return true;
        }
    }
    return false;
}
/**�ж��Ƿ�Ϊ��д��ĸ**/
bool IsUpLetter(char ch) {
    if (ch >= 'A' && ch <= 'Z') return true;
    return false;
}
/**�ж��Ƿ�ΪСд��ĸ**/
bool IsLowLetter(char ch) {
    if (ch >= 'a' && ch <= 'z') return true;
    return false;
}
/**�ж��Ƿ�Ϊ����**/
bool IsDigit(char ch) {
    if (ch >= '0' && ch <= '9') return true;
    return false;
}
/**����ÿ���ֵ�ֵ**/
template <class T>
int value(T* a, int n, T str) {
    for (int i = 0;i < n;i++) {
        if (a[i] == str) return i + 1;
    }
    return -1;
}

bool fuc_state(FILE* fpin) { //�жϺ���״̬������or���� �����˻�
    int left = 1;
    int right = 0;
    char ch;

    int posi = 0;
    while (left != right) {
        ch = fgetc(fpin);
        posi++;
        if (ch == '(')
            left++;
        else if (ch == ')')
            right++;
    }
    //�����Ž���������һ���ַ�
    ch = fgetc(fpin);
    posi++;
    while (IsFilter(ch)) {
        ch = fgetc(fpin);
        posi++;
    }
    fseek(fpin, -posi, SEEK_CUR); //�����˻أ��������� { ֮������ݼ������� 
    if (ch == '{') {
        return true;
    } 
    return false;
}

int deal_formula(string formula) {  // ��������޹��˷�����ʽ�ַ��������Ӳ��˻�
    int len = formula.size();
    string arr = "";
    for (int i = 0;i < len;i++) {
        if (formula[i] == '(') {         
            i++;
            while (formula[i] != '(' && formula[i] != ')') {

            }
        }
        arr += formula[i];

    }
    return 300;
}
int deal_nokh_formula(string formula) { //��������С���� 1+2*3-4/5
    int len = formula.size();
    string arr = "";
    vector<int> number;
    vector<char> symbol;

    for (int i = 0;i < len;i++) {  //�������ֻʣ�Ӽ���
        if (IsDigit(formula[i]) && i != len - 1) {
            arr += formula[i];          
        }
        else { //ѹ�����������Ƿ��ǳ˳�����
            if (i == len - 1) {  //����β��˵��formula[i]������
                arr += formula[i];           
            }
            number.push_back(atoi(arr.c_str())); //ѹ����
           
            if (!symbol.empty()&&(symbol.back() == '*' || symbol.back() == '/')) {
                int a, b;
                a = number.back();
                number.pop_back();
                b = number.back();
                number.pop_back();
                if (symbol.back() == '*') {
                    number.push_back(a * b);
                }
                else if (symbol.back() == '/') {
                    number.push_back(b / a);
                }
                symbol.pop_back();
            }

            if (i != len - 1) { //������β��˵��formula[i]���ַ�
                symbol.push_back(formula[i]);
            }
         
            arr = "";
        }
    }
    int sum = number.front();
    while (!symbol.empty()) {
        int a;
        a = number.back();
        if (symbol.back() == '+') {
            sum += a;
        }
        else if (symbol.back() == '-') {
            sum -= a;
        }
        number.pop_back();
        symbol.pop_back();
        
    }
    return sum;
}

/**�ʷ�����**/
void analyse(FILE* fpin) {
    int arr_num = 0; //�ؼ�������
    int ch_num = 0; //�ַ�����
    int dangerf_num = 0; //Σ�պ�������

    char ch = ' ';
    string arr = "";  //����һ���ؼ��ֻ��ʶ��
    string filter_str = ""; //����һ�ι��˷�

    bool in_fuc = false; //�Ƿ��ں�����
    string in_fuc_name = ""; //��ǰ���ں������֣������ж��Ƿ��еݹ�
    int left_kh_num = 0; //�����ţ���⺯���Ƿ����
    int right_kh_num = 0; 

    bool in_state = false; //�Ƿ���char int������״̬��������;������ ���ڼ�¼���ܳ��ֵ�ָ������
    bool in_state_p = false;
    vector<string> pointer;
    vector<string> pointer_pname;

    int left_xkh_num = 0;//С���ţ����
    int right_xkh_num = 0;

    string last_state;//��¼�ϸ��������ͣ�int char �ȵ�... ���ڰ�ջ����ת������ʱ���ַ��������������int a[2000]-->int *a=new int[2000]
    vector<string> shift_var_name; //��¼��ǰ�������б�ת�Ƶ����ϵı���������returnǰ����delete
    bool fuc_has_ret = false;
    while ((ch = fgetc(fpin)) != EOF) {
        arr = "";
        filter_str = "";

        if (IsFilter(ch)) {
            fprintf(fout, "%c", ch);
        }       //�ж��Ƿ�Ϊ���˷�

        else if (IsLowLetter(ch)) {    //�ж��Ƿ�Ϊ�ؼ���
            while (IsUpLetter(ch) || IsLowLetter(ch) || ch == '_'|| IsDigit(ch)) {  //��Сд�����֣���_�����
                arr += ch;
                ch = fgetc(fpin);
            }
            //���¸���Ϊ���˷�����ĸ���õ�����token
            fseek(fpin,-1L,SEEK_CUR); //�˻�һ�񣬴�ʱ�õ���Ϊһ��Сд��ĸ
            arr_num = IsKeyword(arr);

            if (arr_num <= keywordNum) {  //��ʶ��Ϊ�ؼ���
                //1 cout << arr_num << " " << arr << " �ؼ���" << endl;            //����ע�ͣ���ʾע�͵���Ļ�Ϸǹؼ���Ϣ,ֻ���������޸�����
                
                if (arr_num <= 6) {  //��¼��������int char..  ���ں���ջ�ƶ�
                    last_state = arr.c_str();
                    in_state = true;
                }
              
                else if (arr_num == 20) { //return,��д��return֮ǰ��delete���ж��ϱ���
                    fuc_has_ret = true; //������return
                    if (shift_var_name.size() >= 1) {   //todo��Ϊ��ʽ����д�ĺܸ��ӣ���Ϊ����ûreturnʱ��delete
                        fprintf(fout, "%s", "delete[]");
                        fprintf(fout, "%s", shift_var_name[0].c_str());
                        fprintf(fout, "%c\n", ';');
                        for (int i = 1;i < shift_var_name.size();i++) {
                            fprintf(fout, "%s", "    delete[]");
                            fprintf(fout, "%s", shift_var_name[i].c_str());
                            fprintf(fout, "%c\n", ';');
                        }
                        shift_var_name.clear();
                        fprintf(fout, "%s", "    ");
                    }                 
                }               
                fprintf(fout, "%s", arr.c_str());
            }
            else //��ʶ��Ϊ�������� ��ָ��
            {
                ch = fgetc(fpin); //�������¸���Ϊ���˷�����ĸ
                while (IsFilter(ch)) {
                    filter_str += ch;
                    ch = fgetc(fpin);
                }
                //cout << endl << "��ǰ��Ϊ���˷����ַ�Ϊ��" << ch << endl;
                if (ch == '(') {  //��ʶ��Ϊ����
                    //state = 11; 
                    dangerf_num = IsDangerFuc(arr);
                    if (dangerf_num <= dangerfucNum) { //����Σ�պ�������Ϊ���� 1:gets 2:strcpy
                        cout << IDENTIFIER_v << " " << arr << " ��ʶ��-����(Σ�գ�" ; //Σ�պ�����Ϊ���ã����Ժ���������

                        //arr += ch; //�������ַ������ϣ� ����ֱ�Ӵ�����������ģ�
                        left_xkh_num++;
                        string identifier_inkh_name = ""; //��¼Σ�պ����ڱ�������

                        switch (dangerf_num) {
                            case 1:  //gets(s)-->fgets(s,sizeof(s),stdin)
                            {                               
                                arr = "fgets("; //��ǰ���arr="gets("  �����пո������ո񣬸�Ϊ�º���
                                while(left_xkh_num != right_xkh_num) {
                                    ch = fgetc(fpin);
                                    identifier_inkh_name += ch;
                                    if (ch == '(') {
                                        left_xkh_num++;
                                    }
                                    else if (ch == ')') {
                                        right_xkh_num++;
                                    }
                                }
                                //����arr="fgets("
                                // identifier_inkh_name = "s)"
                                arr += identifier_inkh_name;
                                identifier_inkh_name.erase(identifier_inkh_name.length() - 1, 1);
                                
                                for (int i = 0;i < pointer.size();i++) {
                                    if (pointer[i].compare(identifier_inkh_name) == 0) {
                                        identifier_inkh_name = pointer_pname[i];
                                    }
                                }

                                arr.insert(arr.length() - 1, ",sizeof("+identifier_inkh_name+"),stdin");
                                fseek(fpin, 1L, SEEK_CUR); //ǰ��һ����Ϊ�Ѿ��ѣ����������ˣ�֮�󻹻��˻�һ���������ﱣ��ƽ��
                                left_xkh_num = 0;
                                right_xkh_num = 0;

                                break;
                            }
                            case 2:  //strcpy(s,s1)-->strcpy_s(s,sizeof(s),s1)
                            {
                                arr = "strcpy_s("; 
                                while ((ch = fgetc(fpin)) != ',') {
                                    identifier_inkh_name += ch;
                                    arr += ch;
                                    if (ch == '(') {
                                        left_xkh_num++;
                                    }
                                    else if (ch == ')') {
                                        right_xkh_num++;
                                    }
                                }
                                arr += ch; //arr���϶���
                                while (left_xkh_num != right_xkh_num) {
                                    ch = fgetc(fpin);        
                                    arr += ch;
                                    if (ch == '(') {
                                        left_xkh_num++;
                                    }
                                    else if (ch == ')') {
                                        right_xkh_num++;
                                    }
                                }
                                //����arr="strcpy_s(s,s1)"
                                // identifier_inkh_name = "s"
                              
                                for (int i = 0;i < pointer.size();i++) {
                                    if (pointer[i].compare(identifier_inkh_name) == 0) {
                                        identifier_inkh_name = pointer_pname[i];
                                    }
                                }
                                arr.insert(arr.find(",") + 1, "sizeof(" + identifier_inkh_name + "),");
                                fseek(fpin, 1L, SEEK_CUR); //ǰ��һ����Ϊ�Ѿ��ѣ����������ˣ�֮�󻹻��˻�һ���������ﱣ��ƽ��
                                left_xkh_num = 0;
                                right_xkh_num = 0;

                                break;
                            }
                            case 3:  //scanf("%s",&s)-->strcpy_s("%s",&s,sizeof(s))
                            {
                                arr = "scanf_s(";
                                while ((ch = fgetc(fpin)) != '&') {                                   
                                    arr += ch;
                                    if (ch == '(') {
                                        left_xkh_num++;
                                    }
                                    else if (ch == ')') {
                                        right_xkh_num++;
                                    }
                                }
                                arr += ch; //arr����&
                              
                                while (left_xkh_num != right_xkh_num) {                                  
                                    ch = fgetc(fpin);
                                    identifier_inkh_name += ch; //д��ch = fgetc(fpin)����Ϊ����&
                                    arr += ch;
                                    if (ch == '(') {
                                        left_xkh_num++;
                                    }
                                    else if (ch == ')') {
                                        right_xkh_num++;
                                    }
                                }
                                //����arr="scanf_s("s%",&s)"
                                // identifier_inkh_name = "s)"
                                arr.erase(arr.length() - 1, 1); //ɾȥ������
                                identifier_inkh_name.erase(identifier_inkh_name.length() - 1, 1); //ɾȥ������     

                                for (int i = 0;i < pointer.size();i++) {
                                    if (pointer[i].compare(identifier_inkh_name) == 0) {
                                        identifier_inkh_name = pointer_pname[i];
                                    }
                                }

                                arr += ",sizeof(" + identifier_inkh_name + "))";
                                fseek(fpin, 1L, SEEK_CUR); //ǰ��һ����Ϊ�Ѿ��ѣ����������ˣ�֮�󻹻��˻�һ���������ﱣ��ƽ��
                                left_xkh_num = 0;
                                right_xkh_num = 0;

                                break;
                            }
                            case 4:  //strcpy(s,s1)-->strncpy(s,s1,sizeof(s)-length(s)-1)  //������length��Ϊ
                            {
                                arr = "strcat_s(";
                                while ((ch = fgetc(fpin)) != ',') {
                                    identifier_inkh_name += ch;
                                    arr += ch;
                                    if (ch == '(') {
                                        left_xkh_num++;
                                    }
                                    else if (ch == ')') {
                                        right_xkh_num++;
                                    }
                                }
                                arr += ch; //arr���϶���
                                while (left_xkh_num != right_xkh_num) {
                                    ch = fgetc(fpin);
                                    arr += ch;
                                    if (ch == '(') {
                                        left_xkh_num++;
                                    }
                                    else if (ch == ')') {
                                        right_xkh_num++;
                                    }
                                }
                                //����arr="strcat_s(s,s1)"
                                // identifier_inkh_name = "s"                              
                                //arr.erase(arr.length() - 1, 1); //ɾȥ������                              

                                for (int i = 0;i < pointer.size();i++) {
                                    if (pointer[i].compare(identifier_inkh_name) == 0) {
                                        identifier_inkh_name = pointer_pname[i];
                                    }
                                }
                                arr.insert(arr.find(",") + 1, "sizeof(" + identifier_inkh_name + ") - strlen(" + identifier_inkh_name + ") - 1,");
                                //arr += ",sizeof(" + identifier_inkh_name + ") - strlen(" + identifier_inkh_name + ") - 1)";
                                fseek(fpin, 1L, SEEK_CUR); //ǰ��һ����Ϊ�Ѿ��ѣ����������ˣ�֮�󻹻��˻�һ���������ﱣ��ƽ��
                                left_xkh_num = 0;
                                right_xkh_num = 0;

                                break;
                            }
                        }
                        cout << "  ; ���޸�Ϊ :" << arr << endl;
                        fprintf(fout, "%s", arr.c_str());//arr��ʱΪ������+�������������ֱ����
                    }
                    else {   //���������������ж���Ϊ�������ǵ���
                        if (fuc_state(fpin)) {  //���������������Ϊ������״̬����ʱҪ�������ռ��С������¼��������Ϊ֮�����ڲ��Ƿ��еݹ���׼����
                            cout << IDENTIFIER_v << " " << arr << " ��ʶ��-����(��ȫ��-����״̬" << endl; //����
                           // state=
                            //if (arr.compare("main") != 0) {
                            in_fuc = true;  //���뺯��״̬ 
                            in_fuc_name += arr; //��¼��ʱ�������֣����ڼ���Ƿ��еݹ�
                            fuc_has_ret = false; //������ʼ�����趨��return
                            cout << endl << "���뺯��:" << in_fuc_name << endl << endl;
                            fprintf(fout, "%s", arr.c_str());
                            //}
                        }
                        else {  //�������ã�����Ƿ���ڵݹ�
                            cout << IDENTIFIER_v << " " << arr << " ��ʶ��-����(��ȫ��-����״̬ ;"; //����
                            if (in_fuc) {
                                if (in_fuc_name.compare(arr) == 0) {
                                    cout << " ���ĳ�����ʹ���˵ݹ麯������ע�����Ƿ�ݹ�������ࡣ";
                                    arr += ch;
                                    while ((ch = fgetc(fpin)) != ';') {
                                        arr += ch;
                                    }
                                    arr += ch;
                                    fprintf(fout, "%s", arr.c_str());
                                    fprintf(fout, "%s", " //���ĳ�����ʹ���˵ݹ麯������ע�����Ƿ�ݹ�������ࡣ");
                                    fseek(fpin, 1L, SEEK_CUR); //�˻�һ��
                                }
                                else {
                                    fprintf(fout, "%s", arr.c_str());
                                }
                            }
                            cout << endl;
                            //��δ֪bug,��Ҫ�����������账����Ϣ��                         
                        }                                         
                    }
                }
                else { //��ʶ��Ϊ�������ȼ���Ƿ���ջ�ϣ���ʶ���¸��ַ�Ϊ[�������ǣ���[]�������Ƿ����1024�����ǣ�������䵽���ϡ�
                    // 2��֪Ϊ�εı�ʶ�������������� cout << IDENTIFIER_v << " " << arr << " ��ʶ��-����" << endl; //����
                    //��ʱch��Ϊ���������Ϊ������ջ��С�ڴ� ��=��վ��С�ڴ棬����� ��[��ջ�ϣ����ܴ��ڴ棬����
                    if (ch == '[' && in_fuc) {  //��ջ�� ֱ�Ӵ���]
                        //arr += "";                   

                        string formula = "";
                        int num = 0;
                        while ((ch = fgetc(fpin)) != ']') {
                            if (!IsFilter(ch)) {
                                formula += ch;
                            }
                        }
                        //fseek(fpin, -1L, SEEK_CUR); //�˻�һ��,����]
                        num = deal_nokh_formula(formula); //���봦���ַ���

                        cout << arr << " ������ʽ,��ֵΪ:" << num <<endl;
                        if (num > 1024) {  //Խ�磬��ͬ]һ��������������,����¼��shift_var_name;
                            shift_var_name.push_back(arr);

                            arr.insert(0, "*"); //����*����
                            arr += "= new ";
                            arr += last_state;
                            arr += "[";
                            arr += formula;
                            arr += "]";
                           
                            cout << "������ռ�ռ�����ѷ��䵽���ϣ�" << endl;

                        }
                        else {  //��Խ��,����ԭ���ı���+[��ʽ]
                            arr += "[";
                            arr += formula;
                            arr += "]";
                        }
                        fprintf(fout, "%s", arr.c_str());
                        continue;
                    }
                    else if (in_state_p) { //�ñ���Ϊָ�룬ֱ�Ӵ�������;
                        pointer.push_back(arr);
                        string pname = "";
                        bool pname_start = false;
                        while (ch != ',' && ch != ';') {
                            arr += ch;          
                            if (pname_start) {
                                if(IsUpLetter(ch) || IsLowLetter(ch) || ch == '_' || IsDigit(ch))
                                pname += ch;
                                if (IsSeparater(ch))
                                    pname_start = false;
                            }
                            if (ch == '=') {
                                pname_start = true;
                            }
                           
                            ch = fgetc(fpin);
                        }
                        pointer_pname.push_back(pname);
                        in_state_p = false;

                        fprintf(fout, "%s", arr.c_str());
                    }
                    else { //��������,ֻ�����������[��������ʽ ֮���������ַ�����
                       fprintf(fout, "%s", arr.c_str());
                    }
                }
                fprintf(fout, "%s", filter_str.c_str()); //д���м�Ĺ��˷�������������£�֮���˻�һ�񣬿�ʼ������˷���ģ���
                fseek(fpin, -1L, SEEK_CUR); //�˻�һ��
            }
        }

        else if (IsDigit(ch)) {      //�ж��Ƿ�Ϊ����
            while (IsDigit(ch) || (ch == '.' && IsDigit(fgetc(fpin)))) {
                arr += ch;
                ch = fgetc(fpin);
            }
            fseek(fpin, -1L, SEEK_CUR); //��ǰ��һ������Ϊ�ڶ������ch=.�����¸���Ϊ����
            //3������ cout << CONSTANT << " " << arr << " ������" << endl;
            fprintf(fout, "%s", arr.c_str());
        }

        else if (IsUpLetter(ch) || IsLowLetter(ch) || ch == '_') {  //�жϱ�־������ͷΪ��д    /TODO������
            while (IsUpLetter(ch) || IsLowLetter(ch) || ch == '_' || IsDigit(ch)) {
                arr += ch;
                ch = fgetc(fpin);
            }
            fseek(fpin, -1L, SEEK_CUR);
            printf("%3d  ", CONSTANT);
            //4 ��ʶ�� cout << arr << " ��ʶ��" << endl;
            fprintf(fout, "%s", arr.c_str());
        }      

        else if ((ch_num = IsOperator(ch)) != 0) {
            arr += ch;
            //5 ����� cout << ch_num << " " << arr << " �����" << endl;
            if (ch_num == 63) { //*
                if (in_state) {
                    in_state_p = true;
                 
                }
            }
            fprintf(fout, "%s", arr.c_str());
        }
        else if ((ch_num = IsSeparater(ch)) != 0) {
            arr += ch;
            //6 �ָ��� cout << ch_num << " " << arr << " �ָ���" << endl;
            //fprintf(fout, "%s", arr.c_str());
            if (in_fuc) {  //�����ں����ڲ�
                if (ch_num == 53) {
                    left_kh_num++;  //�����ڣ��������+1
                }
                else if (ch_num == 54) {
                    right_kh_num++;   //�����ڣ��Ҵ����� + 1
                    if (right_kh_num == left_kh_num) {  //�������==�Ҵ�������Ŀ����������
                        in_fuc = false;
                        left_kh_num = 0;
                        right_kh_num = 0;
                        cout << endl << "��������:" << in_fuc_name << endl << endl;
                        in_fuc_name = "";

                        if (!fuc_has_ret) { //������return,������Ҫdelete�ģ���}ǰ��Ӵ��롣
                            for (auto x: shift_var_name) {
                                fprintf(fout, "%s", "    delete[]");
                                fprintf(fout, "%s", x.c_str());
                                fprintf(fout, "%c\n", ';');
                            }
                            shift_var_name.clear();                    
                        }

                    }
                }            
            }
            if (ch_num == 51) {
                if (in_state) {
                    in_state = false;
                    in_state_p = false;
                }
            }

            fprintf(fout, "%s", arr.c_str());  //д���������Ҫdelete���ں���������}֮ǰ
        }
        else {
            arr += ch;
            //7 �޷�ʶ���ַ� cout << ch << " �޷�ʶ����ַ���" << endl;
            fprintf(fout, "%s", arr.c_str());
        }
    }

}
int main()
{
    char inFile[40] = "code.txt"; //Ҫ��������ļ���·��
    fout = fopen("result.txt", "w"); //�������ļ���ÿ��ִ�и���
    while (true) {
        // cin >> inFile;
        if ((fpin = fopen(inFile, "r")) != NULL)
            break;
        else {
            cout << "�ļ�������" << endl;
            cout << "������Դ�ļ���������·���ͺ�׺��:";
        }

    }
    cout << "------�ʷ���������------" << endl;
    analyse(fpin);
    return 0;
}


