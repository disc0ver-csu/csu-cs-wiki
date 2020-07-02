/**
 * Copyright (C), 2015-2020, XXX有限公司
 * FileName: PersonSkeleton
 * Author:   ITryagain
 * Date:     2020/6/9 12:05
 * Description:
 * History:
 * <author>          <time>          <version>          <desc>
 * 作者姓名           修改时间           版本号              描述
 */
package 实验四.实验四_RMI.server;

import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * 〈一句话功能简述〉<br> 
 * 〈〉
 *
 * @author ITryagain
 * @create 2020/6/9
 * @since 1.0.0
 */

public class PersonSkeleton extends Thread{

    private PersonServer personServer;

    public PersonSkeleton(PersonServer personServer){
        this.personServer = personServer;
    }

    public void run(){
        try {
            ServerSocket serverSocket = new ServerSocket(8000);
            Socket socket = serverSocket.accept();
            ObjectInputStream ois = new ObjectInputStream(socket.getInputStream());
            ObjectOutputStream oos = new ObjectOutputStream(socket.getOutputStream());
            while(socket != null){
                String method = (String)ois.readObject();
                if(method.equals("age")){
                    int age = personServer.getAge();
                    oos.writeInt(age);
                    oos.flush();
                }else if(method.equals("name")){
                    String name = personServer.getName();
                    oos.writeObject(name);
                    oos.flush();
                }
            }
        } catch (Throwable e) {
            e.printStackTrace();
        }
    }

}
