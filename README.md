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

## 概要
本项目主要用于上过的课的课程实验与课设代码开源,，以及使用 wiki 对部分课程知识点进行补充讲解，其目的为：  
 1. 让学校课程使用了十几年的实验内容进行更新
 2. 帮助大家通过代码更好地进行学习

目前已有开源代码的学科有：
 1. 计算机图形学
 2. 密码学
 3. 大型数据库技术
 4. Linux
 5. 数字图像处理
 6. 汇编
 7. 分布式与云计算（未完成）
 8. [JAVA](https://github.com/leo6033/Java_Project)
 9. [动画与游戏程序设计](https://github.com/leo6033/UnityLearing/tree/master/TanksWar)

有用的话别忘了点个 star 

## 参与
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
