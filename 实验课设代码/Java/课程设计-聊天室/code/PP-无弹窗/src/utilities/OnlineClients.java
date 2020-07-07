package utilities;

import java.awt.*;
import java.io.*;
import java.util.*;
import java.net.*;

/*
* 存储在线用户
*/
public class OnlineClients implements Serializable {
	private ArrayList<String> onlineNames;
	private ArrayList<Socket> onlineSockets;
	private ArrayList<PrintStream> onlinePs;
	private ArrayList<BufferedReader> onlineBr;

	private int isClient;

	//服务器-初始化在线用户列表
	public OnlineClients(){
		this.onlineSockets = new ArrayList<>();
		this.onlineNames = new ArrayList<>();
		this.onlinePs = new ArrayList<>();
		this.onlineBr = new ArrayList<>();
		this.isClient = 0;
	}
	//客户端-初始化在线用户列表
	public OnlineClients(ArrayList<String> onlineNames){
		this.onlineNames = onlineNames;
		this.isClient = 1;
	}


	public ArrayList<String> getOnlineNames() {
		return this.onlineNames;
	}
	public ArrayList<Socket> getOnlineSockets(){
		return this.onlineSockets;
	}

	public String getUserName(int index){
		return this.onlineNames.get(index);
	}
	public String getUserName(Socket s){
		int index = this.onlineSockets.indexOf(s);
		return this.getOnlineNames().get(index);
	}

	public Socket getUserSocket(int index){
		return this.onlineSockets.get(index);
	}
	public Socket getUserSocket(String userName) {
		int index = onlineNames.indexOf(userName);
		return this.onlineSockets.get(index);
	}

	public PrintStream getUserPs(int index){return this.onlinePs.get(index);}
	public BufferedReader getUserBr(int index){return this.onlineBr.get(index);}

	public int getIndex(Socket s){return this.onlineSockets.indexOf(s);}
	public int getIndex(String user){return this.onlineNames.indexOf(user);}
	public int getSize(){return this.onlineNames.size();}

	public void addUser(String userName, Socket s, BufferedReader br, PrintStream ps) {
		//服务器使用
		onlineNames.add(userName);
		onlineSockets.add(s);
		try {
			onlinePs.add(ps);
			onlineBr.add(br);
		}catch (Exception e){e.printStackTrace();}

	}
	public void addUser(String userName) {
		//客户端使用
		onlineNames.add(userName);
	}
	public void delUser(String userName){
		int i= this.onlineNames.indexOf(userName);
		this.onlineNames.remove(i);
		if(this.isClient!=1) {
			this.onlineSockets.remove(i);
			this.onlineBr.remove(i);
			this.onlinePs.remove(i);
		}
	}
}
