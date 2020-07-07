package Interface;

import utilities.*;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.PrintStream;
import java.net.*;
import java.util.ArrayList;
import java.util.Collections;
import javax.swing.*;

public class ClientInterface extends JFrame implements ActionListener {
	private Info inf;
	private Socket s;
	private PrintStream ps;
	private OnlineClients clients;
	private ClientInterface self;

	private ServerSocket ss = null;

	public String userName;

	private Container container;	//容器
	private JTextArea ServerMsgArea;	//服务器消息窗
	private JList<String> clientList; //显示用户列表
	private DefaultListModel<String> listModel; //存储在线用户列表
	private ArrayList<String> openedClient;	//打开了聊天窗口的用户列表
	private ArrayList<ChatWindow> opendedChatWindow; //已经打开的聊天窗口
	private ArrayList<String> openedGroup; //打开了聊天窗口的群聊列表
	private ArrayList<GroupChatWindow> opendedGroupChatWindow; //已经打开的群聊窗口


	public ClientInterface(Info inf, String user, OnlineClients olClients, Socket socket, PrintStream ps) {
		this.self = this;
		this.inf = inf;
		this.s = socket;
		this.ps = ps;
		this.userName = user;
		this.clients = olClients;
		this.clients.delUser(user);
		this.listModel = new DefaultListModel<>();
		this.clientList = new JList();
		this.openedClient = new ArrayList<>();
		this.opendedChatWindow = new ArrayList<>();
		this.openedGroup = new ArrayList<>();
		this.opendedGroupChatWindow = new ArrayList<>();

		//监听好友列表上的鼠标事件
		this.clientList.addMouseListener(
			new MouseAdapter() {
				public void mouseClicked(MouseEvent evt) {
					//双击弹出私聊对话框
					if (evt.getClickCount() == 2) {
						String target = clientList.getSelectedValue();
						if(!target.equals("创建群聊")) {
							if(openedGroup.indexOf(target)==-1) {
								ChatWindow w = new ChatWindow(inf.userName, target, ps);
								w.showChatWindow();
								openedClient.add(target);
								opendedChatWindow.add(w);
							}
							else{
								GroupChatWindow gw = opendedGroupChatWindow.get(openedGroup.indexOf(target));
								gw.showGroupChatWindow();
							}
						}
						else{
							checkBox c = new checkBox(self, clients);
							if(c.checkedUsers.size()>0) {
								//生成群聊名称
								ArrayList<String> tmp = new ArrayList<>();
								tmp.add(userName);
								for (int i = 0; i < c.checkedUsers.size(); i++) {tmp.add(c.checkedUsers.get(i));}
								Collections.sort(tmp);
								String groupName = tmp.get(0);
								for (int i = 1; i < tmp.size(); i++) {groupName = groupName + "_" + tmp.get(i);}


								GroupChatWindow gw = new GroupChatWindow(inf.userName, groupName, c.checkedUsers, ps);
								gw.showGroupChatWindow();
								openedGroup.add(groupName);
								opendedGroupChatWindow.add(gw);
								listModel.removeElement("创建群聊");
								listModel.addElement(groupName);
								listModel.addElement("创建群聊");
								clientList.setModel(listModel);
							}
						}
					}
				}
			}
		);
	}


	public void showInterface(){
		try{
			setSize(800, 430);
			setTitle("PP Chating Room   " + this.userName);

			this.container = getContentPane();

			this.ServerMsgArea = new JTextArea();
			this.ServerMsgArea.setWrapStyleWord(true);
			this.ServerMsgArea.setLineWrap(true);
			this.ServerMsgArea.setEditable(false);
			this.ServerMsgArea.setPreferredSize(new Dimension(600, 280));
			this.container.add(this.ServerMsgArea, BorderLayout.WEST);

			for(int i=0; i<this.clients.getOnlineNames().size(); i++){
				if(this.clients.getUserName(i)!=this.userName) {
					String tmp = this.clients.getUserName(i);
					this.listModel.addElement(tmp);
				}
			}
			this.listModel.addElement("创建群聊");

			this.clientList.setModel(this.listModel);
			this.clientList.setFixedCellWidth(150);
			this.container.add(this.clientList, BorderLayout.EAST);

			//窗口通用设置
		/*
		ImageIcon icon = new ImageIcon("icon/icon2.png");
		setIconImage(icon.getImage());*/
			setResizable(true);
			setLocationRelativeTo(null);
			setDefaultCloseOperation(EXIT_ON_CLOSE);
			setVisible(true);
		} catch (Exception e){
			System.out.println("显示界面出错");
			e.printStackTrace();
		}
	}


	//新用户登录后添加到用户列表
	public void addUser(String userName){
		this.listModel.removeElement("创建群聊");
		this.listModel.addElement(userName);
		this.listModel.addElement("创建群聊");
		this.clientList.setModel(this.listModel);
	}
	//用户下线后删除
	public void delUser(String userName){
		this.listModel.removeElement(userName);
		this.clientList.setModel(this.listModel);
		try{
			int index = this.openedClient.indexOf(userName);
			this.openedClient.remove(index);
			this.opendedChatWindow.remove(index);
		}catch (Exception e){}
	}

	//接收到用户消息后弹出窗口
	public void jumpWindow(Message msg){
		String source = msg.getUserFrom();
		String groupName = msg.getGroupName();
		System.out.println("GroupName:"+groupName);
		if(groupName.equals("###")){
			if(this.openedClient.contains(source)){
				System.out.println("已经打开窗口");
				int index = this.openedClient.indexOf(source);
				ChatWindow w = this.opendedChatWindow.get(index);
				w.addMessage(msg);
				if(!w.state){
					w.setVisible(true);
					w.state = true;
				}
			}
			else {
				System.out.println("没有打开窗口");
				ChatHistory.refreshHistory(msg.getUserTo(), msg.getUserFrom(), msg);
				ChatWindow w = new ChatWindow(this.userName, source, ps);
				this.openedClient.add(source);
				this.opendedChatWindow.add(w);
				w.showChatWindow();
			}
		}
		else{
			ArrayList<String> members = new ArrayList<>();
			String tmp[] = groupName.split("_");
			for(int i=0; i<tmp.length; i++){
				members.add(tmp[i]);
			}
			members.remove(this.userName);

			if(this.openedGroup.contains(groupName)){
				System.out.println("已经打开群聊窗口");
				int index = this.openedGroup.indexOf(groupName);
				GroupChatWindow w = this.opendedGroupChatWindow.get(index);
				w.addMessage(msg);
				if(!w.state){
					w.setVisible(true);
					w.state = true;
				}
			}
			else {
				System.out.println("没有打开群聊窗口");
				GroupChatHistory.refreshHistory(msg.getUserTo(), groupName, msg);
				GroupChatWindow gw = new GroupChatWindow(this.userName, groupName, members, ps);
				this.openedGroup.add(groupName);
				this.opendedGroupChatWindow.add(gw);
				gw.showGroupChatWindow();
				this.listModel.removeElement("创建群聊");
				this.listModel.addElement(groupName);
				this.listModel.addElement("创建群聊");
				this.clientList.setModel(this.listModel);
			}
		}
	}

	//显示服务器消息
	public void addServerMsg(String msg){
		String content = "服务器:" + msg + "\n";
		this.ServerMsgArea.append(content);
	}

	@Override
	public void actionPerformed(ActionEvent e){
	}

	private JButton getBtn(JPanel panel) {
		int count = panel.getComponentCount();
		for (int i = 0; i < count; i++) {
			Component comp = panel.getComponent(i);
			if (comp instanceof JButton) {
				JButton btn = (JButton) comp;
				return btn;
			}
		}
		return null;
	}


	public static void main (String[]args){
		Socket s = new Socket();
		Info inf = new Info("A");
		ArrayList<String> tmpl = new ArrayList<>();
		PrintStream ps = null;
		try {
			ps= new PrintStream(s.getOutputStream());
		} catch (Exception e){};
		tmpl.add("A");
		tmpl.add("B");
		tmpl.add("C");
		OnlineClients ol = new OnlineClients(tmpl);
		ClientInterface w = new ClientInterface(inf, "A", ol, s, ps);
		w.showInterface();

	}

}
