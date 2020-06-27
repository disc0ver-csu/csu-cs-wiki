# Lamport 逻辑时钟

## 前言



## The Partial Ordering

定义不依赖于物理时钟的`happen before`关系如下（用$\rightarrow$ 表示）

1. 如果 $a$，$b$ 是相同进程的两个事件，且$a$出现在$b$之前，那么$a \rightarrow b$。
2. 如果$a$是某进程消息发送的一方，b 是另一进程接收该消息的一方，则$a \rightarrow b$。
3. 该关系具备传递性，即$a \rightarrow b$ ，$b \rightarrow c$，则$a \rightarrow c$。如果$a \nrightarrow b$，$b \nrightarrow a$，那我们称 $a$，$b$ 是并发（concurrent）的。
4. 另外补充，该关系是反自反的，即，对 $\forall a,a \nrightarrow a$，（系统中一个时间可以在它自身之前发生没有实际意义）。
