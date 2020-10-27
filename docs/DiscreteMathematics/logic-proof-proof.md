# 逻辑与证明——推理证明方法

## 推理规则

### 有效推理

命题逻辑中的**论证**指的是一系列命题：论证中除了最后的命题外，其余都称为**前提**，最后的命题称为**结论**。如果它所有前提为真蕴含结论为真，则这个论证形式是**有效**的。总结一下：

- **论证**：是指以一个命题结尾的一系列命题陈述。
- **结论**：论证的结尾，推得的命题。
- **前提**：论证的系列命题除去结论都是前提。
- **有效**：论证的最后结论，是根据前提为真时推得的，则论证有效。

??? note "英文定义"

    An _argumentin_ propositional logic is a sequence of propositions. All but the final proposition in the argument are called _premises_ and the final proposition is called the _conclusion_ . An argument is _valid_ if the truth of all its premises implies that the conclusion is true.

    An _argument form_ in propositional logic is a sequence of compound propositions involving propositional variables. An argument form is _valid_ no matter which particular propositions are substituted for the propositional variables in its premises, the conclusion is true if the premises are all true.

### 命题逻辑的推理规则

永真式$(p \land ( p \rightarrow q )) \rightarrow q$是推理的基本方法，称为**演绎推理**（modus ponens），其他相近的推理规则如下表描述

![proof-1](images/proof-1.png)

### 谓词逻辑的推理规则

我们已经讨论了命题的推理规则。现在，我们将描述一些重要的命题的推理规则，涉及量词。这些推理规则在数学论证中广泛使用，通常没有被明确提及

![proof-2](images/proof-2.png)

## 证明简介

### 一些术语

1.  **theorem**：A theorem is a statement that can be shown to be true.

    - The term theorem is usually reserved for a statement that is considered at least somewhat important.
    - Theorems can also be referred to as facts or results.

2.  **proposition**：Less important theorems sometimes are called propositions.
3.  **proof**：A proof is a valid argument that establishes the truth of a theorem.

    - We demonstrate that a theorem is true with a proof.

4.  **axiom**：The statementsused in a proof can include axioms(or postulates), which are statements we assume to be true.
5.  **lemma**：A less important theorem that is helpful in the proof of other results is called a lemma(plural _lemmas_ or _lemmata_ ).

### 证明方法

1.  直接证明（Direct Proofs）

    直接证明就是最朴素的根据蕴含式$p \rightarrow q$的证明方法，通过使用公理、定义和已知定理，根据假设条件$p$是正确的，推得结论$q$也必须是正确的。

    ??? note "Example: If $n$ is an odd integer, then $n^2$ is odd."

        符号化描述，我们试图证明$\forall n (P(n) \rightarrow Q(n))$。其中$P(n)$表示“$n$是一个奇数”，而$Q(n)$表示“$n^2$是一个奇数”。按照直接证明法，我们**假设前提是正确的**。根据奇数的定义，$n=2k+1$，$k$是整数。我们**试图证明结论也是正确的**。根据乘方运算规则，我们计算得到$n^2=(2k+1)^2=2(2k^2+2k)+1$。根据奇数的定义，我们可以确定$n^2$是个奇数。根据直接证明法我们证明了该命题。

    有些时候，直接证明法会使求证过程走向死胡同。

2.  逆否证明法（Proof by Contraposition）

    一种非直接证明方法是对偶证明法。逆否证明法的“合理性”来源于命题与其逆否命题的等价性，$p \rightarrow q$和$\lnot q \rightarrow \lnot p$是等价的，也即$(p \rightarrow q) \Leftrightarrow (\lnot q \rightarrow \lnot p)$。实际上多条件$p_1 \land p_2 \land p_3$的话，逆否还会应用德摩根定律 $\lnot p_1 \lor \lnot p_2 \lor \lnot p_3$，所以我们找出和原始条件任意一个相矛盾即可证明。

    ??? note "Example: If $n$ is an integer and $3n+2$ is odd, then $n$ is odd."

        逆否证明法，先将结论否定，则我们可以得到$n$是偶数。根据偶数的定义，$n=2k$，$k$是整数。那么我们可以得到$3n+2 = 6k+2 = 2(3k+1)$，而这表明$3n+2$是一个偶数。我们找到了条件的一个否定。由于通过结论的否推理出条件的否($\lnot q \rightarrow \lnot p$)，原命题($p \rightarrow q$)为真。

3.  反证法（Proofs by Contradiction）

    笔者发现过去学习中把逆否证明法直接当成反证法，逆否证明适用于命题描述本身包含“条件”、“蕴含”、“结论”。但反证法不仅限于这种情况，比如，我们可以用反证法来证明“$\sqrt{2}$是无理数”。**不过，不对逆否证明法做细致区分有合理性，因为通过重写式子可以用反证法证明来表示逆否证明法**

    英文教材中反证法描述如下：

    > Suppose we want to prove that a statement $p$ is true. Furthermore, suppose that we can find a contradiction $q$ such that $\lnot p \rightarrow q$ is true. Because $q$ is false, but $\lnot p \rightarrow q$ is true, we can conclude that $\lnot p$ is false, which means that $p$ is true. How can we find a contradiction $q$ that might help us prove that $p$ is true in this way?
    >
    > Because the statement $r \rightarrow \lnot r$ is a contradiction whenever $r$ is a proposition, we can prove that $p$ is true if we can show that $\lnot p \rightarrow(r \land \lnot r)$ is true for some propositionr. Proofs of this type are called **proofs by contradiction**. Because a proof by contradiction does not prove a result directly, it is another type of indirect proof. We provide three examples of proof by contradiction.

    英文定义比中文严谨很多，形象一点地讲，反证法实际上是寻找一个$\lnot p$蕴含的“隐性”条件$r$（比如原命题的部分文字构成的命题），而根据逻辑推理却得到$\lnot p \rightarrow \lnot r$，就找到了$(r \land \lnot r)$这一矛盾。而据此有$\lnot p \rightarrow (r \land \lnot r)$真，可得到$\lnot p$为假，$p$为真。还是举例来说明吧。

    ??? note "Example: Show that at least four of any 22 days must fall on the same day of the week."

        我们用$p$表示命题“At least four of 22 chosen days fall on the same day of the week.”。$r$表示命题“22 days are chosen”。根据反证法，我们令$\lnot p$为真，即“At most 3 of 22 chosen days fall on the same day of the week.”。根据$\lnot p$，由于1周7天，我们最多可选天数为21天。这导出了矛盾，“22天被选出，而最多选出21天”，即$\lnot p \rightarrow (r \land \lnot r)$。根据这一矛盾，我们得出，$p$为真。证毕。

    !!! success "逆否证明法与反证法的关系"

        通过重写式子可以用反证法证明来表示逆否证明法

        > Note that we can rewrite a proof by contraposition of a conditional statement as a proof by contradiction. In a proof of $p \rightarrow q$ by contraposition, we assume that $\lnot q$ is true. We then show that $\lnot p$ must also be true. To rewrite a proof by contraposition of $p \rightarrow q$ as a proof by contradiction, we suppose that both $p$ and $¬q$ are true. Then, we use the steps from the proof of $\lnot q \rightarrow \lnot p$ to show that $\lnot p$ is true. This leads to the contradiction $p \land \lnot p$, completing the proof.

        更详尽的解释和例子可以查阅参考书，这里笔者用数学表达式简要给出“重写”的要点，读者可尝试理解：

        - **逆否证明法**：要证明命题$p \rightarrow q$，证其逆否命题$\lnot q \rightarrow \lnot p$。假定$\lnot q$正确，推理得到$\lnot p$。

        - **反证法重写**：要证明命题$p \rightarrow q$，将反证法中$p$重写为$p \rightarrow q$，而$r$重写为$p$，即证明$(\lnot (p \rightarrow q)) \rightarrow (p \land \lnot p)$，也即$(p \land \lnot q) \rightarrow (p \land \lnot p)$。由于$(p \land \lnot q) \rightarrow p$永真，找到$(p \land \lnot q) \rightarrow \lnot p$即可。

## 证明方法与策略

证明简介所介绍的基本证明方法仅仅是一个开端，在本节详述**证明的艺术和科学**，提供证明的建议、技巧，包括如何通过回顾以及更改已有证明来达成最终证明目标。

### 穷举证明和分情况证明

$$(p_1 \lor p_2 \lor \cdots \lor p_n) \rightarrow q \Leftrightarrow [(p_1 \rightarrow q) \land (p_2 \rightarrow q) \land \cdots \land (p_n \rightarrow q)]$$

该永真式给出了分情况证明的依据，每个$p_i \rightarrow q$证明相对独立，就是**分情况证明**。

1.  穷举证明

    有些命题可以使用较小的例子穷举说明所有的可能情况。穷举证明可看作一种特殊的分情况证明，即每种情况对应一个例子。

2.  分情况证明

    分情况证明必须涵盖定理中所有可能出现的情况。举例说明：

    ??? note "Example: Prove that if $n$ is an integer, then $n^2 \ge n$."

        分三种情况进行讨论。

        - Case(i): When $n=0$, because $0^2=0$, we see that $0^2 \ge 0$. It follows that $n^2 \ge n$ is true in this case.
        - Case(ii): When $n \ge 1$, when we multiply both sides of the inequality $n \ge 1$ by the positive integer $n$, we obtain $n \cdot n \ge n \cdot 1$. This implies that $n^2 \ge n$ for $n \ge 1$.
        - Case(iii): In this case $n \le -1$. However, $n^2 \ge 0$. It follows that $n^2 \ge n$.

    使用分情况证明时不要忽略整体关系，比如类似情况的证明。

### 存在性证明

<!-- TODO -->

待补充

1.  构造性证明方法
2.  非构造性证明方法

### 唯一性证明

有些定理断言具有**特定性质**的**唯一元素**的存在。换言之，**只有一个元素具备该性质**。唯一性证明的两个步骤是：

- **Existence**： 存在性证明，我们证明具备所述性质的元素$x$存在。
- **Uniqueness**： 唯一性证明，我们证明如果元素$y \ne x$，那么$y$不具备所述性质。

等价的，我们也可以通过证明如果$x$和元素$y$都具所述性质，则$x = y$。

唯一性证明可看作证明元素$x$和性质谓词$P(x)$描述的下述命题为真

$$\exists x(P(x) \land \forall y(y \ne x \rightarrow \lnot P(y)))$$

### 证明策略

<!-- TODO -->

待补充，有兴趣的同学可以自行查阅英文教材。
