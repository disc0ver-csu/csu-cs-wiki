/**
 * Copyright (C), 2015-2020, XXX有限公司
 * FileName: EchoServer
 * Author:   ITryagain
 * Date:     2020/6/10 15:33
 * Description:
 * History:
 * <author>          <time>          <version>          <desc>
 * 作者姓名           修改时间           版本号              描述
 */
package 实验三.echo.data.server;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.util.Date;

/**
 * 〈一句话功能简述〉<br> 
 * 〈〉
 *
 * @author ITryagain
 * @create 2020/6/10
 * @since 1.0.0
 */

public class EchoServer {

    private final static int PORT = 8000;
    private final static String HOST = "localhost";

    public static void main(String[] args){
        try {
            DatagramSocket datagramSocket = new DatagramSocket(PORT);
            System.out.println("服务器启动");
            while(true){
                DatagramPacket request = new DatagramPacket(new byte[1024], 1024);
                datagramSocket.receive(request);

                DatagramPacket response = new DatagramPacket(request.getData(), request.getLength(), request.getAddress(), request.getPort());
                datagramSocket.send(response);

                String result = new String(response.getData(), 0, response.getLength());
                System.out.println("客户端 " + request.getAddress() + ":" + request.getPort() + " 发送命令 " + result);
            }
        } catch (java.io.IOException e) {
            e.printStackTrace();
        }
    }

}
