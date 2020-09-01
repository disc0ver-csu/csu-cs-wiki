<!--
 * @Description:
 * @Author: 妄想
 * @Date: 2020-04-04 15:13:21
 * @LastEditTime: 2020-06-19 15:25:45
 * @LastEditors: 妄想
-->

# CSU_CS_experiment

[![Gitpod Ready-to-Code](https://img.shields.io/badge/Gitpod-Ready--to--Code-brightgreen?logo=gitpod&style=flat-square)](https://gitpod.io/#https://github.com/CSU-CS-WIKI/CSU_CS_Experiment)
[![license](https://img.shields.io/github/license/CSU-CS-WIKI/CSU_CS_Experiment)](LICENSE)
[![Build Status](https://travis-ci.org/CSU-CS-WIKI/CSU_CS_Experiment.svg?branch=master)](https://travis-ci.org/CSU-CS-WIKI/CSU_CS_Experiment)
[![GitHub watchers](https://img.shields.io/github/watchers/CSU-CS-WIKI/CSU_CS_Experiment)](https://github.com/CSU-CS-WIKI/CSU_CS_Experiment)
[![GitHub stars](https://img.shields.io/github/stars/CSU-CS-WIKI/CSU_CS_Experiment)](https://github.com/CSU-CS-WIKI/CSU_CS_Experiment)

Language: [English](https://github.com/CSU-CS-WIKI/CSU_CS_Experiment/blob/master/README-en.md) | [中文简体](https://github.com/CSU-CS-WIKI/CSU_CS_Experiment/blob/master/README.md) 

## Abstract

The project has opened some source codes related to a list of projects which students majoring in Computer Science should complete in some courses. We also build a Wiki. Our main purposes are as followed:

- Contribute to the Open Source Project.
- Use Wiki to help students have a better comprehension of or review the **key points** of several courses.
- Accelerate the pace of **code iteration** in labs/experiments. (To be honest, most of codes are out of date while some of them were generated 10-15 years ago.)

Don't forget to give us a star💫 :)

## Courses List

(We need contributors to proofread the translation :) Join us! )

These courses are available at present.

<!-- Remeber to change the links after reconstraction -->

1. [Computer Graphics](https://github.com/CSU-CS-WIKI/computer-graphics)
2. [Cryptology](https://github.com/CSU-CS-WIKI/cryptography)
3. [Commercial Database](https://github.com/CSU-CS-WIKI/large-database-oracle)
4. [Linux](https://github.com/CSU-CS-WIKI/linux-system)
5. [Digital Image Process](https://github.com/CSU-CS-WIKI/digital-image-process)
6. [Assembly Language](https://github.com/CSU-CS-WIKI/assembly-language)
7. [Distributed Systems and Cloud Computing](https://github.com/CSU-CS-WIKI/distributed-systems)
8. [Java](https://github.com/CSU-CS-WIKI/java-projects)
9. [Animation and Game Programing](https://github.com/leo6033/UnityLearing/tree/master/TanksWar)
10. [compiler principles](https://github.com/CSU-CS-WIKI/compiler-principles)
11. [software testing](https://github.com/CSU-CS-WIKI/software-testing)

## Contribution

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
