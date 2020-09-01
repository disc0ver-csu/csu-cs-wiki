# 贡献 Wiki 词条标准

这篇文章将叙述了贡献 Wiki 词条的标准。包括文件目录结构、文档编写规范、样式使用和一些在页面编辑过程中需注意的点，希望您在撰稿或修正 Wiki 页面之前，仔细阅读，以帮助您完成更高质量的内容。

## 文件目录结构

本 Wiki 是通过 MkDocs 生成的静态静态网站，源文件为 Markdown 风格，如果你搭建过 Hexo 等类似的静态博客，那这种创作方式一定再熟悉不过了（~~老学长又废话了~~）。

项目`master`分支储存 Wiki 的源文件和实验代码的源文件，为方便利用 Github Page 托管网站，`gh-page`分支用来保存生成的网页。进行 Wiki 词条编辑，**不需要手动修改`gh-page`分支**，**只需要修改`docs-`前缀或`feature-`前缀的分支**，**不建议直接修改`master`分支**。

Wiki 源文件储存在`./docs`目录下，目录结构如下：

```bash
docs
├─Competition
│  └─images
├─CompilerPrinciples
├─DistributedSystems
│  └─images
├─...
├─Intro
│  └─images
├─SoftwareTesting
│  └─images
└─_static
    ├─css
    └─js
```

1. 你应该在`docs`下的一个子目录中进行贡献，该目录名应为一个课程（或子类名），如`Competition`对应竞赛，`SoftwareTesting`对应软件测试。然后再在该文件内编辑`.md`后缀的 Markdown 文件。
2. 如有目录新增，需在 `mkdocs.yml` 中 `nav` 部分添加标签名和地址。
3. 注意，**文件名小写**，**以 `-` 分割**，如`sync-clock.md`对应时钟同步知识点，`white-box.md`对应白盒测试知识点。另外，**文件名简单且容易理解**，合理的文件命名有助于长期维护。

## 文档编写规范

你可以使用我们提供的[模板](https://github.com/CSU-CS-WIKI/csu-cs-wiki/tree/master/docs/Intro/docs-template.md)

1.  一级标题应与`mkdocs.yml`中`nav`标签对应。
2.  二级标题应为多个，覆盖该词条的主要子知识点。
3.  请确保文档中引用的图片不会触发某些网站的防盗链，若会触发，建议将图片转存到本库内对应的 `images` 文件夹中，命名方式为 `MD 文档名称 + 编号` 的形式，引用方式为 `![](./images/xx.jpg)`。
4.  确保文档中引用链接的稳定性。
5.  文档中涉及的代码，若代码长度较长，采用行内折叠代码写法，格式如下（其他可用样式请参考模板）
6.  Wiki 部分 git 提交**不需要**在尾部加入 [ci skip]

    ````markdown
    ??? note 标题

        折叠内容，代码的话应用markdown代码标注。
        ```python
        import numpy as np
        import pandas as pd
        ```
    ````

    折叠效果

    ??? note "code"

        ```python
        import numpy as np
        import pandas as pd
        ```
