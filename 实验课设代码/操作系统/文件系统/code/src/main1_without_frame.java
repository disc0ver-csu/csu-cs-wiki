import fmsModel.*;

import java.io.IOException;
import java.util.Date;
import java.util.List;
import java.util.Scanner;

import static fmsConfig.MainConfig.BLOCKNUM;
import static fmsModel.HostHolder.getCurDir;
import static fmsModel.HostHolder.setCurDir;
import static fmsService.DirService.*;
import static fmsService.DiskService.*;
import static fmsService.FileService.*;
import static fmsService.UserService.*;

public class main1_without_frame {
    public static void main(String[] args) throws IOException{
        /**
         * 没有界面的文件管理系统，管理员可以修改文件权限。
         * 注：退出时输入"exit"退出，不要直接强行停止，否则下次打开时若不清空磁盘将会发生错误。
         */
        Scanner scanner=new Scanner(System.in);
        String input;
        System.out.print("正进入文件系统...");
        while(true){
            System.out.println("是否需要格式化磁盘？(y/n)");
            input=scanner.nextLine().toLowerCase();
            if(input.equals("y")){
                System.out.println("正在格式化磁盘……");
                formatDisk();
                System.out.println("格式化成功！");
                break;
            }
            else if(input.equals("n")){
                initDisk();
                break;
            }
            else{
                System.out.print("无法识别您的输入，请重试。");
            }
        }
        System.out.println("您好，用户root。现在时间是"+new Date()+",输入help可获取指令列表。");
        while (true){
            int curId=getCurDir().getId();
            INode curNode = getINodeById(curId,root);
            String cur=getFullName(curNode);
            String username=HostHolder.getUser().getUserName();
            System.out.print(username+"@docManage:"+cur+"#");
            input=scanner.nextLine().toLowerCase();
            String order=input.trim().split(" ")[0];
            String[] word;
            switch (order){
                case "help":
                    System.out.println("指令列表：");
                    System.out.println("ls [<目录>] : 显示当前目录或给定目录下的文件列表");
                    System.out.println("ll [<目录>] : 显示当前目录或给定目录下的文件详细信息");
                    System.out.println("cd <目录> : 进入给定目录");
                    System.out.println("mkdir <目录名> [<目录>] : 在当前目录或给定目录下创建目录");
                    System.out.println("create <文件名> [<目录>]: 在当前目录或给定目录下创建文件");
                    System.out.println("read <文件名> : 读取文件");
                    System.out.println("rm [-r] <文件名或目录名> : 删除文件或目录，-r代表递归删除目录下所有子目录和文件");
                    System.out.println("write/overwrite <文件名> <写入内容> : 向文件中写入内容");
                    System.out.println("su <用户名> : 登录其他用户");
                    System.out.println("useradd <用户名> : 注册其他用户");
                    System.out.println("userdel <用户名> : 删除其他用户");
                    System.out.println("exit : 退出文件系统");
                    break;
                case "exit":
                    releaseDisk();
                    System.out.println("再见！");
                    System.exit(0);
                    break;
                case "ls":
                    // 1.是否有目录参数，目录参数是否合法
                    // 2.当前用户是否拥有读该目录的权限
                    // 3.调用函数
                    word=input.split(" ");
                    if(word.length==1){//如果没有目录参数,就在当前目录ls
                        List<String> dirs=listDir("");
                        for(String s:dirs){
                            System.out.print(s+" ");
                        }
                    }
                    else if(word.length!=2){
                        System.out.println("参数不合法！");
                        break;
                    }
                    else{//有目录参数的话，检测是否有权限访问该目录，ls该目录的内容
                        if(canViewDir(word[1])){
                            IndexNode now=getCurDir();
                            setCurDir(changeDir(word[1]));
                            List<String> dirs=listDir("");
                            for(String s:dirs){
                                System.out.print(s+" ");
                            }
                            setCurDir(now);
                        }
                    }
                    System.out.println();
                    break;
                case "ll":
                    // 1.是否有目录参数，目录参数是否合法
                    // 2.当前用户是否拥有读该目录的权限
                    // 3.调用函数
                    word=input.split(" ");
                    if(word.length==1){//如果没有目录参数,就在当前目录ls
                        ListInfo("");
                    }
                    else if(word.length!=2){
                        System.out.println("参数不合法！");
                        break;
                    }
                    else{//有目录参数的话，检测是否有权限访问该目录，ls该目录的内容
                        if(canViewDir(word[1])){
                            IndexNode now=getCurDir();
                            IndexNode go=changeDir(word[1]);
                            setCurDir(go);
                            ListInfo("");
                            setCurDir(now);
                        }
                    }
                    break;
                case "cd":
                    // 1.目录参数是否合法
                    // 2.当前用户是否拥有读该目录的权限
                    // 3.调用函数
                    word=input.split(" ");
                    if(word.length!=2) {
                        System.out.println("cd指令参数错误！");
                        break;
                    }
                    if(canViewDir(word[1])){
                        IndexNode go=changeDir(word[1]);
                        setCurDir(go);
                    }
                    break;
                case "mkdir":
                    word=input.split(" ");
                    if(word.length==2){
                        int status=mkdir(word[1]);
                        if(status==-1){
                            System.out.println("创建失败");
                            break;
                        }
                        else if(status==-1){
                            System.out.println("已有同名目录！");
                            break;
                        }
                    }
                    else if(word.length!=3){
                        System.out.println("参数不合法！");
                        break;
                    }
                    else{
                        if(canWriteDir(word[2])){
                            IndexNode now=getCurDir();
                            setCurDir(changeDir(word[2]));
                            if(mkdir(word[1])==-1){
                                System.out.println("创建失败");
                                setCurDir(now);
                                break;
                            }
                            setCurDir(now);
                        }
                    }
                    printTree();
                    break;
                case "create":
                    word=input.split(" ");
                    if(word.length==2){
                        if(createFile(word[1])==BLOCKNUM - 1){
                            System.out.println("创建失败");
                            break;
                        }
                    }
                    else if(word.length!=3){
                        System.out.println("参数不合法！");
                        break;
                    }
                    else{
                        if(canWriteDir(word[2])){
                            IndexNode now=getCurDir();
                            setCurDir(changeDir(word[2]));
                            if(createFile(word[1])==BLOCKNUM - 1){
                                System.out.println("创建失败");
                                setCurDir(now);
                                break;
                            }
                            setCurDir(now);
                        }
                    }
                    break;
                case "read":
                    word=input.split(" ");
                    if(word.length!=2){
                        System.out.println("read参数不合法");
                        break;
                    }
                    if(canViewFile(word[1])){
                        System.out.println(readFile(word[1]));
                    }
                    break;
                case "write":
                    word=input.split(" ");
                    if(word.length!=3){
                        System.out.println("write参数不合法");
                        break;
                    }
                    if(canWriteFile(word[1])){
                        writeFile(word[1],word[2]);
                    }
                    break;
                case "overwrite":
                    word=input.split(" ");
                    if(word.length!=3){
                        System.out.println("overwrite参数不合法");
                        break;
                    }
                    if(canWriteFile(word[1])){
                        deleteOneFile(word[1]);
                        createFile(word[1]);
                        writeFile(word[1],word[2]);
                    }
                    break;
                case "rm":
                    word=input.split(" ");
                    if(word.length!=3 && word.length!=2){
                        System.out.println("rm参数不合法");
                        break;
                    }
                    if(word.length==3){
                        if(!word[1].equals("-r")){
                            System.out.println("rm参数不合法");
                        }
                        else{
                            if(canWriteFile(word[2])){
                                if(!deleteAllFile(word[2])){
                                    System.out.println("删除文件失败");
                                }
                                else System.out.println("删除成功");
                            }
                        }
                    }
                    else if(word.length==2){
                        if(canWriteFile(word[1])){
                            if(!deleteOneFile(word[1])){
                                System.out.println("删除文件失败");
                            }
                            else System.out.println("删除成功");
                        }
                    }
                    break;
                case "su":
                    word=input.split(" ");
                    if(word.length!=2){
                        System.out.println("su参数不合法");
                        break;
                    }
                    login(word[1]);
                    break;
                case "useradd":
                    word=input.split(" ");
                    if(!HostHolder.getUser().getUserName().equals("root")){
                        System.out.println("非root用户无权创建用户");
                        break;
                    }
                    if(word.length!=2){
                        System.out.println("useradd参数不合法");
                        break;
                    }
                    User user=new User(word[1]);
                    register(user);
                    break;
                case "userdel":
                    word=input.split(" ");
                    if(!HostHolder.getUser().getUserName().equals("root")){
                        System.out.println("非root用户无权删除用户");
                        break;
                    }
                    if(word.length!=2){
                        System.out.println("userdel参数不合法");
                        break;
                    }
                    deleteUser(word[1]);
                    break;
                default:
                    System.out.println("指令无效，请重试！");
            }
        }
    }
}
