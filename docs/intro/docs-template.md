# 这是一级标题

一级标题应与`mkdocs.yml`中`nav`部分命名一致。

## 这是二级标题 1

二级标题应为该文的大段标题

## 这是二级标题 2

### 这是三级标题 1

<!-- 这是注释 -->

这是注释写法`<!-- -->`。

这是**加粗**。

这是 tag 写法`tag`。

这是引用

> 引用

图片链接：`![]()`（不建议使用外链，请参照词条贡献标准使用）

![这是图片链接](./images/qs1.png)

[这是网页链接](https://CSU-CS-WIKI.github.io/csu-cs-wiki/)

这是代码段（请在点点点后写明语言）

```C++
// C++片段
```

```golang
// go 段落
```

```bash
git clone ...
```

## 这是三级标题 2

mkdocs-material 的一些特殊用法，比如提示，折叠。`???`为折叠，`!!!`非折叠，`note`，`info`等会加载不同的样式，颜色样式参考[Mkdocs 颜色样式](https://cyent.github.io/markdown-with-mkdocs-material/syntax/note_style/)，引号内为显示的标题。

```markdown
??? note "标题"

    内容
```

```markdown
!!! info "提示"

    内容
```

??? note "标题"

    内容

!!! info "提示"

    内容
