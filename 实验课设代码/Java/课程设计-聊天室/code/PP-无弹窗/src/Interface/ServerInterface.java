package Interface;

import utilities.*;

import javax.swing.*;
import javax.swing.text.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.net.Socket;
import java.util.*;

public class ServerInterface extends JFrame implements ActionListener {
	public OnlineClients clients;
	private ServerInterface self;
	private JPanel EditMsgArea;
	private JTextArea EditMsg;
	private JButton SendMsgBtn;
	private JPanel mainPanel;
	private JScrollPane jsp;

	public String userName;
	private Container container;	//容器
	private JTextPane broadcastArea;	//服务器消息窗
	private JList<String> clientList; //显示用户列表
	private DefaultListModel<String> listModel; //存储在线用户列表
	private ArrayList<String> openedClient;	//打开了聊天窗口的用户列表
	private ArrayList<ChatWindow> opendedChatWindow; //已经打开的聊天窗口

	private Style baseStyle;	//文本基本样式
	private Map<String, javax.swing.text.Style> styles;	//用户-样式对应表
	private Map<String, Color> userColors;	//用户-颜色对应表
	private ArrayList<Color> colors;	//颜色表


	public ServerInterface() {
		this.self = this;
		this.listModel = new DefaultListModel<>();
		this.clientList = new JList();
		this.clientList.setFont(new Font("微软雅黑",Font.BOLD,12));
		this.openedClient = new ArrayList<>();
		this.opendedChatWindow = new ArrayList<>();
		this.mainPanel = new JPanel();
		this.EditMsgArea = new JPanel();

		this.broadcastArea = new JTextPane();
		this.broadcastArea.setEditable(false);
		this.broadcastArea.setPreferredSize(new Dimension(610, 280));
		
		this.EditMsg = new JTextArea();
		this.EditMsg.setWrapStyleWord(true);
		this.EditMsg.setLineWrap(true);
		this.EditMsg.setFont(new Font("微软雅黑",Font.PLAIN,14));
		this.EditMsg.setPreferredSize(new Dimension(500, 30));
		this.EditMsg.setBorder(BorderFactory.createLineBorder(new Color(247,141,63)));
		this.EditMsg.setBorder(new RoundBorder(new Color(247,141,63)));
		this.EditMsgArea.add(this.EditMsg, BorderLayout.WEST);
		this.EditMsgArea.setBackground(Color.WHITE);

		this.SendMsgBtn = new JButton("发送信息");
		this.SendMsgBtn.setFont(new Font("微软雅黑",Font.BOLD,13));
		this.SendMsgBtn.setPreferredSize(new Dimension(100,30));
		this.SendMsgBtn.setBackground(new Color(185,237,248));//设置背景色
		this.SendMsgBtn.setBorderPainted(false);
		addActionListener(this.SendMsgBtn);
		this.EditMsgArea.add(this.SendMsgBtn, BorderLayout.EAST);

		Style s = this.broadcastArea.getStyledDocument().addStyle(null, null);
		StyleConstants.setFontFamily(s, "微软雅黑");// 为style样式设置字体属性
		StyleConstants.setFontSize(s, 18);// 为style样式设置字体大小

		this.styles = new HashMap<>();
		this.userColors = new HashMap<>();
		this.baseStyle = this.broadcastArea.addStyle("base",s);
		Style s1 = initStyle(new Color(33, 31, 48),"broadcast");
		this.styles.put("broadcast", s1);
		Style s2 = initStyle(new Color(50, 56, 77),"me");
		this.styles.put("me", s2);
		this.colors = new ArrayList<>();
		this.initColors();

		//监听用户列表上的鼠标事件
		this.clientList.addMouseListener(
			new MouseAdapter() {
				public void mouseClicked(MouseEvent evt) {
					//双击弹出私聊对话框
					if (evt.getClickCount() == 2) {
						String target = clientList.getSelectedValue();
						if(target.equals("强制下线")) {
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

	//初始化颜色表
	private void initColors(){
		this.colors.add(new Color(226, 153, 48));
		this.colors.add(new Color(47, 170, 238));
		this.colors.add(new Color(171, 196, 161));
		this.colors.add(new Color(42, 67, 170));
	}

	public void showInterface(){
		try {
			setSize(800, 370);
			setTitle("PP Chating Room Server");

			this.container = getContentPane();

			this.broadcastArea = new JTextPane();
			this.broadcastArea.setEditable(false);
			this.broadcastArea.setBorder(new RoundBorder(new Color(247,141,63)));
			this.broadcastArea.setPreferredSize(new Dimension(635, 280));
			this.jsp = new JScrollPane(this.broadcastArea);
			this.jsp.setPreferredSize(new Dimension(605, 280));
			this.jsp.setBorder(BorderFactory.createEmptyBorder());

			for (int i = 0; i < this.clients.getOnlineNames().size(); i++) {
				if (this.clients.getUserName(i) != this.userName) {
					String tmp = this.clients.getUserName(i);
					this.listModel.addElement(tmp);
				}
			}
			this.listModel.addElement("强制下线");

			this.mainPanel.setPreferredSize(new Dimension(640, 370));
			this.mainPanel.add(this.jsp, BorderLayout.NORTH);
			this.mainPanel.add(this.EditMsgArea, BorderLayout.SOUTH);
			this.mainPanel.setBackground(Color.WHITE);
			this.container.add(this.mainPanel, BorderLayout.WEST);

			this.clientList.setModel(this.listModel);
			this.clientList.setFixedCellWidth(150);
			this.container.add(this.clientList, BorderLayout.EAST);
			this.container.setBackground(Color.WHITE);


			//窗口通用设置
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
		Color c = this.colors.get(0);
		this.colors.remove(0);
		this.userColors.put(userName, c);
		Style style = initStyle(c, userName);
		this.styles.put(userName, style);
	}
	//获取某个用户的颜色
	public String getUserColor(String userName){
		Color c = this.userColors.get(userName);
		String str = "";
		str = String.valueOf(c.getRed());
		str += ",";
		str += String.valueOf(c.getGreen());
		str += ",";
		str += String.valueOf(c.getBlue());
		return str;
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
				String target = clientList.getSelectedValue();
				String content = EditMsg.getText();
				if(target.equals("强制下线")){
					//发送消息
					try {
						for(int i=0; i<clients.getSize(); i++){
							try {
								System.out.println("向"+clients.getUserName(i)+"广播信息...");
								Operations.sendMsg("服务器", content, clients.getUserPs(i));
							} catch (Exception excp){
								System.out.println("向"+clients.getUserName(i)+"广播信息错误！");
							}
						}
						addStyledText(" 广播("+ Operations.getCurrentTime() +")："+content + "\n","broadcast");
						System.out.println("已广播信息");
					} catch (Exception E){E.printStackTrace();}
				}
				else{
					System.out.println("向"+target+"发送信息...");
					int index = clients.getIndex(target);
					try {
						Operations.sendMsg("服务器", content, clients.getUserPs(index));
						addStyledText(" 服务器对"+target+"说("+ Operations.getCurrentTime() +")："+content + "\n","me");
					}catch (Exception E){E.printStackTrace();}
				}
				EditMsg.setText("");
			}
		});
	}


	//生成新样式
	private Style initStyle(Color c, String name){
		Style s = this.broadcastArea.addStyle(name, this.baseStyle);
		StyleConstants.setForeground(s, c);
		StyleConstants.setFontSize(s,16);
		return s;
	}

	//将纯文本转化为样式文本并插入到界面
	private void addStyledText(String text, String name){
		try {
			Style style = this.styles.get(name);
			this.broadcastArea.getStyledDocument().insertString(
					this.broadcastArea.getStyledDocument().getLength(),
					text, style
			);
		}catch (Exception e){e.printStackTrace();}
	}

	public static void main (String[]args){
		Color c = new Color(123,231,132);

		System.out.println(c.getGreen());
	}

}
