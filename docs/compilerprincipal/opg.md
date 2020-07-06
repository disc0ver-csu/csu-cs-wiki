# 算符优先文法

## 概述

**算符优先文法**（operator precedence grammar）是形式语言的一种。

从技术上讲，算符优先文法是上下文无关文法（context free grammar，也即 2 型文法）的一种。在《程序设计语言编译原理（陈火旺 第三版）》一书中，我们在**语法分析------自下而上分析**中学习到该文法。

??? note "补充：语言层次关系"

    n 型之间文法的关系，如果你上的是 XDZ 老师的课程，相信他会给你们讲解的，这里稍作补充。

    - 3型：正规语言（Regular Language，RL），是有限自动机所识别的语言类。
    - 2型：上下文无关语言（Context Free Language，CFL），是下推自动机识别的语言类。
    - 1型：上下文有关（相关）语言（Context Sensitive Language，CSL），是有界自动机识别的语言类（这个笔者自己查的，待确定）。
    - 0型：短语语言，一些地方又称无限制形式语言，是图灵机识别的语言类。

    从3型到0型，是逐层被包含的关系，即RL被CFL包含，CFL被CSL包含。至于为什么这么划分，请读者自行学习（~~因为我不懂~~）。

## 概念回顾

自下而上语法分析中有一些核心概念必须掌握（或者需要你去复习一下）：

- 文法
- 推导
- 规范推导
- 归约
- 规范规约
- 句柄
- 短语
- 直接短语

~~好吧其实你真的需要回顾不少~~

其实算符优先文法并不走规范归约的过程（~~所以你上面很多复习是没直接作用的~~），上述内容有助于你**更好的理解**算符优先文法，以及之后的 LR(0)文法。

## 优先关系与优先关系表

在后面的定义中，$a$、$b$代表任意终结符；$P$、$Q$、$R$代表任意非终结符；$\cdots$代表由终结符和非终结符组成的任意序列，包括空字。

先来介绍算符文法：

!!! summary "算符文法"

    一个文法，如果它的任一产生式的有部都不含两个相继（并列）的非终结符，即不含如下形式的产生式右部：

    $$\cdots QR \cdots$$

    则我们称该文法为**算符文法**。

算符优先文法是直观的，其关键在于比较相邻终结符 a 与 b 的优先关系，**优先关系**如下描述：

- $a=b$：当且仅当文法$G$中含有形如$P \rightarrow \cdots ab \cdots$或$P \rightarrow aQb \cdots$的产生式
- $a<b$：当且仅当文法$G$中含有形如$P \rightarrow \cdots aR \cdots$的产生式，而$R \stackrel{+}{\Rightarrow} b \cdots$或$R \stackrel{+}{\Rightarrow} Qb \cdots$
- $a>b$：当且仅当文法$G$中含有形如$P \rightarrow \cdots Rb \cdots$的产生式，$R \stackrel{+}{\Rightarrow} \cdots a$或$R \stackrel{+}{\Rightarrow} \cdots aQ$

那么就可以介绍本文的主角，算符优先文法了：

!!! summary "算符优先文法"

    如果一个算符文法$G$中的任何终结符对$(a,b)$至多只满足下述三关系之一：

    $$a=b, a<b,a>b$$

    则我们称$G$是一个算符优先文法。

而**算符优先表**就是描述终结符对$(a,b)$关系的表格。

听起来有点玄乎哈，我们来举个例子，比如下面这个表格，给出的就是四则运算（左结合）加括号的算符优先表。

| bef\after | \+  | \-  | \*  |  /  |  (  |  )  | \#  |
| :-------: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
|    \+     |  >  |  >  |  <  |  <  |  <  |  >  |  >  |
|    \-     |  >  |  >  |  <  |  <  |  <  |  >  |  >  |
|    \*     |  >  |  >  |  >  |  >  |  <  |  >  |  >  |
|     /     |  >  |  >  |  >  |  >  |  <  |  >  |  >  |
|     (     |  <  |  <  |  <  |  <  |  <  |  =  |     |
|     )     |  >  |  >  |  >  |  >  |     |  >  |  >  |
|    \#     |  <  |  <  |  <  |  <  |  <  |     |  =  |

而它所对应的文法如下：

- $E \rightarrow E+T | E-T |T$
- $T \rightarrow T*F | T/F |F$
- $F \rightarrow (E) | i$

细心的同学可能发现了，$i$作为终结符并没有在上表中，这是不应该的，不过在笔者自己的实现过程中，输入部分是单独接口从输入流读取并进行转化识别，不会单独对数值进行一次归约（笔者觉得可以省略，因为$i$优先级最高，输入下个字符便会立即归约），或许这里有些像词法分析当作语法分析的一个部分吧（待同学们指证、补充）。

那么有了优先表，我们就可以进行算符优先分析了，不过别急，有一个问题我们并没有解释清楚，这个优先关系表怎么构造来的？

## 优先关系表的构造

Well，如果你能理解上一小节的内容，你或许会说；当然是根据优先关系来确定优先关系表啊！

话不错，但是不够细致，我们在这里可不是讨论**可能性**的问题，而是在讨论**可行性**的问题。如果仅凭肉眼扫描，逐个判断终结符对$(a,b)$是什么关系，你有$n^{2}$对，且在肉眼扫描过程中，难以在关系判断时保证**不缺漏**哪个产生式。随着产生式的增多，复杂度会进一步增大。实际上，我们希望能找到一个从文法**自动构造**算符优先表的算法。

??? not "补充：和算符文法有关的题外话"

    从优先级关系中我们不难get到，**优先关系**实际上**描述了相邻终结符的归约顺序**，以$a>b$为例，要求有$S$初始符号，可推$\cdots Rb$而$R$这个非终结符要可推$\cdots a$，那么也就是说要先归约$\cdots a$到$R$，然后$\cdots Rb$再继续往上归约，也即$a$先于$b$归约。

    一言以蔽之：文法终结符的优先级别是**规定它在归约时归约的先后次序**，先归约的终结符优先级高。

    再回过头来看算符文法，还记得算法优先文法的大前提，算符文法的要求嘛？即文法不含如下形式的产生式右部：

    $$\cdots QR \cdots$$

    这里可以稍微解释一下为什么了。设想，如文法中有$\cdots QR \cdots$，则无法确定Q和R产生的终结符谁会与开始符号更近或更远，因此不允许有这种形式，任何终结符对的优先级只有一种关系，因此，在文法中不允许有终结符对交错出现在不同层次上。（Well，这段话搬运自xdz老师的ppt，~~我也没太明白~~，只能稍微get不能比较先后关系，欢迎同学们讨论、指证）。

算法描述如下：

- 通过检查$G$的每个产生式的每个候选式，可找出所有满足$a=b$的终结符对（线性扫描一遍）；
- 为了找出所有满足关系$a<b$和$a>b$的终结符对，首先对$G$的每个非终结符 P 构造两个集合$FIRSTVT(P)$和$LASTVT(P)$;

  - $FIRSTVT(P) = \{a | P \stackrel{+}{\Rightarrow}  a \cdots  \quad or \quad P \stackrel{+}{\Rightarrow} Qa \cdots , a \in V_T , Q \in V_N\}$

  - $LASTVT(P) = \{a | P \stackrel{+}{\Rightarrow} \cdots a   \quad or \quad P \stackrel{+}{\Rightarrow} \cdots , a \in V_T , Q \in V_N\}$

- 与之对应的规则为（以 FIRSTVT 为例）

  - 若有产生式$P \rightarrow a \cdots$或者$P \rightarrow Qa \cdots$，则$a \in FIRSTVT(P)$
  - 若有$a \in FIRSTVT(Q)$，且有产生式$P \rightarrow Q \cdots$，则$a \in FIRSTVT(P)$

- 构造上述两集合的方法（不动点算法），我的描述可能不大好理解，还请各位同学参考原 PPT 或书籍：初始各个非终结符 P 的$FIRSTVT$/$LASTVT$集合为空，按规则 1 初始化填入产生式本身确定的终结符，然后一轮一轮扫描，按上述规则 2 判断上一轮新填入$Q$对应集合的终结符是否会“传递”到其他非终结符的集合中。如此循环直至所有集合都不再扩张。
- 有了 $FIRSTVT(P)$和 $LASTVT(P)$之后，就可以通过检查每个产生式的候选式，来确定终结符之间的$<$和$>$关系，即：构造出分析表。

  - 存在产生式右部为：$\cdots aP \cdots$，那么$\forall b\in FIRSTVT(P)$,$a < b$
  - 存在产生式右部为：$\cdots Qb \cdots$，那么$\forall a \in LASTVT(Q)$,$a > b$

## 算符优先分析

有了算符优先表，就可以进行算符优先分析了。算符优先分析中的归约涉及下面两个核心概念

- **素短语**：至少含有一个终结符，除了它自身外不再含任何更小的素短语。
- **最左素短语**：处于句型最左边的那个素短语；

> 注：素短语不是句柄（由于要含有至少一个终结符，它的“体积”要比句柄大一些），所以算符优先算法**不是**规范规约方法。

考虑算符优先文法，我们把句型（括在两个#之间）的一般形式写成：

$$N_1a_1N_2a_2 \cdots N_na_nN_{n+1}$$

那我们的核心任务就是，找到**最左素短语**并把它归约掉就可以了！怎么找呢？一个算符优先文法$G$的任何句型的最左素短语是满足如下条件的最左子串$N_ja_j \cdots N_ia_iN_{i+1}$

$$a_{j-1} < a_j$$

$$a_j = a_{j+1} , \cdots , a_{i-1} = a_i$$

$$a_i > a_{i+1}$$

后面就是编程实现了，笔者针对《程序设计语言编译原理（陈火旺第三版）》中给出的算法描述写了一个 C++版本，核心逻辑如下：

??? note "C++"

    ```C++
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
    ```

完整代码学习请访问[代码仓库](https://github.com/leo6033/CSU_CS_Experiment/tree/master/%E5%AE%9E%E9%AA%8C%E8%AF%BE%E8%AE%BE%E4%BB%A3%E7%A0%81/CompilerPrincipal)

这篇文章是笔者学完编译原理一年以后写的，其中有很多有错误或表达不规范的地方，欢迎同学们讨论、指证。
