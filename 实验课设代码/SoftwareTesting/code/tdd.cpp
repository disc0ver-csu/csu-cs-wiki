/*
** 程序名：testAdd
** 程序功能：从input输入文件中逐行输入两个整数值
**         在输入合法的情况下（范围4字节有符号int类型）打印运算成功并输出和值。
**         否则打印错误信息
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
** 函数名：isNum
** 函数功能：用来检测是否为合法输入数
** 参数名称与类型：
**  string s
** 返回值：
**  bool
*/
bool isNum(string s)
{
    bool flag = false;
    if (s == "")
        return false;
    rep(i, 0, s.size())
    {
        if (i == 0 && s[i] == '-')
            continue;
        if (s[i] < '0' || s[i] > '9')
            return false;
    }
    return true;
}

/*
** 函数名：getAdd
** 函数功能：根据两输入值获取商值
** 参数名称与类型：
**  int a
**  int b
** 返回值类型：
**  long long
*/
ll getAdd(int a, int b)
{
    return ll(a) + ll(b);
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
    cout << ("======= Start Program: testAdd ================") << endl;

#ifdef DEBUG_INPUT
    freopen("input", "r", stdin);
    // freopen("output", "w", stdout);
#endif // DEBUG_INPUT
    string a, b;
    int parseNum;
    while (cin >> a >> b)
    {
        bool a_type = isNum(a);
        bool b_type = isNum(b);
        int a_int, b_int;
        int flag = true;
        // 判断非数字的情况
        if (!a_type)
        {
            flag = false;
            std::cerr << "Error: a=" << a << " is not a num." << endl;
        }
        if (!b_type)
        {
            flag = false;
            std::cerr << "Error: b=" << b << " is not a num." << endl;
        }
        if (!flag)
        {
            cout << "Try Again." << endl;
            continue;
        }

        try
        {
            a_int = stoi(a, string::size_type());
        }
        catch (const std::out_of_range &oor)
        {
            std::cerr << "Error: Value of a out of range! " << oor.what() << endl;
            flag = false;
        }
        try
        {
            b_int = stoi(b, string::size_type());
        }
        catch (const std::out_of_range &oor)
        {
            std::cerr << "Error: Value of b out of range! " << oor.what() << endl;
            flag = false;
        }

        ll ans = getAdd(a_int, b_int);

        if (!flag)
        {
            cout << "Try Again." << endl;
            continue;
        }
        else
        {
            cout << "Correct! The value is " << ans << "." << endl;
        }
    }

    cout << "==============================================" << endl;
    return 0;
}
• 不带格式转换的程序（对照程序）
/*
** 程序名：testAddCompact
** 程序功能：做testAdd程序的对照组，检测数值类型转换的有效性
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
** 函数名：isNum
** 函数功能：用来检测是否为合法输入数
** 参数名称与类型：
**  string s
** 返回值：
**  bool
*/
bool isNum(string s)
{
    bool flag = false;
    if (s == "")
        return false;
    rep(i, 0, s.size())
    {
        if (i == 0 && s[i] == '-')
            continue;
        if (s[i] < '0' || s[i] > '9')
            return false;
    }
    return true;
}

/*
** 函数名：getAdd
** 函数功能：根据两输入值获取商值
** 参数名称与类型：
**  int a
**  int b
** 返回值类型：
**  long long
*/
ll getAdd(int a, int b)
{
    return ll(a + b);
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
    cout << ("======= Start Program: testAdd ================") << endl;

#ifdef DEBUG_INPUT
    freopen("input", "r", stdin);
    // freopen("output", "w", stdout);
#endif // DEBUG_INPUT
    string a, b;
    int parseNum;
    while (cin >> a >> b)
    {
        bool a_type = isNum(a);
        bool b_type = isNum(b);
        int a_int, b_int;
        int flag = true;
        // 判断非数字的情况
        if (!a_type)
        {
            flag = false;
            std::cerr << "Error: a=" << a << " is not a num." << endl;
        }
        if (!b_type)
        {
            flag = false;
            std::cerr << "Error: b=" << b << " is not a num." << endl;
        }
        if (!flag)
        {
            cout << "Try Again." << endl;
            continue;
        }

        try
        {
            a_int = stoi(a, string::size_type());
        }
        catch (const std::out_of_range &oor)
        {
            std::cerr << "Error: Value of a out of range! " << oor.what() << endl;
            flag = false;
        }
        try
        {
            b_int = stoi(b, string::size_type());
        }
        catch (const std::out_of_range &oor)
        {
            std::cerr << "Error: Value of b out of range! " << oor.what() << endl;
            flag = false;
        }

        ll ans = getAdd(a_int, b_int);

        if (!flag)
        {
            cout << "Try Again." << endl;
            continue;
        }
        else
        {
            cout << "Correct! The value is " << ans << "." << endl;
        }
    }

    cout << "==============================================" << endl;
    return 0;
}
