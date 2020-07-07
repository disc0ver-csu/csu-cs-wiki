/**
 * Copyright (C), 2015-2020, XXX有限公司
 * FileName: ServerMain
 * Author:   ITryagain
 * Date:     2020/6/6 11:08
 * Description:
 * History:
 * <author>          <time>          <version>          <desc>
 * 作者姓名           修改时间           版本号              描述
 */
package 实验一.server;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;

/**
 * 〈一句话功能简述〉<br> 
 * 〈〉
 *
 * @author ITryagain
 * @create 2020/6/6
 * @since 1.0.0
 */

public class ServerMain {

    public static void main(String[] args){
        try {
            DatagramSocket datagramSocket = new DatagramSocket(8000);

            byte[] buf = new byte[1024];
            DatagramPacket datagramPacket = new DatagramPacket(buf, buf.length);

            datagramSocket.receive(datagramPacket);
            System.out.println(datagramPacket.getAddress().getHostAddress() + ":" + datagramPacket.getPort());
            System.out.println(new String(datagramPacket.getData(), 0, datagramPacket.getLength()));

            datagramSocket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
