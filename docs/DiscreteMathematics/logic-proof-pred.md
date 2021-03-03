# 逻辑与证明——谓词与量词

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

### 嵌套量词

相关的问题

如何用英文翻译，比较麻烦，翻译此类式子的第一步是写出表达式中的量词和谓词的含义。

二个量词的可以用一个表来表示，更多量词的情况据此类推。

| Statement                                                  | When True                                                 | When False                                                          |
| :--------------------------------------------------------- | :-------------------------------------------------------- | :------------------------------------------------------------------ |
| $\forall x \forall y P(x,y) \\ \forall y \forall x P(x,y)$ | $P(x, y)$is true for every pair $x, y$.                   | There is a pair $x, y$ for $∀y∀xP (x, y)$ which $P(x, y)$ is false. |
| $\forall x \exists y P(x,y)$                               | For every $x$ there is a $y$ for which $P(x,y)$ is true.  | There is an x such that $P(x,y)$ is false for every $y$.            |
| $\exists x \forall y P(x,y)$                               | There is an $x$ for which $P(x,y)$ is true for every $y$. | For every $x$ there is a $y$ for which $P(x,y)$ is false.           |
| $\exists x \exists y P(x,y) \\ \exists y \exists x P(x,y)$ | There is a pair $x,y$ for which $P(x,y)$ is true.         | $P(x,y)$ is false for every pair $x,y$.                             |

“符号化”，使用嵌套量词翻译数学表述。

如：Forall positive integers $x$ and $y$, $x+y$ is positive.量词描述为

??? success "答案"

    $$\forall x \forall y((x >0) \land (y >0) \rightarrow (x+y>0))$$

如：极限的定义

$$\lim_{x \rightarrow a} f(x) = L$$

For every real number $\epsilon > 0$ there exists a real number $\delta > 0$ such that $|f(x)−L|< \epsilon$ whenever $0<|x−a|<δ$. 量词描述为

??? success "答案"

    $$\forall \epsilon > 0 \exists \delta > 0 \forall x (0<|x−a|<δ \rightarrow |f(x)−L|< \epsilon)$$

??? note "一个面试提到的问题"

    $\forall x \exists y P(x,y) \rightarrow \exists y \forall x P(x,y)$，证明或者证否（举出$P(x,y)$实例）。
