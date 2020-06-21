/**
 * Copyright (C), 2015-2020, XXX有限公司
 * FileName: DaytimeServer
 * Author:   ITryagain
 * Date:     2020/6/9 17:25
 * Description:
 * History:
 * <author>          <time>          <version>          <desc>
 * 作者姓名           修改时间           版本号              描述
 */
package 实验三.daytime.data.server;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;
import java.util.Date;

/**
 * 〈一句话功能简述〉<br> 
 * 〈〉
 *
 * @author ITryagain
 * @create 2020/6/9
 * @since 1.0.0
 */

public class DaytimeServer {

    private final static int PORT = 8000;

    public static void main(String[] args){
        try {
            DatagramSocket datagramSocket = new DatagramSocket(PORT);
            System.out.println("服务器启动");
            while(true){
                DatagramPacket request = new DatagramPacket(new byte[1024], 1024);
                datagramSocket.receive(request);

                String daytime = new Date().toString();
                byte[] data = daytime.getBytes("US-ASCII");

                DatagramPacket response = new DatagramPacket(data, data.length, request.getAddress(), request.getPort());
                datagramSocket.send(response);
                System.out.println("客户端 " + request.getAddress() + ":" + request.getPort() + "于" + daytime + "发起请求");
            }
        } catch (java.io.IOException e) {
            e.printStackTrace();
        }
    }

}
