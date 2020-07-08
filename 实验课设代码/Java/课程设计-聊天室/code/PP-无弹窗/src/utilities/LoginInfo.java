package utilities;

import java.io.*;

/*
* 存储"+this.userName+"登录信息
*/
public class LoginInfo implements Serializable {
	private String userName;
	private String password;
	
	public LoginInfo(String userName, String password) {
		this.userName = userName;
		this.password = password;
	}
	
	public String getUserName() {
		return this.userName;
	}
	public String getUserPassword() {
		return this.password;
	}
	
	public void saveLoginInfo() {
		//保存登录信息
		File dir = new File("LoginInfo");
		if (!dir.exists()) {
			dir.mkdir();
		}
		File file =new File("LoginInfo/"+this.userName+".dat");
		FileOutputStream out;
		try {
		    out = new FileOutputStream(file);
		    ObjectOutputStream objOut = new ObjectOutputStream(out);
		    objOut.writeObject(this);
		    objOut.flush();
		    objOut.close();
		    System.out.println("成功保存"+this.userName+"登录信息");
		} catch (IOException e) {
		    System.out.println("保存"+this.userName+"登录信息失败");
		    e.printStackTrace();
		}
	}
	
	public static LoginInfo getLoginInfo(String userName) {
		//读取"+this.userName+"信息
		File file = new File("LoginInfo/"+userName+".dat");
		FileInputStream in;
		try {
			in = new FileInputStream(file);
			ObjectInputStream objIn = new ObjectInputStream(in);
			LoginInfo inf = null;
			inf = (LoginInfo)objIn.readObject();
            objIn.close();
            System.out.println("成功读取"+userName+"登录信息");
            return inf;
		} catch (Exception e) {
		    System.out.println("读取"+userName+"登录信息失败");
		    e.printStackTrace();
		    return null;
		} 
	}
}
