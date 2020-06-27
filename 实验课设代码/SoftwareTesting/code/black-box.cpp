/*
** 程序名：testDevide
** 程序功能：从input输入文件中逐行输入两个值，第一个值做被除数，第二个值做除数，
**         在输入合法的情况下（范围-100～100）打印运算成功并输出商值。
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
#define LOW_BOUND -100.0
#define UP_BOUND 100.0
#define EPS 1e-10

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
        if (s[i] == '.')
        {
            if (!flag)
                flag = true;
            else
                return false;
        }
        else if (s[i] < '0' || s[i] > '9')
            return false;
    }
    return true;
}

/*
** 函数名：getDevide
** 函数功能：根据两输入值获取商值
** 参数名称与类型：
**  double a
**  double b
** 返回值类型：
**  double
*/
double getDevide(double a, double b)
{
    return a / b;
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
    string a, b;
    int parseNum;
    while (cin >> a >> b)
    {
        // cout << "# " << a << " " << b << endl;
        // 调用
        bool a_type = isNum(a);
        bool b_type = isNum(b);
        double a_double, b_double;
        int flag = true;
        // 判断非数字的情况
        if (!a_type)
        {
            flag = false;
            cout << "Error: a=" << a << " is not a num." << endl;
        }
        if (!b_type)
        {
            flag = false;
            cout << "Error: b=" << b << " is not a num." << endl;
        }
        if (!flag)
        {
            cout << "Try Again." << endl;
            continue;
        }
        stringstream ss;
        // ss.clear();
        // ss << a;
        // ss >> a_double;
        // ss.clear();a.size()
        // ss << b;
        // ss >> b_double;
        a_double = stod(a, string::size_type());
        b_double = stod(b, string::size_type());
        // cout << "# " << a_double << " " << b_double << endl;
        // 判断超出数字限制
        if (a_double < LOW_BOUND + EPS || a_double > UP_BOUND - EPS)
        {
            flag = false;
            cout << "Error a=" << a_double << " out of bound." << endl;
        }
        if (b_double < LOW_BOUND + EPS || b_double > UP_BOUND - EPS)
        {
            flag = false;
            cout << "Error b=" << b_double << " out of bound." << endl;
        }
        // 对0的判断
        if (abs(b_double) < EPS)
        {
            flag = false;
            cout << "Error b=" << 0 << " undevisable." << endl;
        }
        if (!flag)
        {
            cout << "Try Again." << endl;
            continue;
        }
        // 进行运算
        double ans = getDevide(a_double, b_double);
        cout << "Correct! The value is " << ans << " ." << endl;
    }

    cout << "==============================================" << endl;
    return 0;
}