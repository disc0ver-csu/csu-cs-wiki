# Commit 标准

我们建议使用 Angular 的 Git Commit Log 规范。虽然我们并不运用一些自动化工具来检测 Commit 历史，使用这种提交方式，能方便 review（~~大家就当是训练规范性吧~~）。

## 使用模板

请使用`master`分支根目录下的`.gitmessage`，你可以预览一下[我写的参考模板](https://github.com/disc0ver-csu/csu-cs-wiki/blob/master/.gitmessage)。

使用方式

```bash
git config --global commit.template .gitmessage
```

再次提交的时候试试，如果你使用的是 Linux，建议放置在用户根目录下，然后执行如下命令。

```bash
git config --global commit.template ~/.gitmessage
```

Windows 不成功的话请使用绝对地址。

## 提交规范

<!-- TODO -->

后面再补充吧
