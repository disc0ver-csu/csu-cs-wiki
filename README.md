<!--
 * @Description:
 * @Author: 妄想
 * @Date: 2020-04-04 15:13:21
 * @LastEditTime: 2020-06-19 15:25:45
 * @LastEditors: 妄想
-->

# CSU_CS_experiment

[![Gitpod Ready-to-Code](https://img.shields.io/badge/Gitpod-Ready--to--Code-brightgreen?logo=gitpod&style=flat-square)](https://gitpod.io/#https://github.com/leo6033/CSU_CS_Experiment)
[![license](https://img.shields.io/github/license/leo6033/CSU_CS_Experiment)](LICENSE)
[![Build Status](https://travis-ci.com/leo6033/CSU_CS_Experiment.svg?branch=master)](https://travis-ci.com/leo6033/CSU_CS_Experiment)
[![GitHub watchers](https://img.shields.io/github/watchers/leo6033/CSU_CS_Experiment)](https://github.com/leo6033/CSU_CS_Experiment)
[![GitHub stars](https://img.shields.io/github/stars/leo6033/CSU_CS_Experiment)](https://github.com/leo6033/CSU_CS_Experiment)

语言： [English](https://github.com/leo6033/CSU_CS_Experiment/blob/master/README-en.md) | [中文简体](https://github.com/leo6033/CSU_CS_Experiment/blob/master/README.md)

## 概要

本项目开源了部分 CS 专业的课程实验与课程设计的源码,我们同时还架设了一个 Wiki 网站，我们的核心想法是：

- 为代码开源做点贡献
- 利用 Wiki 帮助同学们更好地理解或复习课程的**核心知识点**
- 加速学院一些课程实验与课程设计的**代码迭代**（部分实验用的是 10-15 年前的代码，太过时了）

如果你喜欢，别忘了给我们一个 Star💫！

## 课程目录

目前已有开源代码的学科有：

1. [计算机图形学](https://github.com/leo6033/CSU_CS_Experiment/tree/master/%E5%AE%9E%E9%AA%8C%E8%AF%BE%E8%AE%BE%E4%BB%A3%E7%A0%81/%E8%AE%A1%E7%AE%97%E6%9C%BA%E5%9B%BE%E5%BD%A2%E5%AD%A6)
2. [密码学](https://github.com/leo6033/CSU_CS_Experiment/tree/master/%E5%AE%9E%E9%AA%8C%E8%AF%BE%E8%AE%BE%E4%BB%A3%E7%A0%81/%E5%AF%86%E7%A0%81%E5%AD%A6)
3. [大型数据库技术](https://github.com/leo6033/CSU_CS_Experiment/tree/master/%E5%AE%9E%E9%AA%8C%E8%AF%BE%E8%AE%BE%E4%BB%A3%E7%A0%81/%E5%A4%A7%E5%9E%8B%E6%95%B0%E6%8D%AE%E5%BA%93)
4. [Linux](https://github.com/leo6033/CSU_CS_Experiment/tree/master/%E5%AE%9E%E9%AA%8C%E8%AF%BE%E8%AE%BE%E4%BB%A3%E7%A0%81/Linux)
5. [数字图像处理](https://github.com/leo6033/CSU_CS_Experiment/tree/master/%E5%AE%9E%E9%AA%8C%E8%AF%BE%E8%AE%BE%E4%BB%A3%E7%A0%81/%E6%95%B0%E5%AD%97%E5%9B%BE%E5%83%8F%E5%A4%84%E7%90%86)
6. [汇编](https://github.com/leo6033/CSU_CS_Experiment/tree/master/%E5%AE%9E%E9%AA%8C%E8%AF%BE%E8%AE%BE%E4%BB%A3%E7%A0%81/%E6%B1%87%E7%BC%96%E8%AF%BE%E8%AE%BE)
7. [分布式与云计算（未完成）](https://github.com/leo6033/CSU_CS_Experiment/tree/master/%E5%AE%9E%E9%AA%8C%E8%AF%BE%E8%AE%BE%E4%BB%A3%E7%A0%81/%E5%88%86%E5%B8%83%E5%BC%8F%E4%B8%8E%E4%BA%91%E8%AE%A1%E7%AE%97)
8. [Java](https://github.com/leo6033/Java_Project)
9. [动画与游戏程序设计](https://github.com/leo6033/UnityLearing/tree/master/TanksWar)

## 参与贡献

<!-- TODO -->

欢迎大家参与该项目，参与的方式大概如下：

1. 关于实验课设代码开源：

   - 该项目中还未涉及到的课程
   - 该项目中未包括的实验
   - 对已有代码进行优化

   **需保证代码质量**

   非 wiki 部分 commit 时加入 [ci skip]，例如

   ```
   git commit -m "分布式与云计算 实验1 finish [ci skip]"
   ```

2. 关于课程 wiki：

   本地部署方式

   ```
   git clone git@github.com:leo6033/CSU_CS_Experiment.git --depth=1

   cd CSU_CS_Experiment

   # 安装 mkdocs，需要 Python3 环境
   pip install -U -r requirements.txt -i https://pypi.tuna.tsinghua.edu.cn/simple/

   # 使用自定义主题
   chmod +x ./scripts/build.sh && ./scripts/build.sh

   # 两种方法（选其一即可）：
   # 1. 运行一个本地服务器，访问 http://127.0.0.1:8000 可以查看效果
   mkdocs serve

   # 2. 在 site 文件夹下得到静态页面
   mkdocs build

   # 获取 mkdocs 的命令行工具的说明（解释了命令和参数的含义）
   mkdocs --help
   ```

   在 `docs` 目录下对应位置进行 wiki 内容编写，如有目录新增，需在 `mkdocs.yml` 中 `nav` 部分添加。

## License

[MIT © Richard McRichface.](LICENSE)
