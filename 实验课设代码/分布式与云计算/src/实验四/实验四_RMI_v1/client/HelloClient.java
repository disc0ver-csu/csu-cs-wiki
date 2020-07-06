/**
 * Copyright (C), 2015-2020, XXX有限公司
 * FileName: HelloClient
 * Author:   ITryagain
 * Date:     2020/6/8 18:06
 * Description:
 * History:
 * <author>          <time>          <version>          <desc>
 * 作者姓名           修改时间           版本号              描述
 */
package 实验四.实验四_RMI.实验四_RMI_v1.client;

import 实验四.实验四_RMI_v1.HelloTask;
import 实验四.实验四_RMI_v1.HelloTaskImpl;
import 实验四.实验四_RMI_v1.IHello;

import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;

/**
 * 〈一句话功能简述〉<br> 
 * 〈〉
 *
 * @author ITryagain
 * @create 2020/6/8
 * @since 1.0.0
 */

public class HelloClient {

    public static void main(String[] args){
        try {
            IHello hi = (IHello) Naming.lookup("rmi://127.0.0.1:1099/hello");

            HelloTask task = new HelloTaskImpl();
            for(int i = 0; i < 10; i ++){
                System.out.println(hi.say(task));
            }
        } catch (NotBoundException | MalformedURLException | RemoteException e) {
            e.printStackTrace();
        }

    }

}
