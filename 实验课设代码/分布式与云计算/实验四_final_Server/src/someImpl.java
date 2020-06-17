/**
 * Copyright (C), 2015-2020, XXX有限公司
 * FileName: someImpl
 * Author:   ITryagain
 * Date:     2020/6/9 14:33
 * Description:
 * History:
 * <author>          <time>          <version>          <desc>
 * 作者姓名           修改时间           版本号              描述
 */

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

/**
 * 〈一句话功能简述〉<br> 
 * 〈〉
 *
 * @author ITryagain
 * @create 2020/6/9
 * @since 1.0.0
 */

public class someImpl extends UnicastRemoteObject implements someInterface {

    public someImpl() throws RemoteException {
        super();
    }

    @Override
    public String sayHello(String name) throws RemoteException {
        System.out.println("Client-" + name + " : invoking \" sayHello \"");
        return "Hello " + name + " this is a message from Remote Method";
    }
}
