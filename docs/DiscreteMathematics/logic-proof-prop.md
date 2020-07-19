# 逻辑与证明——命题与逻辑等价

## 命题

> A proposition is a declarative sentence that is either true or false, but not both.
>
> 命题是一个陈述句。可以是真或假，但不能无法判断。

命题是**陈述句**，需要具备逻辑真假的含义。小时候学习的诸如疑问句、感叹句、祈使句，都不可作为命题。考虑以下四个句子。

1. What time is it?
2. Read this carefully.
3. $x + 1 = 2$
4. $x + y = z$

其中句 1 和句 2 根据定义都不是命题，句 3 和句 4 也不是命题，因为你无法判断其真假。我们使用**命题表示符**（Statement Variable）来符号化命题：$p,q,r,s$

### 联结词

命题可通过**联结词**（Connectives）相互结合构成新的命题，有以下：

1. 否定（Negation， NOT）
2. 合取（Conjunction，AND）
3. 析取（Inclusive Disjunction，OR）
4. 异或（Exclusive Disjunction，XOR）
5. 蕴含（Implication）
6. 双条件（Biconditional）

其中 5 和 6 被称为条件式的命题，因为与自然语言中的“因果逻辑”相关。针对条件式命题，还有一些不常用符号的方式用于描述从原有命题构造新命题的过程，比如逆命题形式（Converse），逆否命题形式（Contrapositive），否命题形式（Inverse），构造规则如下表：

|             命题              |      形式      |
| :---------------------------: | :------------: |
|       $p \rightarrow q$       |  Implication   |
|       $q \rightarrow p$       |    Converse    |
| $\lnot q \rightarrow \lnot p$ | Contrapositive |
| $\lnot p \rightarrow \lnot q$ |    Inverse     |

!!! note "关于双条件"

    其实双条件就是我们过去常说的“当且仅当”，即英文里的if and only if。但双条件在自然语言中的表达常不是精确的，比如有时候用“如果...就”来代替“当且仅当”，这导致双条件与蕴含有时会分不清。由于自然语言中的这种不精确性，我们需要假设自然语言中的条件语句是否隐式包括其逆，从而区分其是蕴含还是双条件。

### 优先级

|      操作符       | 优先级别 |
| :---------------: | :------: |
|      $\lnot$      |    1     |
|      $\land$      |    2     |
|      $\lor$       |    3     |
|   $\rightarrow$   |    4     |
| $\leftrightarrow$ |    5     |

### 真值表与计算机表示

对于合成的命题，按优先级计算部分再合并即可。同时计算机中用 1 比特的取值来表示逻辑真$T$或假$F$。计算机通过改变位状态的 0/1 来（位操作）对应一联结词。

## 命题等价

数学论证中使用的一种重要的步骤是用另一个具有相同真值的命题替换一个命题。因此，在构造数学论证时，广泛采用与给定复合命题具有相同真值的命题的方法。（暴力的方法，枚举完整的真值表，判断两命题真值表是否完全对应）

要介绍后面的逻辑等价，我们需要先引入**重言式**（tautology，永真式）的概念，相应的概念还有**矛盾式**（永假式）和**偶然式**。

- **重言式**：复合命题恒真。
- **矛盾式**：符合命题恒假。
- **偶然式**：复合命题既不是恒真又不恒假，习惯性我们就用偶然式称呼这类命题。

### 逻辑等价

**定义**：如果两个偶然式$p$和$q$满足$p \leftrightarrow q$是重言式（永真），则我们使用符号$\equiv$来表示$p$和$q$是**逻辑等价**的。

!!! alarm "关于逻辑等价符号"

    需要注意，$\equiv$并不是一个逻辑联结符号，而是“$p \leftrightarrow q$是永真式”的简化表达。习惯上我们有时会使用符号$\Leftrightarrow$代替$\equiv$（即等价符号）。

定律

下表是常见的基本等价式，我们也常用 XX 定律描述它们。

| 等价式                                                                                                                  | 名称                          |
| :---------------------------------------------------------------------------------------------------------------------- | :---------------------------- |
| $p \land \mathrm{T} \equiv p \\ p \lor \mathrm{F} \equiv p$                                                             | 同一律（Identity laws）       |
| $p \lor \mathrm{T} \equiv T \\ p \land \mathrm{F} \equiv F$                                                             | 零律（Domination laws）       |
| $p \lor p \equiv p \\ p \land p \equiv p$                                                                               | 幂等律（Idempotent laws）     |
| $\lnot(\lnot p) \equiv p$                                                                                               | 对合律（Double negation law） |
| $p \lor q \equiv q \lor p \\ p \land q \equiv q \land p$                                                                | 交换律（Commutative laws）    |
| $(p \lor q) \lor r \equiv p \lor ( q \lor r ) \\ (p \land q) \land r \equiv p \land ( q \land r)$                       | 结合律（Associative laws）    |
| $(p \lor q) \land r \equiv (p \lor  r)  \land ( q \lor r ) \\ (p \land q) \lor r \equiv (p \land  r)  \lor (q \land r)$ | 分配律（Distributive laws）   |
| $\lnot (p \land q) \equiv \lnot p \lor \lnot q \\ \lnot (p \lor q) \equiv p \land \lnot q$                              | 德摩根律（De Morgan's laws）  |
| $p \lor (p \land q) \equiv p \\ p \land (p \lor q) \equiv p$                                                            | 吸收率（Absorption laws）     |
| $p \lor \lnot p \equiv \mathrm{T} \\ p \land \lnot p \equiv \mathrm{F}$                                                 | 否定律（Negation laws）       |

另外还有跟蕴含式和双条件式相关的逻辑等价式子，这里举几个常见的进行讲述，其余等价式请查阅书籍。

$$p \rightarrow q \equiv \lnot p \lor q \tag{1}$$

$$p \rightarrow q \equiv \lnot p \rightarrow \lnot p \tag{2}$$

$$p \leftrightarrow q \equiv (p \rightarrow q) \land (q \rightarrow p) \tag{3}$$

$$p \leftrightarrow q \equiv \lnot p \leftrightarrow \lnot q \tag{4}$$

!!! note "Tips 1"

    式 1 和式 3 告诉我们可用$\land$、$\lor$、$\lnot$来表示所有带蕴含和双条件的命题。

!!! note "Tips 2"

    式2 表示的是**逆否命题**与原始命题的等价性。这给我们提供了一种思路，即通过证明逆否命题来证明原命题

!!! note "Tips 3"

    式4似乎比较难理解有什么用，但可以通过以下几步来解释。

    - $p \leftrightarrow q \equiv \lnot p \leftrightarrow \lnot q$
    - $\lnot p \leftrightarrow \lnot q \equiv ( \lnot p \rightarrow \lnot q) \land ( \lnot q \rightarrow \lnot p)$

    所以，使用式4与式3等于我们用两次逆否命题来证明充分性和必要性。

证明逻辑等价的方法：使用**真值表**或者应用已有的**逻辑等价式**进行化简

证明逻辑不等价：优先化简，例举一个边界情况

### 命题的可满足性

如果命题中的一些符号变量被赋值使得命题为真，则该命题是**可满足的**（satisfied），如果不存在这样的赋值，则称命题为**不可满足的**（unsatisfied）。

联想“数独”游戏。

更多详细内容请参见 Discrete Mathematics and Its Applications (7th Edition) 1.3

<!-- TODO -->

待补充

### 解决可满足性问题

??? note "Solving Satisfiability Problems"

    A truth table can be used to determine whether a compound proposition is satisfiable, or equiv-alently, whether its negation is a tautology (see Exercise 60). This can be done by hand fora compound proposition with a small number of variables, but when the number of variablesgrows, this becomes impractical. For instance, there are $2^{20}  = 1048576$ rows in the truth ta-ble for a compound proposition with $20$ variables. Clearly, you need a computer to help youdetermine, in this way, whether a compound proposition in $20$ variables is satisfiable

