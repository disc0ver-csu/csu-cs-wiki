#include <bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f //表示无限大没有定义
typedef long long ll;
// #define DEBUG DEBUG

//针对文法
// E->E+T|E-T|T
// T->T*F|T/F|F
// F->(E)|i

// 采用双栈的形式
char optStack[100]; //符号栈
ll numStack[100];   //数字栈
// 两个指针
int optPtr = 0; //符号栈指针
int numPtr = 0; //数字栈指针
// 一个用来控制输入的输入字符指针
int strPtr = 0;

//手动构造运算符->index映射  返回一个映射泛型
map<char, int> initMapToIndex(char *vtList, int vtNum)
{
    map<char, int> mapToIndex;
    mapToIndex.clear();
    for (int i = 0; i < vtNum; i++)
    {
        mapToIndex.insert(make_pair(vtList[i], i));
    }
    return mapToIndex;
}

//插入新运算符 返回该运算符的index
int addMapToIndex(map<char, int> &mapToIndex, char newVT)
{
    int sizeOfMap = mapToIndex.size();
    mapToIndex.insert(make_pair(newVT, sizeOfMap));
    return sizeOfMap;
}

//手动构造优先表  这里还没有写完构造firstvt和lastvt的方法
void initPriorityTable(int ptable[][100], int numVT)
{
    //  { '+', '-', '*', '/', '(', ')', '#' };

    // 不合法
    // ptable[5][4] = ptable[6][5] = ptable[4][6] = 2;
    ptable[4][5] = ptable[6][6] = 0;

    ptable[0][0] = ptable[0][1] = ptable[0][5] = ptable[0][6] = 1;
    ptable[1][0] = ptable[1][1] = ptable[1][5] = ptable[1][6] = 1;
    ptable[2][0] = ptable[2][1] = ptable[2][2] = ptable[2][3] = ptable[2][5] = ptable[2][6] = 1;
    ptable[3][0] = ptable[3][1] = ptable[3][2] = ptable[3][3] = ptable[3][5] = ptable[3][6] = 1;
    // ptable[4] '('没有 大于关系
    ptable[5][0] = ptable[5][1] = ptable[5][2] = ptable[5][3] = ptable[5][5] = ptable[5][6] = 1;
    // ptable[6] '#'没有 大于关系
    ptable[0][2] = ptable[0][3] = ptable[0][4] = -1;
    ptable[1][2] = ptable[1][3] = ptable[1][4] = -1;
    ptable[2][4] = -1;
    ptable[3][4] = -1;
    ptable[4][0] = ptable[4][1] = ptable[4][2] = ptable[4][3] = ptable[4][4] = -1;
    ptable[6][0] = ptable[6][1] = ptable[6][2] = ptable[6][3] = ptable[6][4] = -1;
}

bool reduction(int st, int fn)
{
    if (fn - st == 0)
    {
        // 普通
        int num2 = numStack[--numPtr];
        int num1 = numStack[--numPtr];
        switch (optStack[fn])
        {
        case '+':
            numStack[numPtr++] = num1 + num2;
            break;
        case '-':
            numStack[numPtr++] = num1 - num2;
            break;
        case '*':
            numStack[numPtr++] = num1 * num2;
            break;
        case '/':
            numStack[numPtr++] = num1 / num2;
            break;
        default:
            break;
        }
        return true;
    }
    else if (fn - st == 1 && optStack[st] == '(' && optStack[fn] == ')')
    {
        // 特殊
        // 直接返回  等价于弹出两个符号栈，不对数值栈操作
        return true;
    }
    else
    {
        // Error
        return false;
    }
}

void initPtr()
{
    optPtr = 0;
    numPtr = 0;
    strPtr = 0;
}

stringstream getStringSteamfromStr(const string &checkString)
{
    return stringstream(checkString);
}

int getNextInput(const string &ss, int &pos, char &opt, ll &num)
{
    if (ss.length() == pos)
    {
        return 0;
    }
    int start = pos;
    while (ss.length() > pos && ss[pos] >= '0' && ss[pos] <= '9')
    {
        //连续数字
        pos++;
    }
    if (start == pos)
    {
        opt = ss[pos++];
#ifdef DEBUG
        cout << "getNextInput - operation = " << opt << endl;
#endif // DEBUG
        return 1;
    }
    else
    {
        num = stoll(ss.substr(start, pos - start));
#ifdef DEBUG
        cout << "getNextInput - number = " << num << endl;
#endif // DEBUG
        return 2;
    }
}

bool easyCheck(int ptable[][100], map<char, int> &mapToIndex, const string &checkString)
{
    // // 获取字符流
    // stringstream ss = getStringSteamfromStr(checkString);
    initPtr();
    cout << "inputstr=" << checkString << endl;
    char a;   // 字符接收
    ll num;   // 数值接收
    int type; // 接收类型
    // ss >> a;
    // cout << "a=" << a << endl;
    type = getNextInput(checkString, strPtr, a, num);
    // checkStack[0] = a;
    optStack[optPtr++] = a;

    while ((type = getNextInput(checkString, strPtr, a, num)) != 0)
    {
        // 纸带向机器内输出一个字符，后面用getinput代替（用来输入多字符）
        if (type == 2)
        {
            // 输入为数字
            numStack[numPtr++] = num;
            continue;
        }
        // 输入为字符
        if (mapToIndex.count(a) == 0)
        {
            //字符输入不合法
            cout << "Error 1: Checkstring has forbidden character. (Syntax Error)" << endl;
            return false;
        }
        // 判断两个终结符的优先级关系
        int opt_bef_id = mapToIndex[optStack[optPtr - 1]]; // 栈顶符号的map id
        int opt_aft_id = mapToIndex[a];                    //要入栈的符号的map id
        int opt_now_id;
        // 优先级关系
        int opt_ralation = ptable[opt_bef_id][opt_aft_id];
        // 素短标志位置
        int final_pos, start_pos;

        while (opt_ralation == 1)
        {
            final_pos = optPtr - 1;
            do
            {
                opt_now_id = opt_bef_id;
                start_pos = optPtr - 1;
                optPtr--;
                opt_bef_id = mapToIndex[optStack[optPtr - 1]];
            } while (ptable[opt_bef_id][opt_now_id] != -1);
            // 规约
            // 素短语
            //  opt_now <   opt_bef  > opt_aft
            // 常见情况
            // '+'(opt_now)   '*'(opt_bef)   '+'(opt_aft)   =>  处理的素短语为   num opt num
            // 不常见情况 上述do-whilt 两轮（有相等）
            // '-'(opt_now)   '('(opt_bef)   ')'(opt_aft)   =>  处理的素短语为    opt num opt
            opt_ralation = ptable[opt_bef_id][opt_aft_id];
            bool reductionFlag = reduction(start_pos, final_pos);
            if (reductionFlag)
            {
#ifdef DEBUG
                cout << "Success reduction!" << endl;
#endif // DEBUG
            }
            else
            {
                cout << "Error 3: Reduction error. (Syntax Error)" << endl;
                return false;
            }
        }

        if (opt_ralation == -1 || opt_ralation == 0)
        {
            optStack[optPtr++] = a;
        }
        else
        {
            cout << "Error 2: Checkstring has conflict operator. (Syntax Error)" << endl;
            return false;
        }
        if (a == '#')
        {
            break;
        }
    }
    return true;
}
int main()
{
    char rawVtList[10] = {'+', '-', '*', '/', '(', ')', '#'};
    // char rawVtList[10] = { '+', '*', '~', 'i', '(', ')' };
    int rawNum = 6;
    int priorityTable[100][100];
    memset(priorityTable, INF, sizeof(priorityTable));
    map<char, int> mapToIndex = initMapToIndex(rawVtList, rawNum);
    addMapToIndex(mapToIndex, '#');
    initPriorityTable(priorityTable, mapToIndex.size());

    // vector<string> testString;
    // testString.push_back("#我看看Zou同学是不是傻");
    // testString.push_back("#2+3+4+5+1#");
    // for (int i = 0; i < testString.size(); i++) {
    //     cout << "======== Begin OPG Test ========" << endl;
    //     if (easyCheck(priorityTable, mapToIndex, testString[i])) {
    //         cout << "Accept! ans=" << numStack[0] << endl;
    //     }
    //     cout << "======= Finish OPG Test ========" << endl
    //          << endl
    //          << endl;
    // }
    string rawInput;
    cout << "======== Start Program  ========" << endl;
    cout << "Your input ('q' to quit): ";
    while (cin >> rawInput && rawInput[0] != 'q')
    {
        cout << "======== Begin OPG Test ========" << endl;
        if (easyCheck(priorityTable, mapToIndex, rawInput))
        {
            cout << "Accept! ans=" << numStack[0] << endl;
        }
        cout << "======= Finish OPG Test ========" << endl
             << endl
             << endl;

        cout << "Your input ('q' to quit): ";
    }
    cout << "========= End Program  =========" << endl;

    char temp;
    cin >> temp;
}