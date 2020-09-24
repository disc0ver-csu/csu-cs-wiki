# 集合论——序关系与等价关系

在本小节我们关注两类特殊的关系，分别用来描述顺序，以及元素间的相关性。

## 偏序

我们常常用关系对集合的某些元素或全体元素排序，**偏序**关系是最常见的之一。

**偏序**：定义在集合$S$上的关系$R$，如果它是自反的、反对称的和传递的，就成为**偏序**，集合$S$与定义在其上的偏序$R$一起称为**偏序集**，记作$(S,R)$。

??? note "常见的偏序集"

    $(\mathbf{Z},\ge)$: 整数集$Z$上的“大于等于关系”。

    $(\mathbf{Z^+},\mid)$: 正整数集$Z^{+}$上的整除关系。

    $(\mathcal{P(S)}, \subseteq)$：定义在集合$S$的幂集上的包含关系。

偏序集可以用关系图表示，但是有向图中有许多边不必表示出来，因为它们是必须存在的（比如自反性对应的边），习惯上偏序集使用**哈斯（Hasse）图**来表示，本文就不再绘图了，请读者根据参考书进行学习。

**可比与不可比**： 偏序集$(S,\preccurlyeq)$中的元素$a$和$b$如果有$a \preccurlyeq b$或$b \preccurlyeq a$，则称为**可比**的(comparable)，也即$(x,y) \in R \lor (y,x) \in R$。当$a$和$b$是$S$中的元素并且既没有$a \preccurlyeq b$，也没有$b \preccurlyeq a$，即$(x,y) \notin R \land (y,x) \notin R$，则称$a$与$b$**不可比**的(incomparable)。

**全序**：如果偏序集$(S, \preccurlyeq)$中的每对元素都是可比的，则称该关系为**全序**（或**线序**）关系。一个全序集也称为链。

> If$(S, \preccurlyeq)$ is a poset and every two elements of $S$ are comparable, $S$ is called a _totally ordered_ or _linearly ordered set_, and $\preccurlyeq$ is called a _total order_ or a _linear order_. A totally ordered set is also called a _chain_.

??? note "为什么会有“链”的概念"

    与Hasse图联系起来，全序要求每对元素都是可比的，所以每对元素都可以区分出“前驱”、“后继”，或者你可以理解为“祖先”和“子孙”，这么看就退化到了一条链上。

**良序**：对于偏序集$(S, \preccurlyeq)$，如果$\preccurlyeq$是全序，并且$S$的每个非空子集都有一个最小元素，就称该关系为良序关系而$(S, \preccurlyeq)$称为良序集。

> $(S,\preccurlyeq)$ is a _well-ordered set_ if it is a poset such that $\preccurlyeq$ is a total ordering and every nonempty subset of $S$ has a least element.

正整数的有序对集合，$Z^+ \times Z^+$，如果$a_1 <b_1$，或者$a_1 = b_1$且$a_2 \le b_2$（字典序），则$(a_1,a_2) \preccurlyeq (b_1,b_2)$，那么$(Z^+ \times Z^+, \preccurlyeq)$是良序集（有兴趣读者自行验证）。

良序必为全序，实际上“反对称性+任一非空子集存在最小元”就能够保证全序性质。**良序的逆关系不一定是良序**（例如$(N, \le)$）

??? note "南京大学离散数学思考题：“道是无序却有序”"

    自然数$1,2,3,\cdots,n^2+1$的任何一种排列中，必然含一个长度不小于$n+1$的严格递增链或严格递减链。

    笔者也不会做，鸽巢定理？

**良序归纳原理**：设$S$是一个良序集。如果（归纳步骤）对所有$y \in S$，如果$P(x)$对于所有$x \in S$且$x \prec y$为真，则$P(y)$为真，那么，$P(x)$对所有的$x \in S$为真。

> **THE PRINCIPLE OF WELL-ORDERED INDUCTION**: Suppose that $S$ is a well-ordered set. Then $P(x)$ is true for all $x\in S$,if
>
> _INDUCTIVE STEP_: For every $y\in S$, if $P(x)$ is true for all $x \in S$ with $x \prec y$, then $P(y)$ is true.

<!-- TODO 待补充 极大极小最大最小和格 -->

## 等价关系

### 介绍

我们将研究具有一组特殊性质的关系，可以用这组性质在某一方面类似的相关个体之间建立联系。

**等价关系**（equivalence）：定义在集合$A$上的关系如果是自反的、对称的和传递的，则称为**等价关系**。

如果两元素$a$和$b$通过等价关系$R$相关联，则称它们是等价（equivalent）的，常记为$a \sim b$。

??? note "常见的等价关系"

    1.  **模$m$同余关系**（Congruence Modulo $m$）：最广泛使用的等价关系之一是**模$m$同余关系**。设$m$是大于1的整数，以下关系是定义在整数集上的等价关系。

        $$R = \{ (a,b) | a \equiv b~ (\mathrm{mod}~m) \}$$

    2.  等长字符串关系：设$R$是定义在英文字母组成的字符串的几何上的关系，满足$aRb$当且仅当$l(a) = l(b)$，其中$l(x)$ 是字符串$x$的长度。$R$是等价关系（易证明三个性质）。

### 等价类与划分

由等价关系确定的一组元素构成的子集，叫做这个关系的一个等价类。

**等价类**：设$R$是定义在集合$A$上的等价关系。与$A$中的一个元素$a$相关联的所有元素的集合叫做$a$的等价类。元素$a$的关于$R$的等价类记作$[a]_R$，当只考虑一个关系时，我们将省去下标$R$并把这个等价类写作$[a]$。换压制，如果$R$是定义在集合$A$上的等价关系，则元素$a$的等价类是

$$[a]_R = \{s | (a,s) \in R \}$$

如果$b \in [a]_R$，则$b$叫做这个等价类的**代表元**（representative）。一个等价类的任何元素都可以作为这个类的代表元，没有特殊要求。

??? note "有关等价关系的一些等价命题的证明"

    设$R$是定义在集合$A$上的等价关系，下面的关于集合$A$中$a$、$b$两个元素的命题是等价的。

    (i)$aRb$  (ii)$[a] = [b]$  (iii)$[a] \cap [b] \ne \emptyset$

    <!-- TODO -->

    循环证明，详细见参考书。(i)推(ii)（子集相互包含），(ii)推(iii)（自反性说明非空），(iii)推(i)（举$c$，利用对称性和传递性）。

**划分**：集合$S$的**划分**是$S$的不相交的非空子集构成的集合，且它们的并集就是$S$。一族子集$A_i$， $i \in I$，（其中$I$是下标的集合）构成$S$的划分，当且仅当

$$A_i \ne \emptyset ~~~i \in I$$

$$A_i \cap A_j = \emptyset ~~~ i \ne j $$

和

$$\bigcup_{i \in I}A_i = S$$

**等价类与划分**：我们现在将说明一个等价关系怎样划分一个集合。设$R$是定义在集合$A$上的等价关系，$R$的所有等价类的并集就是集合$A$，因为$A$的每个元素$a$都在它子集的等价类，即$[a]_R$中，换句话说，

$$\bigcup_{a \in A} [a]_R = A$$

此外我们可以知道等价类要不相等，要不不相等，因此当$[a]_R \ne [b]_R$时，

$$[a]_R \cap [b]_R = \emptyset$$

这两个结论证明了等价类$A$的划分，因为它们将$A$分成不相交的子集。

## 集合的划分与覆盖
