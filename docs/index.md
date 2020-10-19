disqus:
pagetime:
title: CSU CS Wiki

# CSU CS Wiki

本项目 Wiki 部分目的在于帮助同学们更好地理解或复习课程的**核心知识点**，以及竞赛相关内容。

本项目受 [OI Wiki](https://oi-wiki.org/) 的启发，在编写过程中参考了其资料，在此致谢。

项目目前在起步阶段，急需优质的 Wiki 词条内容，我们期待你的加入，项目 QQ 交流群：1102036265。

如果你喜欢，别忘了点击右上角，给我们一个 Star💫！

## 参与贡献

### Quick Start

[项目本地部署 QuickStart](https://disc0ver-csu.github.io/csu-cs-wiki/Intro/quick-start/)

你可以直接在 Github 上编辑 Wiki 的源文档，但如果需要较大范围改动，那么我们建议你采取**本地部署**的方式。

### 贡献 Wiki 词条

[贡献 Wiki 词条参考标准](https://disc0ver-csu.github.io/csu-cs-wiki/Intro/docs-guide/)

### 贡献代码

[贡献代码参考标准](https://disc0ver-csu.github.io/csu-cs-wiki/Intro/codes-guide/)

!!! warning "特别注意"

    特别注意：

    **开源代码的初衷不是为了敷衍实验/课设**！

    **开源代码的初衷不是为了敷衍实验/课设**！

    **开源代码的初衷不是为了敷衍实验/课设**！

    相反，我们希望通过开源已有的（部分）实现形式，促进教学方和学生方良性发展，所以我们也会跟课程老师进行沟通（~~相信你也不希望全班代码一个样子吧~~）。

## Material color palette 颜色主题

### Primary colors 主色

> 默认为 `white`

点击色块可更换主题的主色

<div id="color-button">
<button data-md-color-primary="red">Red</button>
<button data-md-color-primary="pink">Pink</button>
<button data-md-color-primary="purple">Purple</button>
<button data-md-color-primary="deep-purple">Deep Purple</button>
<button data-md-color-primary="indigo">Indigo</button>
<button data-md-color-primary="blue">Blue</button>
<button data-md-color-primary="light-blue">Light Blue</button>
<button data-md-color-primary="cyan">Cyan</button>
<button data-md-color-primary="teal">Teal</button>
<button data-md-color-primary="green">Green</button>
<button data-md-color-primary="light-green">Light Green</button>
<button data-md-color-primary="lime">Lime</button>
<button data-md-color-primary="yellow">Yellow</button>
<button data-md-color-primary="amber">Amber</button>
<button data-md-color-primary="orange">Orange</button>
<button data-md-color-primary="deep-orange">Deep Orange</button>
<button data-md-color-primary="brown">Brown</button>
<button data-md-color-primary="grey">Grey</button>
<button data-md-color-primary="blue-grey">Blue Grey</button>
<button data-md-color-primary="white">White</button>
</div>

<script>
  var buttons = document.querySelectorAll("button[data-md-color-primary]");
  Array.prototype.forEach.call(buttons, function(button) {
    button.addEventListener("click", function() {
      document.body.dataset.mdColorPrimary = this.dataset.mdColorPrimary;
      localStorage.setItem("data-md-color-primary",this.dataset.mdColorPrimary);
    })
  })
</script>

### Accent colors 辅助色

> 默认为 `red`

点击色块更换主题的辅助色

<div id="color-button">
<button data-md-color-accent="red">Red</button>
<button data-md-color-accent="pink">Pink</button>
<button data-md-color-accent="purple">Purple</button>
<button data-md-color-accent="deep-purple">Deep Purple</button>
<button data-md-color-accent="indigo">Indigo</button>
<button data-md-color-accent="blue">Blue</button>
<button data-md-color-accent="light-blue">Light Blue</button>
<button data-md-color-accent="cyan">Cyan</button>
<button data-md-color-accent="teal">Teal</button>
<button data-md-color-accent="green">Green</button>
<button data-md-color-accent="light-green">Light Green</button>
<button data-md-color-accent="lime">Lime</button>
<button data-md-color-accent="yellow">Yellow</button>
<button data-md-color-accent="amber">Amber</button>
<button data-md-color-accent="orange">Orange</button>
<button data-md-color-accent="deep-orange">Deep Orange</button>
</div>

<script>
  var buttons = document.querySelectorAll("button[data-md-color-accent]");
  Array.prototype.forEach.call(buttons, function(button) {
    button.addEventListener("click", function() {
      document.body.dataset.mdColorAccent = this.dataset.mdColorAccent;
      localStorage.setItem("data-md-color-accent",this.dataset.mdColorAccent);
    })
  })
  // #758
  document.getElementsByClassName('md-nav__title')[1].click()
</script>
