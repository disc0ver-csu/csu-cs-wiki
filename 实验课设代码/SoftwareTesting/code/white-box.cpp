/*
** 程序名：testLeapYear
** 程序功能：从input输入文件中逐行判断年份是否为闰年年份（int范围）
** 作者：Edwardzcn
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<string, string> pss;
#define rep(i, a, n) for (int i = a; i < n; ++i)
#define per(i, a, n) for (int i = n - 1; i >= a; --i)

#define DEBUG_INPUT DEBUG_INPUT

/*
** 枚举类型：CHECK_TYPE
** 枚举说明：用来表征rawInput检测后的类型
** 作者：Edwardzcn
*/
enum CHECK_TYPE
{
    NO_NUM,
    POSITIVE_NUM,
    NEGATIVE_NUM
};

/*
** 函数名：checkInput
** 函数功能：用来检测rawInput
** 参数名称与类型：
**  string s
** 返回值：
**  int
*/
int checkInput(string s)
{
    if (s == "")
        return CHECK_TYPE::NO_NUM;

    bool flag1 = false;
    if (s[0] == '-')
    {
        flag1 = true;
        rep(i, 1, s.size())
        {
            if (s[i] < '0' || s[i] > '9')
            {
                return CHECK_TYPE::NO_NUM;
            }
        }
    }
    else
    {
        rep(i, 0, s.size())
        {
            if (s[i] < '0' || s[i] > '9')
            {
                return CHECK_TYPE::NO_NUM;
            }
        }
    }
    if (flag1)
        return CHECK_TYPE::NEGATIVE_NUM;
    else
        return CHECK_TYPE::POSITIVE_NUM;
}

/*
** 函数名：checkLeapYear
** 函数功能：根据输入年份判断其是否为闰年
** 参数名称与类型：
**  int year
** 返回值类型：
**  bool
*/
bool checkLeapYear(int year)
{
    // 判断闰年的核心逻辑
    if (year % 400 == 0 || year % 4 == 0 && year % 100 != 0)
    {
        return true;
    }
    return false;
}

/*
** 函数名：main
** 函数功能：主函数，入口
** 参数名称与类型：
**  int argc
**  char* argv[]
** 返回值类型：
**  int
*/
int main(int argc, char *argv[])
{
    cout << ("======= Start Program: testLeapYear ==========\n");

#ifdef DEBUG_INPUT
    freopen("input", "r", stdin);
    // freopen("output", "w", stdout);
#endif // DEBUG_INPUT
    string rawInput;
    int parseNum;
    while (cin >> rawInput)
    {
        // 调用
        int ans = checkInput(rawInput);
        switch (ans)
        {
        case CHECK_TYPE::NO_NUM:
            cout << "Input:" << rawInput << " is not a number." << endl;
            break;
        case CHECK_TYPE::NEGATIVE_NUM:
            cout << "Input:" << rawInput << " is not positive." << endl;
            break;
        case CHECK_TYPE::POSITIVE_NUM:
            parseNum = atoi(rawInput.c_str());
            if (checkLeapYear(parseNum))
                cout << "YES! Year:" << parseNum << " is a leap year." << endl;
            else
                cout << "NO! Year:" << parseNum << " is not a leap year." << endl;
            break;
        default:
            break;
        }
    }

    cout << "==============================================" << endl;
    return 0;
}