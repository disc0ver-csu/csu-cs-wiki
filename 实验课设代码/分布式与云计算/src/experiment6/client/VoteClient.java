/**
 * Copyright (C), 2015-2020, XXX有限公司
 * FileName: VoteClient
 * Author:   ITryagain
 * Date:     2020/6/16 11:20
 * Description:
 * History:
 * <author>          <time>          <version>          <desc>
 * 作者姓名           修改时间           版本号              描述
 */
package experiment6.client;


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
 * @create 2020/6/16
 * @since 1.0.0
 */

public class VoteClient {
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

            NameComponent nc = new NameComponent("Vote", "");
            NameComponent path[] = {nc};
            VoteAppTest.Votes h = VoteAppTest.VotesHelper.narrow(ncRef.resolve(path));
            System.out.println("客户端调用 CORBA 服务器端的 'castVote' 方法");
            h.castVote("lmw");
            h.castVote("wx");
            h.castVote("szh");
            h.castVote("lmw");
            VoteAppTest.Vote[] votes = h.getList();
            for(int i = 0; i < votes.length; i ++){
                System.out.println(votes[i].name + " 获得 " + votes[i].value + " 票");
            }

        }catch (Exception e){

        }

    }
}
