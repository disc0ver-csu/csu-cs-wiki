/**
 * Copyright (C), 2015-2020, XXX有限公司
 * FileName: HelloClient
 * Author:   ITryagain
 * Date:     2020/6/12 12:55
 * Description:
 * History:
 * <author>          <time>          <version>          <desc>
 * 作者姓名           修改时间           版本号              描述
 */
package experiment5.client;

import experiment5.HelloApp.Hello;
import experiment5.HelloApp.HelloHelper;
import org.omg.CORBA.ORB;
import org.omg.CORBA.Object;
import org.omg.CosNaming.NameComponent;
import org.omg.CosNaming.NamingContext;
import org.omg.CosNaming.NamingContextHelper;

import java.util.Properties;

/**
 * 〈一句话功能简述〉<br> 
 * 〈〉
 *
 * @author ITryagain
 * @create 2020/6/12
 * @since 1.0.0
 */

public class HelloClient {

    public static void main(String[] args){

        try{
            Properties props = new Properties();
            props.put("org.omg.CORBA.ORBInitialHost", "127.0.0.1");
            props.put("org.omg.CORBA.ORBInitialPort", "8000");

            System.out.println("ORB Initial ... ");
            ORB orb = ORB.init(args, props);

            // 获取命名上下文
            Object obRef = orb.resolve_initial_references("NameService");
            NamingContext ncRef = NamingContextHelper.narrow(obRef);

            NameComponent nc = new NameComponent("Hello", "");
            NameComponent path[] = {nc};
            Hello h = HelloHelper.narrow(ncRef.resolve(path));
            System.out.println("客户端调用 CORBA 服务器端的 'sayHello' 方法");
            System.out.println("欢迎，" + h.asyHello("lmw"));
        }catch (Exception e){

        }

    }

}
