/**
 * Copyright (C), 2015-2020, XXX有限公司
 * FileName: someServer
 * Author:   ITryagain
 * Date:     2020/6/9 14:36
 * Description:
 * History:
 * <author>          <time>          <version>          <desc>
 * 作者姓名           修改时间           版本号              描述
 */

import java.rmi.AlreadyBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

/**
 * 〈一句话功能简述〉<br> 
 * 〈〉
 *
 * @author ITryagain
 * @create 2020/6/9
 * @since 1.0.0
 */

public class someServer {

    public static void main(String[] args){
        try {
            Registry registry = LocateRegistry.createRegistry(1099);
            someInterface si = new someImpl();
            registry.bind("hello", si);
            System.out.println("Server running ...");
        } catch (RemoteException | AlreadyBoundException e) {
            e.printStackTrace();
        }

    }

}
