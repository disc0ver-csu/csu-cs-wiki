# JAVA聊天室

> 写了两个版本的聊天室。
>
> `PP`:
>
> - 用户间的聊天会在弹窗中进行
> - 原始界面，无色彩
> - Mac，windows均流畅运行
>
> `PP-无弹窗`：
>
> - 后来实验老师改了要求，说聊天室就是聊天室，不能有弹窗（？？）因此这个是最终提交给老师检查的版本
> - 用户间的聊天都在总的界面中进行
> - 进行了一定的美化
> - 界面在Mac电脑中显示有点问题
>
> **使用说明**：先运行`Server.java`，然后运行`Client.java`（若第一次登录，则密码自定义就行）
>
> **开发环境**：JDK11，IntelliJ IDEA

## PP

### 功能

1. 双击`用户名`称出现弹窗，进行私聊

   ![image-20200704104601732](./images/image-20200704104601732.png)

2. 双击`创建群聊`，可选择用户进行群聊

   <img src="./images/image-20200704104811203.png" alt="image-20200704104811203" style="zoom: 33%;" />

<img src="./images/image-20200704105021350.png" alt="image-20200704105021350" style="zoom:33%;" />

3. 服务器管理员可与用户私聊信息

   <img src="./images/image-20200704105151850.png" alt="image-20200704105151850" style="zoom:33%;" />

4. 服务器可强制下线用户

   <img src="./images/image-20200704105224308.png" alt="image-20200704105224308" style="zoom:33%;" />

5. 用户上线、下线时所有在线用户会受到消息

   <img src="./images/image-20200704105317998.png" alt="image-20200704105317998" style="zoom:33%;" />

## PP-无弹窗

### 登录界面

<img src="./images/image-20200704110427678.png" alt="image-20200704110427678" style="zoom:40%;" />

- 密码错误：

  <img src="./images/image-20200704110558754.png" alt="image-20200704110558754" style="zoom:40%;" />

- 注册时用户已存在

<img src="./images/image-20200704110641969.png" alt="image-20200704110641969" style="zoom:40%;" />

### 客户端

- 用户上线

<img src="./images/image-20200704110739947.png" alt="image-20200704110739947" style="zoom:40%;" />

- 广播消息

<img src="./images/image-20200704110820396.png" alt="image-20200704110820396" style="zoom:50%;" />

- 私聊

<img src="./images/image-20200704110835398.png" alt="image-20200704110835398" style="zoom:50%;" />

- 创建群聊

<img src="./images/image-20200704110904737.png" alt="image-20200704110904737" style="zoom:30%;" />

<img src="./images/image-20200704110926662.png" alt="image-20200704110926662" style="zoom:25%;" />

### 服务器端

- 广播

<img src="./images/image-20200704111004491.png" alt="image-20200704111004491" style="zoom:50%;" />

- 私聊用户

<img src="./images/image-20200704111019795.png" alt="image-20200704111019795" style="zoom:50%;" />

- 强制下线

<img src="./images/image-20200704111040440.png" alt="image-20200704111040440" style="zoom:30%;" />

