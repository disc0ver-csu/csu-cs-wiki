package utilities;

import Interface.ServerInterface;
import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class ServerOperations {
    private ServerSocket ss;

    //public ClientInterface interf;
    private ServerInterface interf;

    public ServerOperations(ServerSocket ss) {
        interf = new ServerInterface();
        interf.clients = new OnlineClients();
        this.ss = ss;
        this.interf.showInterface();
    }

    //服务器-核实用户信息
    public static String CheckUserInfo(String user, String password) {
        int result;
        result = checkUser(user);
        if(result==0) return "3"; //用户不存在
        else {
            LoginInfo inf = LoginInfo.getLoginInfo(user);
            if(inf.getUserPassword().equals(password)) return "1";  //用户存在且密码正确
            else return "2";  //用户存在但密码错误
        }
    }
    //服务器-检查用户是否存在
    public static int checkUser(String userName) {
        File dir = new File("LoginInfo");
        if (!dir.exists()) {
            dir.mkdir();
            return 0;
        }
        else {
            File[] infs = dir.listFiles();
            for(int i=0; i<infs.length; i++) {
                if (infs[i].getName().equals(userName+".dat")) return 1;
            }
            return 0;
        }
    }
    //服务器-用户登录
    public void login(Socket s, String userName, String password, String result) {
        System.out.println("用户正在登陆...");
        Info inf;
        if(result.equals("3")) {
            //创建用户
            LoginInfo loginInf = new LoginInfo(userName, password);
            loginInf.saveLoginInfo();
            inf = new Info(userName);
            inf.saveInfo();
        }
        else inf = Info.readInfo(userName);
        sendUserLoginInfo(userName);
        try {
            System.out.println("登陆完成...");
            int index = interf.clients.getIndex(s);
            Operations.sendMsg("LoginSuccess", interf.clients.getUserPs(index));
        } catch (Exception e) {System.out.println(e.getMessage());}
        //更新在线列表并通知在线的用户
        try {
            sendUserInfo(s, inf);
            sendOnlineClients(s);
        }catch (Exception e){e.printStackTrace();}

    }
    //服务器-用户下线
    public void logout(String userName){
        interf.clients.delUser(userName);
        interf.delUser(userName);
        sendUserLogoutInfo(userName);
    }



    //服务器-向客户端发送用户信息
    public void sendUserInfo(Socket s, Info inf) {
        System.out.println("准备向用户发送用户信息...");
        try {
            int index = interf.clients.getIndex(s);
            Operations.sendMsg("ReceiveUserInfo", inf.userName, interf.clients.getUserPs(index));
            System.out.println("用户信息发送完成");
        } catch (Exception e) {System.out.println("提示用户接收用户信息失败！");System.out.println(e.getMessage());}
    }
    //服务器-向新用户发送当前在线用户
    public void sendOnlineClients(Socket s){
        System.out.println("准备向用户发送在线用户列表...");
        try {
            int index = interf.clients.getIndex(s);
            PrintStream ps = interf.clients.getUserPs(index);
            Operations.sendMsg("ReceiveOnlineClients", ps);
            System.out.println("发送接收命令");
            int length = interf.clients.getSize();
            //ps.println(length);
            Operations.sendMsg(String.valueOf(length), ps);
            for(int i=0; i<length; i++){
                String userName = interf.clients.getUserName(i);
                Operations.sendMsg(userName,interf.getUserColor(userName), ps);
            }
            //int index = interf.clients.getIndex(s);
            //Operations.sendMsg("ReceiveOnlineClients", "1", interf.clients.getUserName(0), interf.clients.getUserPs(index));
            System.out.println("在线用户列表发送完成");
        } catch (Exception e) {e.printStackTrace();}
    }


    //服务器广播
    public void broadCastMsg(String msg){
        for(int i=0; i<interf.clients.getSize(); i++){
            Socket tmpS = interf.clients.getUserSocket(i);
            try {
                int index = interf.clients.getIndex(tmpS);
                System.out.println("向"+interf.clients.getUserName(i)+"广播信息...");
                Operations.sendMsg("服务器", msg, interf.clients.getUserPs(index));
            } catch (Exception e){
                System.out.println("向"+interf.clients.getUserName(i)+"广播信息错误！");
            }
        }
        System.out.println("已广播新用户上线信息");
    }
    //服务器-向所有在线的客户端发送新用户上线信息
    public void sendUserLoginInfo(String userName) {
        for(int i=0; i<interf.clients.getSize(); i++){
            Socket tmpS = interf.clients.getUserSocket(i);
            try {
                int index = interf.clients.getIndex(tmpS);
                System.out.println("向"+interf.clients.getUserName(i)+"广播新用户上线信息...");
                Operations.sendMsg("NewUser", userName, interf.getUserColor(userName),interf.clients.getUserPs(index));
            } catch (Exception e){
                System.out.println("向"+interf.clients.getUserName(i)+"发送新用户上线信息错误！");
            }
        }
        System.out.println("已广播新用户上线信息");
    }
    //服务器-向所有在线的客户端发送用户下线信息
    public void sendUserLogoutInfo(String userName) {
        for(int i=0; i<interf.clients.getSize(); i++){
            Socket tmpS = interf.clients.getUserSocket(i);
            try {
                Operations.sendMsg("UserLogout", userName, interf.clients.getUserPs(i));
            } catch (Exception e){
                System.out.println("发送用户下线信息错误！");
                System.out.println(e.getMessage());
            }
        }
    }
    //服务器-强制下线用户
    public void forceLogoutUser(String userName) {
        Socket userSocket = interf.clients.getUserSocket(userName);
        try{
            int index = interf.clients.getIndex(userName);
            Operations.sendMsg("ForceLogout", userName, interf.clients.getUserPs(index));
        }catch (Exception e) {System.out.println("强制下线用户失败！");}
        logout(userName);
    }



    //服务器转发群聊消息
    public static void sendGroupChat(Message msg, PrintStream ps) throws IOException{
        try {
            ps.println("groupChatMsg");
            ps.println(msg.getGroupName());
            ps.println(msg.getUserFrom());
            ps.println(msg.getContent());
        } catch (Exception e) {System.out.println("发送聊天信息失败");e.printStackTrace();}
    }

    //服务器-监听并接收消息
    public void ServerReceiveMsg(ServerSocket ss, Socket s) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(s.getInputStream()));
        PrintStream ps = new PrintStream(s.getOutputStream());
        while(true) {
            try {
                String msgType = br.readLine();
                if(msgType != null) System.out.println("\n接收到  " + msgType + " 请求");
                //用户登录
                if(msgType.equals("CheckUserInfo")){
                    String user = br.readLine();
                    String password = br.readLine();
                    String result = CheckUserInfo(user, password);
                    if(result.equals("2")) {
                        Operations.sendMsg( "WrongPassword", ps);
                        return;
                    }
                    else if(result.equals("3")){
                        Operations.sendMsg( "NoneUser", ps);
                        return;
                    }
                    else{
                        interf.addUser(user);
                        //String[] color = interf.getUserColor(user).split(",");
                        //Color c = new Color(Integer.valueOf(color[0]),Integer.valueOf(color[1]),Integer.valueOf(color[2]));
                        interf.clients.addUser(user, s, br, ps);
                        System.out.println("已将用户加入在线列表:"+interf.clients.getOnlineNames());
                        login(s, user, password, result);
                    }
                }
                //用户注册
                else if(msgType.equals("Signup")){
                    String user = br.readLine();
                    String password = br.readLine();
                    String result = CheckUserInfo(user, password);
                    if(!result.equals("3")){
                        Operations.sendMsg( "UserExists", ps);
                    }
                    else {
                        interf.addUser(user);
                        //String[] color = interf.getUserColor(user).split(",");
                        //Color c = new Color(Integer.valueOf(color[0]),Integer.valueOf(color[1]),Integer.valueOf(color[2]));
                        interf.clients.addUser(user, s, br, ps);
                        System.out.println("已将用户加入在线列表:" + interf.clients.getOnlineNames());
                        login(s, user, password, "3");
                    }
                }
                //转发私聊消息
                else if(msgType.equals("chatMsg")){
                    Message msg = Operations.receiveChat(br);
                    String target = msg.getUserTo();
                    PrintStream targetPs = interf.clients.getUserPs(interf.clients.getIndex(target));
                    Operations.sendChat(msg, targetPs);
                }
                //转发群聊消息
                else if(msgType.equals("groupChatMsg")){
                    Message msg = Operations.receiveGroupChat(br);
                    String target = msg.getUserTo();
                    PrintStream targetPs = interf.clients.getUserPs(interf.clients.getIndex(target));
                    sendGroupChat(msg, targetPs);
                }


            }catch (Exception e) {
                String user = interf.clients.getUserName(s);
                logout(user);
                s.close();
                System.out.println("\n"+user+"已断开连接...");
                break;
            }
        }

    }

}

