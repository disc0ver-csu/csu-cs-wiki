1. 创建文件 Hello.idl
2. 命令行执行 `idlj -oldImplBase -fall Hello.idl`
3. 编写 HelloServer 和 HelloClient
4. 执行 `orbd -ORBInitialPort 8000 -ORBInitialHost 127.0.0.1`
5. 运行 Server 和 Client

