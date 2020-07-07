package utilities;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.net.*;
import java.util.ArrayList;
import javax.swing.*;

public class Interface_own extends JFrame implements ActionListener {
	private Info inf;
	private Socket s;
	private OnlineClients clients;

	private ServerSocket ss = null;

	public String userName;

	private Container container;	//容器
	private JTabbedPane msgTab;		//对话窗
	private JList<String> clientList; //显示用户列表
	private DefaultListModel<String> listModel; //存储在线用户列表
	private ArrayList<String> openedClient;	//打开了聊天窗口的用户列表

	private JPopupMenu popMenu1;
	private JPopupMenu popMenu2;
	private JPopupMenu popMenu3;

	private JMenuItem download;
	private JMenuItem delItem;
	private JMenuItem editItem;

	private JMenuItem newDir;
	private JMenuItem editItem2;
	private JMenuItem upload;

	private JMenuItem delItem2;
	private JMenuItem editItem3;
	private JMenuItem newDir2;
	private JMenuItem upload2;

	public Interface_own(Info inf, String user, OnlineClients olClients, Socket socket) {
		this.inf = inf;
		this.s = socket;
		this.userName = user;
		this.clients = olClients;
		this.clients.delUser(user);
		this.listModel = new DefaultListModel<>();
		this.clientList = new JList();
		this.openedClient = new ArrayList<>();
	}


	public void showInterface(){
		try{
			setSize(800, 600);
			setTitle("PP Chating Room   " + this.userName);

			this.container = getContentPane();
			this.msgTab = new JTabbedPane();

			for(int i=0; i<this.clients.getOnlineNames().size(); i++){
				if(this.clients.getUserName(i)!=this.userName) {
					String tmp = this.clients.getUserName(i);
					createTab(tmp);
					this.listModel.addElement(tmp);
				}
			}

			this.clientList.setModel(this.listModel);
			this.clientList.setFixedCellWidth(100);
			this.container.add(this.clientList, BorderLayout.EAST);
			this.container.add(this.msgTab);

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

	//创建聊天标签页
	private void createTab(String userName){
		JLabel label = new JLabel("", SwingConstants.CENTER);	//标签
		label.setHorizontalAlignment(JLabel.LEFT);
		JPanel panel = new JPanel();	//面板
		panel.add(label);

		JTextArea msgArea = new JTextArea();	//聊天消息框
		msgArea.setPreferredSize(new Dimension(600, 300));
		JScrollPane jsp = new JScrollPane(msgArea);
		panel.add(jsp, BorderLayout.SOUTH);

		JTextArea sendMsgArea = new JTextArea();	//发送消息框
		sendMsgArea.setPreferredSize(new Dimension(600, 80));
		JScrollPane jsp2 = new JScrollPane(sendMsgArea);
		panel.add(jsp2, BorderLayout.SOUTH);

		JButton sendMsgBtn = new JButton("发送消息");
		sendMsgBtn.setSize(20,10);
		panel.add(sendMsgBtn);

		this.msgTab.addTab(userName, panel);
		this.openedClient.add(userName);
	}

	//新用户登录后添加到用户列表
	public void addUser(String userName){
		this.listModel.addElement(userName);
		this.clientList.setModel(this.listModel);
		createTab(userName);
	}
	//用户下线后删除
	public void delUser(String userName){
		this.listModel.removeElement(userName);
		this.clientList.setModel(this.listModel);
		try{
			int index = this.openedClient.indexOf(userName);
			this.msgTab.remove(index);
		}catch (Exception e){}
	}

	@Override
	public void actionPerformed(ActionEvent e){

		int index = this.msgTab.getSelectedIndex();
		System.out.println(this.msgTab.getComponentCount());
		JPanel panel = (JPanel) this.msgTab.getComponentAt(index);
		System.out.println(panel.getComponentCount());
	    if(e.getSource()==getBtn(panel)){
	        String user = this.msgTab.getTitleAt(index);
	        System.out.println(user);
        }


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
		tmpl.add("A");
		tmpl.add("B");
		tmpl.add("C");
		OnlineClients ol = new OnlineClients(tmpl);
		Interface_own w = new Interface_own(inf, "A", ol, s);
		w.showInterface();

	}

}
