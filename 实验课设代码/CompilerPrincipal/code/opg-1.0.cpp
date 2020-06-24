#include <bits/stdc++.h>
using namespace std;
#define INF 0x3f3f3f3f //表示无限大没有定义
// #define DEBUG DEBUG
//针对文法
// E->E+T|T
// T->T*F|F
// F->P~F|P // 注意这个是右结合
// P->(E)|i

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
    //  { '+', '*', '~', 'i', '(', ')', '#' };
    ptable[4][5] = ptable[6][6] = 0;

    ptable[0][0] = ptable[0][5] = ptable[0][6] = 1;
    ptable[1][0] = ptable[1][1] = ptable[1][5] = ptable[1][6] = 1;
    ptable[2][0] = ptable[2][1] = ptable[2][5] = ptable[2][6] = 1;
    // ptable[2][0] = ptable[2][1] = ptable[2][2] = ptable[2][5] = ptable[2][6] = 1;
    ptable[3][0] = ptable[3][1] = ptable[3][2] = ptable[3][5] = ptable[3][6] = 1;
    ptable[5][0] = ptable[5][1] = ptable[5][2] = ptable[5][5] = ptable[5][6] = 1;

    ptable[0][1] = ptable[0][2] = ptable[0][3] = ptable[0][4] = -1;
    ptable[1][2] = ptable[1][3] = ptable[1][4] = -1;
    ptable[2][2] = ptable[2][3] = ptable[2][4] = -1;
    // ptable[2][3] = ptable[2][4] = -1;
    ptable[4][0] = ptable[4][1] = ptable[4][2] = ptable[4][3] = ptable[4][4] = -1;
    ptable[6][0] = ptable[6][1] = ptable[6][2] = ptable[6][3] = ptable[6][4] = -1;
}

bool easyCheck(int ptable[][100], map<char, int> &mapToIndex, string checkString)
{
    //检查栈
    char checkStack[100];
    //字符流
    stringstream ss(checkString);

    //初始化栈压入#
    int k = 0, j;
    char a, q;
    ss >> a;
    checkStack[0] = a;
    cout << checkString << endl;
    while (ss >> a)
    {
        // 纸带向机器内输出一个字符，后面用getinput代替（用来输入多字符）
        j = k;
        if (mapToIndex.count(checkStack[k])) {
            // j指向最后一个终结符
            j = k;
        } else {
            // j指向最后一个终结符
            j = k - 1;
        }
        //对a做一下处理
        if (a >= '0' && a <= '9')
        {
            a = 'i'; //表示为字符
        }
        // 判断合法输入
        if (mapToIndex.count(a) == 0)
        {
            //不合法
            cout << "Error 1: Checkstring has forbidden character. (Syntax Error)" << endl;
            return false;
        }
        // 判断两个终结符的优先级关系
        int relation = ptable[mapToIndex[checkStack[j]]][mapToIndex[a]];
        while (relation == 1)
        {
            // >
            int cnt = 0;
            do
            {
                q = checkStack[j];
                if (mapToIndex.count(checkStack[j - 1]))
                {
                    j -= 1;
                }
                else
                {
                    j -= 2;
                }

            } while (ptable[mapToIndex[checkStack[j]]][mapToIndex[q]] != -1);
            //规约
            k = j + 1;
            checkStack[k] = 'X';
            relation = ptable[mapToIndex[checkStack[j]]][mapToIndex[a]];
            // Outprint
            for (int temp = 0; temp <= k; temp++)
                cout << checkStack[temp];
            // cout << "  after simplize" << endl;
            cout << "   after simplize  j=" << j << "  k=" << k << "  a=" << a << endl;
        }
        //update relation
        if (relation == -1 || relation == 0)
        {
            k = k + 1;
            checkStack[k] = a;
        }
        else
        {
            cout << "Error 2: Checkstring has conflict operator. (Syntax Error)" << endl;
            return false;
        }
        if (a == '#')
        {
            //TODO
            break;
        }
    }
    return true;
}
int main()
{
    char rawVtList[10] = {'+', '*', '~', 'i', '(', ')', '#'};
    // char rawVtList[10] = { '+', '*', '~', 'i', '(', ')' };
    int rawNum = 6;
    int priorityTable[100][100];
    memset(priorityTable, INF, sizeof(priorityTable));
    map<char, int> mapToIndex = initMapToIndex(rawVtList, rawNum);
    addMapToIndex(mapToIndex, '#');
    initPriorityTable(priorityTable, mapToIndex.size());
    // for (int i = 0; i < 7; i++) {
    //     for (int j = 0; j < 7; j++) {
    //         cout << priorityTable[i][j] << " ";
    //     }
    //     cout << endl;
    // }
    //okok!
    vector<string> testString;
    testString.push_back("#1+2*3+(5*6)#");
    testString.push_back("#3*4+(2*5+7#");
    testString.push_back("#6~2+5*3+7*#");
    testString.push_back("#5+(7)#");
    testString.push_back("#5+((7))#");
    for (int i = 0; i < testString.size(); i++)
    {
        if (easyCheck(priorityTable, mapToIndex, testString[i]))
            cout << "accept" << endl;
    }

    char temp;
    cin >> temp;
}