package Interface;

import utilities.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.PrintStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

public class ServerInterface extends JFrame implements ActionListener {
	private PrintStream ps;
	public OnlineClients clients;
	private ServerInterface self;
	private JPanel EditMsgArea;
	private JTextArea EditMsg;
	private JButton SendMsgBtn;
	private JPanel mainPanel;

	private ServerSocket ss = null;

	public String userName;
	private Container container;	//容器
	private JTextArea broadcastArea;	//服务器消息窗
	private JList<String> clientList; //显示用户列表
	private DefaultListModel<String> listModel; //存储在线用户列表
	private ArrayList<String> openedClient;	//打开了聊天窗口的用户列表
	private ArrayList<ChatWindow> opendedChatWindow; //已经打开的聊天窗口


	public ServerInterface() {
		this.self = this;
		this.listModel = new DefaultListModel<>();
		this.clientList = new JList();
		this.openedClient = new ArrayList<>();
		this.opendedChatWindow = new ArrayList<>();
		this.mainPanel = new JPanel();
		this.EditMsgArea = new JPanel();

		this.broadcastArea = new JTextArea();
		this.broadcastArea.setWrapStyleWord(true);
		this.broadcastArea.setLineWrap(true);
		this.broadcastArea.setEditable(false);
		this.broadcastArea.setPreferredSize(new Dimension(600, 280));
		
		this.EditMsg = new JTextArea();
		this.EditMsg.setWrapStyleWord(true);
		this.EditMsg.setLineWrap(true);
		this.EditMsg.setPreferredSize(new Dimension(500, 100));
		this.EditMsgArea.add(this.EditMsg, BorderLayout.WEST);

		this.SendMsgBtn = new JButton("发送信息");
		this.SendMsgBtn.setPreferredSize(new Dimension(100,100));
		addActionListener(this.SendMsgBtn);
		this.EditMsgArea.add(this.SendMsgBtn, BorderLayout.EAST);

		//监听好友列表上的鼠标事件
		this.clientList.addMouseListener(
			new MouseAdapter() {
				public void mouseClicked(MouseEvent evt) {
					//双击弹出私聊对话框
					if (evt.getClickCount() == 2) {
						String target = clientList.getSelectedValue();
						if(!target.equals("强制下线")) {
							int index = clients.getIndex(target);
							ChatWindow w = new ChatWindow("服务器", target, clients.getUserPs(index));
							w.showChatWindow();
							openedClient.add(target);
							opendedChatWindow.add(w);
						}
						else{
							checkBox c = new checkBox(self, clients);
							for(int i=0; i<c.checkedUsers.size(); i++){
								forceLogoutUser(c.checkedUsers.get(i));
							}
						}
					}
				}
			}
		);
	}

	public void showInterface(){
		try {
			setSize(800, 430);
			setTitle("PP Chating Room Server");

			this.container = getContentPane();

			this.broadcastArea = new JTextArea();
			this.broadcastArea.setWrapStyleWord(true);
			this.broadcastArea.setLineWrap(true);
			this.broadcastArea.setEditable(false);
			this.broadcastArea.setPreferredSize(new Dimension(635, 280));
			this.container.add(this.broadcastArea, BorderLayout.WEST);

			for (int i = 0; i < this.clients.getOnlineNames().size(); i++) {
				if (this.clients.getUserName(i) != this.userName) {
					String tmp = this.clients.getUserName(i);
					this.listModel.addElement(tmp);
				}
			}
			this.listModel.addElement("强制下线");

			this.mainPanel.setPreferredSize(new Dimension(640, 420));
			this.mainPanel.add(this.broadcastArea, BorderLayout.NORTH);
			this.mainPanel.add(this.EditMsgArea, BorderLayout.SOUTH);
			this.container.add(this.mainPanel, BorderLayout.WEST);

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
		System.out.println("\n添加新用户:"+userName+"\n");
		this.listModel.removeElement("强制下线");
		this.listModel.addElement(userName);
		this.listModel.addElement("强制下线");
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
	
	//显示服务器消息
	public void addServerMsg(String msg){
		String content = "广播:" + msg + "\n";
		this.broadcastArea.append(content);
	}

	//强制下线用户
	private void forceLogoutUser(String userName) {
		Socket userSocket = clients.getUserSocket(userName);
		try{
			int index = clients.getIndex(userName);
			Operations.sendMsg("ForceLogout", userName, clients.getUserPs(index));
		}catch (Exception e) {System.out.println("强制下线用户失败！");}
		clients.delUser(userName);
		listModel.removeElement(userName);
		clientList.setModel(listModel);
		for(int i=0; i<clients.getSize(); i++){
			Socket tmpS = clients.getUserSocket(i);
			try {
				Operations.sendMsg("UserLogout", userName, clients.getUserPs(i));
			} catch (Exception e){
				System.out.println("发送用户下线信息错误！");
				System.out.println(e.getMessage());
			}
		}
	}

	@Override
	public void actionPerformed(ActionEvent e){
	}

	private void addActionListener(JButton btn) {
		// 为按钮绑定监听器
		btn.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				//添加到对话框
				String content = EditMsg.getText();
				//发送消息
				try {
					for(int i=0; i<clients.getSize(); i++){
						Socket tmpS = clients.getUserSocket(i);
						try {
							int index = clients.getIndex(tmpS);
							System.out.println("向"+clients.getUserName(i)+"广播信息...");
							Operations.sendMsg("服务器", content, clients.getUserPs(index));
						} catch (Exception excp){
							System.out.println("向"+clients.getUserName(i)+"广播信息错误！");
						}
					}
					broadcastArea.append("我："+content + "\n");
					System.out.println("已广播新用户上线信息");
					EditMsg.setText("");
				} catch (Exception E){E.printStackTrace();}
			}
		});
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
		ServerInterface w = new ServerInterface();
		w.showInterface();

	}

}
