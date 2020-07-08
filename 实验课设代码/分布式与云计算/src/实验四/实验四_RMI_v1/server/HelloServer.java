/**
 * Copyright (C), 2015-2020, XXX有限公司
 * FileName: HelloServer
 * Author:   ITryagain
 * Date:     2020/6/8 17:19
 * Description:
 * History:
 * <author>          <time>          <version>          <desc>
 * 作者姓名           修改时间           版本号              描述
 */
package 实验四.实验四_RMI.实验四_RMI_v1.server;

import 实验四.实验四_RMI_v1.HelloTask;
import 实验四.实验四_RMI_v1.IHello;

import java.rmi.AlreadyBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

/**
 * 〈一句话功能简述〉<br> 
 * 〈〉
 *
 * @author ITryagain
 * @create 2020/6/8
 * @since 1.0.0
 */

public class HelloServer extends UnicastRemoteObject implements IHello {

    public static void main(String[] args){
        try {
            HelloServer s = new HelloServer();
            Registry registry = LocateRegistry.createRegistry(1099);
            registry.bind("hello", s);
            System.out.println("Start...");
        } catch (RemoteException | AlreadyBoundException e) {
            e.printStackTrace();
        }

    }

    public HelloServer() throws RemoteException{
        super();
    }

    @Override
    public String say(HelloTask task) throws RemoteException {
        String result = task.execute();
        System.out.println("execute say,task.execute : " + result);
        return result;
    }

}
