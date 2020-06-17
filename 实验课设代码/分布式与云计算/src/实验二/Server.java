/**
 * Copyright (C), 2015-2020, XXX有限公司
 * FileName: HelloServer
 * Author:   ITryagain
 * Date:     2020/6/8 9:53
 * Description:
 * History:
 * <author>          <time>          <version>          <desc>
 * 作者姓名           修改时间           版本号              描述
 */
package 实验二;

import java.io.IOException;
import java.net.ServerSocket;

/**
 * 〈一句话功能简述〉<br> 
 * 〈〉
 *
 * @author ITryagain
 * @create 2020/6/8
 * @since 1.0.0
 */

public class Server {

    private static ServerSocket ss;

    public static void main(String[] args){
        try {
            ss = new MyStreamServerSocket(8000);

        } catch (IOException e) {
            e.printStackTrace();
        }

        new Thread(() -> {
            try{
                MyStreamSocket socket = (MyStreamSocket) ss.accept();
                socket.init();
                System.out.println("进入了一个客户机对象：" + socket.getRemoteSocketAddress());
                socket.sendMessage("连接成功");
                while(true){
                    String message = socket.reciveMessage();
                    System.out.println("收到信息: " + message + " 来自：" + socket.getInetAddress().getHostAddress());
                }
            }catch(IOException e){
                e.printStackTrace();
            }
        }).start();

    }

}
