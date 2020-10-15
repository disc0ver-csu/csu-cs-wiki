# 集合论——集合

不要被**集合论**的大标题吓到，我们仅仅涉及集合论一点点知识，本章所介绍的知识主要用来研究离散结构、表示离散对象。至于名字，你可以叫“集合论”，也可以叫“关系代数”，或者你也可以把他们拆散成单独的小章节去理解。许多重要的离散结构都建立在**集合**——汇集对象的结构的基础上，而**集合论**也是笔者称呼这些章节的习惯。在此之上，你还会认识到**组合**——广泛用于无序元素计数、**关系**——序偶的集合用来表示对象的关系、**有限状态机**——为计算机建模。

## 集合

**集合**：集合是对象的一个无序的聚集。更严谨的英文定义如下:

!!! note "Defination of set"

    A _set_ is an unordered collection of objects, called _elements_ or _members_ of the set. A set is said to _contain_ its elements.We write $a \in A$ to denote that $a$ is an element of the set $A$. The notation $a \notin A$ denotes that a is not an element of the set $A$.

**构造与表示**：采用列举（listing）方式，又叫做花名册方式（roster method），如英文字母表中所有元音字母的集合$V$可以表示为$V = \{a,e,i,o,u\}$。或者我们可以采用描述生成方式（Discription），即使用集合构造器（set builder）符号。如小于 10 的所有奇数集合$O$表示为$O = \{ x | x <10 \land x = 2n-1 ,n \in \mathrm{Z}^+  \}$

??? note "与计算机中的数据类型的联系"

    计算机科学中的数据类型（datatype）或类型（type）的概念是建立在集合这一概念上。特别地，数据类型或类型是一个集合地名称，连同可以作用在集合对象上地一组操作的集合。例如，布尔（boolean）是集合$\{0,1\}$的一个名称，连同对其上一个或多个元素实施运算，如AND、OR和NOT。

**集合相等**：两个集合相等当且仅当它们拥有同样的元素，即$A = B \Leftrightarrow \forall x(x \in A \leftrightarrow x \in B)$。证明集合相等除了定义法，有一个更常用的方法会在子集部分介绍。

**空集**：一个特殊的不含任何元素的集合，用$\emptyset$表示。

**全集**：我们断言的包含全部元素的集合。

**朴素集合论**：我们需要注意集合定义中所用到的术语“对象”（object），并没有指定对象是什么。朴素集理论根据直觉定义的集合，并使用无论什么性质都存在一个恰好有该性质对象组成的集合，因而导致了悖论（paradox）或逻辑不一致性。这些逻辑不一致性可以通过公理出发构造集合论来避免。但在我们的学习过程中，仍以朴素集合论为蓝本，有兴趣继续学习公理集合论的同学可以自行查阅资料。

**罗素悖论**：参考 PPT，理解理发师悖论和罗素悖论的等价性。这里我们给出形式化描述：

??? note "Formal presentation of Russell's paradox"

    Define Naive Set Theory (NST) as the theory of predicate logic with a binary predicate $\in$  and the following axiom schema of unrestricted comprehension:

    $$\exists y \forall x (x \in y \Leftrightarrow \phi(x))$$

    for any formula $\phi$  with only the variable x free. Substitute $x \notin x$ for $\phi$. Then by existential instantiation (reusing the symbol $y$) and universal instantiation we have

    $$y \in y \Leftrightarrow y \notin y$$

    a contradiction. There fore, NST is inconsistent.

    简言之，NST假定上述谓词命题为真（总存在一个集合来描述任何性质），但我们取特殊的$\phi$时，会发现矛盾。

## 子集

**子集**（subset）：集合$A$是集合$B$的子集当且仅当$A$的每个元素也是$B$的元素。$A \subseteq B$仅当下面量化式为真：

$$\forall x ( x \in A \rightarrow x \in B)$$

**证明集合相等**：想要证明两个集合$A$和$B$相等，就证明$A \subseteq B$和$B \subseteq A$。

常用：

$$\emptyset \subseteq A \\ A \subseteq A$$

## 集合的大小

集合广泛应用于计数问题，讨论集合的大小是必要的。

**基数**（cardinality）：令$S$为集。如果$S$中恰有$n$个不同的元素，这里$n$是非负整数，我们就说$S$是有限集（finite set），而$n$是$S$的基数。$S$的基数记为$|S|$。而不是有限的集合成为无限集（infinite set）

## 幂集

**幂集**：给定集合$S$，其幂集（power set）是集合$S$的所有子集的集合，记为$\mathcal{P}(X)$ 。

需要辨别跟空集相关的一些集合的幂集，如下：

$$\mathcal{P}(\emptyset) = \{ \emptyset \} \\ \mathcal{P}(\{ \emptyset \}) = \{ \emptyset, \{ \emptyset \} \}$$

幂集的基数：$|\mathcal{P}(A)| = 2^{|A|}$

## 笛卡尔积

有序$n$元组（ordered $n$-tuples）来表示次序。两个有序$n$元组相等仅当每一对对应元素都相等。特别注意有序二元组称为**序偶**（ordered pair）。

**笛卡尔积**（Cartesian product）：$A \times B$表示，是所有序偶$(a,b)$的集合，其中，$a \in A$且$b \in B$：

$$A \times B = \{ (a,b) | a \in A \land b \in B \}$$

与后面所讲的“关系联系起来”，**关系是笛卡尔积的子集**（这句话笔者印象深刻）。

??? note "序偶的表示"

    序偶所定义的性质是两个序偶相等当且仅当第一个元素和第二个元素相等。令人惊奇的是，我们可以用集合论的基本概念来构造序偶，从而取代用序偶作为最基本的概念。证明如果将序偶$(a,b)$定义为$\{\{a\},\{a,b\}\}$，那么$(a,b) = (c,d)$当且仅当$a=c$且$b=d$（证明交给你们自己了）。

    <!-- TODO -->

## 集合运算

- **并**（union）: $A \cup B = \{x | x \in A \lor x \in B\}$
- **交**（intersection）：$A \cap B = \{x | x \in A \land x \in B\}$
- **差**（difference）： $A - B = \{ x | x \in A \land x \notin B \}$
- **补**（complement）： $\overline{A} = \{ x \in U | x \notin A \}$
- **对称差**（symmetric difference）：$A \oplus B = \{x | (x \in A \lor x \in B) \land (x \notin A \lor x \notin B)  \} = (A-B) \cup (B-A) = (A \cup B)-(A \cap B)$

## 集合恒等式

|                                                     恒等式                                                     |             名称              |
| :------------------------------------------------------------------------------------------------------------: | :---------------------------: |
|                                     $A \cap U =A \\ A \cup \emptyset = A$                                      |    恒等律（Identity laws）    |
|                                 $A \cup U = U \\ A \cap \emptyset = \emptyset$                                 |   支配律（Domination laws）   |
|                                         $A \cup A = A \\ A \cap A = A$                                         |   幂等律（Idempotent laws）   |
|                                          $\overline{(\overline{A})}$                                           |  补律（Complementation law）  |
|                                  $A \cup B = B \cup A \\ A\cap B = B \cap A$                                   |  交换律（Commutative laws）   |
|                $A \cup (B \cup C) = (A\cup B) \cup C \\ A \cap (B \cap C) = (A \cap B) \cap C$                 |  结合律（Associative laws）   |
|       $A \cup(B \cap C) = (A \cup B) \cap (A \cup C) \\ A \cap (B \cup C) = (A \cap B) \cup (A \cap C)$        |  分配律（Distributive laws）  |
| $\overline{A \cap B} = \overline{A} \cup \overline{B} \\ \overline{A \cup B} = \overline{A} \cap \overline{C}$ | 德·摩根律（De Morgan's laws） |
|                                $A \cup (A \cap B) = A \\ A \cap (A \cup B) = A$                                |   吸收律（Absorption laws）   |
|                          $A \cup \overline{A} = U \\ A \cap \overline{A} = \emptyset$                          |   互补律（Complement laws）   |

## 交和并的扩展

从两集合拓展到多个集合，按照《离散数学》（方）的解释，试讲交、并运算定义在集合的搜集上（搜集是集合的另一种称呼）。

**定义**：设$C$是某论述域子集的搜集。

1.  $C$的成员的并，记为$\bigcup_{S \in C} S$，是由下式指定的集合：

    $$\bigcup_{S \in C} S = \{ x | \exists s(S \in C \land x \in S) \}$$

2.  如果$C \ne \emptyset$，$C$的成员的交，记为$\bigcap_{S \in C} S$，是下式指定的集合：

    $$\bigcap_{S \in C} S = \{ x | \forall S (S \in C \rightarrow x \in S) \}$$

如果搜集是有限的，那么可以用如下记号表示：

$$A_1 \cup A_2 \cup \cdots \cup A_n = \bigcup_{i=1}^{n} A_i$$

$$A_1 \cap A_2 \cap \cdots \cap A_n = \bigcap_{i=1}^{n} A_i$$
