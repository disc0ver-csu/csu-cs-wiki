# 逻辑与证明

## 为何学习逻辑与证明

<!-- TODO -->

要理解数学，我们必须理解正确的数学论证过程——即“证明”。而学习证明的推理过程则是“逻辑”。虽然在概论部分阐述离散数学各章节内容相对独立，但是本章是个例外。推理与证明被应用于全书，并且不仅离散数学范畴，任何数学推理过程中都会使用到本章介绍的知识。

> Logic = the study of correct reasoning
>
> Logic is the basis of all mathematical reasoning

很多人能直观理解数学推理的重要性，但不甚了解其对计算机科学的重要性。可能部分同学仅以为我们只会在算法正确性、复杂度证明中见到数学推理。事实上，算法中它意蕴足够深远，且推理证明还可用来定义的程序规范，并验证程序的具体实现符合其规范，从而保证系统的“绝对”安全。当然这就是另一个故事了（形式化验证）。总之通过学习逻辑与证明，我们可以：

- 在**数学**领域：证明定理。
- 在**计算机科学**领域：证明程序的执行会怎样。

## 命题（Proposition）

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

### 逻辑等价（Logical Equivalences）

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

### 命题的可满足性（Propositional Satisfiability）

如果命题中的一些符号变量被赋值使得命题为真，则该命题是**可满足的**（satisfied），如果不存在这样的赋值，则称命题为**不可满足的**（unsatisfied）。

联想“数独”游戏。

更多详细内容请参见 Discrete Mathematics and Its Applications (7th Edition) 1.3

<!-- TODO -->

待补充

### 解决可满足性问题

??? note "Solving Satisfiability Problems"

    A truth table can be used to determine whether a compound proposition is satisfiable, or equiv-alently, whether its negation is a tautology (see Exercise 60). This can be done by hand fora compound proposition with a small number of variables, but when the number of variablesgrows, this becomes impractical. For instance, there are $2^{20}  = 1048576$ rows in the truth ta-ble for a compound proposition with $20$ variables. Clearly, you need a computer to help youdetermine, in this way, whether a compound proposition in $20$ variables is satisfiable

## 谓词与量词

### 为什么引入谓词逻辑

在前面介绍的命题逻辑不足以表达自然语言中所有陈述句的含义。比如下面的例子：

> "Every computer connected to the university network is functioning properly."

前述的谓词逻辑不能很好表达出“任意”（every）的概念，比如另一陈述：

> "MATH3 is functioning properly."

其中"MATH3" 是连接起来的 computer，从语言角度，我们认为之前的“任意”陈述句子应包含后面的句子。但是目前并不能做到。相应的，还有如下例子：

> "CS2 is under attack by an intruder,"
>
> "There is a computer on the university network that is under attack by an intruder."

现有的命题逻辑也不能充分表达两句的含义。所以我们需要引入**谓词逻辑**。

### 量词

所谓“量词”（quantifier），实际上是从量化（quantify）发展来的。命题函数变量被赋值时，得到具备一定逻辑值的命题，然而通过使用“量词”，我们可以由前面介绍的命题创建新的“量化命题”。在中文中，量词常见有 _一些_，_许多_，_全部_，_没有_，英文中则是 _all_，_some_，_many_，_none_。借助量词发展的命题，能够表示一个谓词逻辑在一个**元素范围**内为真的程度。

> A propositional function P(x) is a statement involving a variable x over domain D

1.  全称量词

    !!! note "Universal Quantification"

        The _universal quantification_ of $P(x)$ is the statement

        “$P(x)$ for all values ofxin the domain.”

        The notation $\forall xP (x)$ denotes the universal quantification of $P(x)$ . Here $\forall $ is called the _universal quantifier_ .We read $\forall xP (x)$ as “for all $xP (x)$” or “for every $xP (x)$.” An elementfor which $P(x)$ is false is called acounter example of $\forall xP (x)$.

2.  存在量词

    !!! note "Existential Quantification"

        The _existential quantification_ of $P(x)$ is the proposition

        “There exists an elementxin the domain such that $P(x)$.”

        We use the notation $\exists xP(x)$ for the existential quantification of $P(x)$. Here $\exists$ is called the _existential quantifier_.

一些易混淆的表示

$\exists x \forall y p(x,y)$

含义：存在一个$x$，使得所有的$y$，使得$p(x,y)$

$\forall x \exists y p(x,y)$

含义：对于所有的$x$，都存在一个$y$，使得$p(x,y)$

英文教材中还补充了一个 _uniqueness quantifier_ 有兴趣的同学可以自行了解。

### 量词的优先级

**Bound Variable** 约束的量词

a variable is bound if it is known or quantified.

**Free Variable** 自由的量词

a variable neither quantified nor specified with a value

涉及到 Binding Variables，这里用中文解释不太方便，还是搬运徐老师的 PPT 内容吧。

When a quantifier is used on a variable or a value is assigned to a variable, the variable is said to be bound. A variable that is not bound is free. （绑定变量与自由变量）

All variables in a propositional function $P(x_1 , x_2 , \cdots , x_n)$ have to be bound to turn it into a proposition which is true or false

$\forall x  \exists y  Q(x,y)$ is a proposition

<!-- TODO -->

### 涉及量词的逻辑等价

在前面的章节中我们介绍了命题的逻辑等价，现在拓展至带有谓词量词的逻辑等价。

> Statements involving predicates and quantifiers are _logically equivalent_ if and only if they have the same truth value no matter which predicates are substituted into these statements and which domain of discourse is used for the variables in these propositional functions.

即涉及谓词和量词命题陈述是**逻辑等价**的，当且仅当无论将哪些**具体谓词**替换这些陈述，且无论用哪个具体**论述域**描述变量，它们都具有**相同的真值**。

以$S \equiv T$表明涉及谓词和量词的$S$和$T$是逻辑等价的。eg. $\forall x (P(x) \land Q(x)) \equiv \forall xP(x) \land \forall xQ(x)$。

注意

- 量词辖域的扩张
- 量词辖域的收缩

常见

$$\forall x (P(x) \land Q(x)) \equiv \forall xP(x) \land \forall xQ(x)$$

$$\lnot \forall xP(x) \equiv \exists x \lnot P(x)$$

$$\lnot \exists xP(x) \equiv \forall x \lnot P(x)$$
