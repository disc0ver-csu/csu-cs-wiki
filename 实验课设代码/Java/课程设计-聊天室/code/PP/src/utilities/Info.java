package utilities;

import java.io.*;
import java.util.ArrayList;

/*
* 存储用户个人信息
*/
public class Info implements Serializable{
	private String storePath;	//用户信息保存地址
	public String userName;	//用户名
	//private ArrayList<String> friendList;	//好友列表
	
	public Info(String userName) {
	    this.userName = userName;
	    //this.friendList = new ArrayList<String>();
	    this.storePath = "UserInfo/"+userName+".dat";
	}

	public static Info readInfo(String userName) {
        try {
            File file = new File("UserInfo/"+userName+".dat");
            FileInputStream in = new FileInputStream(file);
            ObjectInputStream objIn = new ObjectInputStream(in);
            Info inf = null;
            inf = (Info)objIn.readObject();
            objIn.close();
            System.out.println("成功读取"+userName+"信息");
            return inf;
        } catch (Exception e) {
            System.out.println("读取"+userName+"信息失败");
            e.printStackTrace();
            return null;
        }
    }
	public void saveInfo(){
        try {
            File dir = new File("UserInfo/");
            if(!dir.exists()) dir.mkdir();

            File file = new File("UserInfo/"+this.userName+".dat");
            FileOutputStream out = new FileOutputStream(file);
            ObjectOutputStream objOut = new ObjectOutputStream(out);
            objOut.writeObject(this);
            objOut.flush();
            objOut.close();
            System.out.println("成功保存"+userName+"信息");
        } catch (IOException e) {
            System.out.println("保存"+userName+"信息失败");
            e.printStackTrace();
        }
    }
}
