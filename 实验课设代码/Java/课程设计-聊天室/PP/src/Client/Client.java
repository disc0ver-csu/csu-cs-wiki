package Client;

import java.net.*;
import java.io.*;
import javax.swing.*;
import java.lang.*;
import java.util.ArrayList;

import Interface.ClientInterface;
import utilities.*;

class Client extends JFrame{
	private Socket s = null;
	private OutputStream os;
	private InputStream is;
	public PrintStream ps;
	private BufferedReader br;

	
	private String user = null;
	private String password = null;

	private Info inf;
	private ClientInterface interf;
	private OnlineClients clients;
	
	public Client() throws Exception{
		/*与服务器建立连接*/
		this.s = new Socket("127.0.0.1", 9888);
		this.os = s.getOutputStream();
		this.is = s.getInputStream();
		this.ps = new PrintStream(os);
		this.br = new BufferedReader(new InputStreamReader(this.is));
		/*登录部分*/
        //登录
        while(true){
            this.user = (String)JOptionPane.showInputDialog(null, "输入用户名", "登陆", JOptionPane.PLAIN_MESSAGE);
            this.password = (String)JOptionPane.showInputDialog(null, "输入密码", "登陆", JOptionPane.PLAIN_MESSAGE);
            if(this.user==null) continue;

            System.out.println("发出登陆请求");
            Operations.sendMsg("CheckUserInfo", this.user, this.password, this.ps);

            String loginState = br.readLine();
            if(loginState!=null) {
                if (loginState.equals("WrongPassword")) {
                    //密码错误提示重新输入信息
                    JOptionPane.showMessageDialog(null, "密码错误");
                }
                else break;
            }
        }
        System.out.println("登陆成功！");

        try {
            System.out.println("\n开始监听信息...\n");
            while(true) {
                String msgType = br.readLine();
                if(msgType != null) {
                    System.out.println("\n接收到 " + msgType);
                }
                if(msgType.equals("ReceiveUserInfo")){
                    System.out.println("准备接收用户信息...");
                    String userName = br.readLine();
                    this.inf = new Info(userName);
                    System.out.println("用户信息接收完成");
                }
                else if(msgType.equals("ReceiveOnlineClients")){
                    System.out.println("准备接收在线用户列表...");
                    int length = Integer.parseInt(br.readLine());
                    ArrayList<String> onlineClients = new ArrayList<>();
                    for(int i=0; i<length; i++){
                        onlineClients.add(br.readLine());
                    }
                    this.clients = new OnlineClients(onlineClients);
                    System.out.println("在线用户列表接收完成："+this.clients.getOnlineNames());
                    ClientInterface interf = new ClientInterface(this.inf, this.user, this.clients, s, this.ps);
                    this.interf = interf;
                    System.out.println("显示界面\n");
                    this.interf.showInterface();
                }
                //接收私聊信息
                else if(msgType.equals("chatMsg")){
                    try {
                        Message msg = new Message(br.readLine(), br.readLine(), br.readLine());
                        //在界面添加消息/弹出聊天窗口
                        if(msg.getUserFrom().equals("服务器")){
                            this.interf.addServerMsg(msg.getContent());
                        }
                        else{
                            this.interf.jumpWindow(msg);
                        }
                    } catch (Exception e) {
                        System.out.println("接收聊天信息错误！"+e.getMessage());
                    }
                }
                //接收服务器广播
                else if(msgType.equals("服务器")){
                    this.interf.addServerMsg(br.readLine());
                }
                //接收群聊消息
                else if(msgType.equals("groupChatMsg")){
                    try {
                        Message msg = new Message(br.readLine(), br.readLine(), this.user, br.readLine());
                        //在界面添加消息/弹出聊天窗口
                        this.interf.jumpWindow(msg);
                    } catch (Exception e) {
                        System.out.println("接收聊天信息错误！"+e.getMessage());
                    }
                }
                //新用户上线信息
                else if(msgType.equals("NewUser")){
                    String userName = br.readLine();
                    System.out.println("新用户上线："+userName);
                    clients.addUser(userName);
                    this.interf.addUser(userName);
                    this.interf.addServerMsg(userName+"上线了");
                }
                //其他用户下线
                else if(msgType.equals("UserLogout")){
                    String userName = br.readLine();
                    System.out.println("用户下线："+userName);
                    clients.delUser(userName);
                    this.interf.delUser(userName);
                    this.interf.addServerMsg(userName+"下线了");
                }
                //强制下线
                else if(msgType.equals("ForceLogout")){
                    System.out.println("被服务器强制下线！");
                    System.exit(0);
                }
            }
        }
        catch (Exception e) {
            e.printStackTrace();
            return;
        }
	}

	public static void main(String[] args) throws Exception{
		new Client();
	}

}
