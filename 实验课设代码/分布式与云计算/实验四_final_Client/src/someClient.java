/**
 * Copyright (C), 2015-2020, XXX有限公司
 * FileName: someClient
 * Author:   ITryagain
 * Date:     2020/6/9 15:23
 * Description:
 * History:
 * <author>          <time>          <version>          <desc>
 * 作者姓名           修改时间           版本号              描述
 */

import java.rmi.NotBoundException;
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

public class someClient {

    public static void main(String[] args){
        try {
            Registry registry = LocateRegistry.getRegistry("localhost", 1099);
            someInterface hi = (someInterface) registry.lookup("hello");

            String name = hi.sayHello("world");
            System.out.println(name);

            name = hi.sayHello("lmw");
            System.out.println(name);

        } catch (NotBoundException | RemoteException e1) {
            e1.printStackTrace();
        }
    }
}
