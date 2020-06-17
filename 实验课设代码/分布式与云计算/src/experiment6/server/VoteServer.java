/**
 * Copyright (C), 2015-2020, XXX有限公司
 * FileName: VoteServer
 * Author:   ITryagain
 * Date:     2020/6/16 11:18
 * Description:
 * History:
 * <author>          <time>          <version>          <desc>
 * 作者姓名           修改时间           版本号              描述
 */
package experiment6.server;

import experiment6.VoteAppTest.VotesImpl;
import org.omg.CORBA.ORB;
import org.omg.CORBA.Object;
import org.omg.CosNaming.NameComponent;
import org.omg.CosNaming.NamingContext;
import org.omg.CosNaming.NamingContextHelper;
import org.omg.CosNaming.NamingContextPackage.CannotProceed;
import org.omg.CosNaming.NamingContextPackage.InvalidName;
import org.omg.CosNaming.NamingContextPackage.NotFound;

import java.util.Properties;

/**
 * 〈一句话功能简述〉<br> 
 * 〈〉
 *
 * @author ITryagain
 * @create 2020/6/16
 * @since 1.0.0
 */

public class VoteServer {
    public static void main(String[] args){

        try {
            Properties props = new Properties();
            props.put("org.omg.CORBA.ORBInitialHost", "127.0.0.1");
            props.put("org.omg.CORBA.ORBInitialPort", "8000");


            System.out.println("ORB initial ...");
            ORB orb = ORB.init(args, props);

            System.out.println("将实例注册到 ORB");
            VotesImpl voteImpl = new VotesImpl();
            orb.connect(voteImpl);

            // 获取命名上下文
            Object obRef = orb.resolve_initial_references("NameService");
            NamingContext ncRef = NamingContextHelper.narrow(obRef);
            // 绑定命名中的对象引用
            NameComponent nc = new NameComponent("Vote", "");
            NameComponent path[] = {nc};
            ncRef.rebind(path, voteImpl);

            java.lang.Object sync = new java.lang.Object();
            synchronized (sync){
                sync.wait();
            }
            System.out.println("等待 CORBA 客户端调用 ...");

        } catch (NotFound | CannotProceed | InvalidName | org.omg.CORBA.ORBPackage.InvalidName | InterruptedException notFound) {
            notFound.printStackTrace();
        }

    }
}
