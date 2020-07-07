/**
 * Copyright (C), 2015-2020, XXX有限公司
 * FileName: ClientMain
 * Author:   ITryagain
 * Date:     2020/6/6 11:15
 * Description:
 * History:
 * <author>          <time>          <version>          <desc>
 * 作者姓名           修改时间           版本号              描述
 */
package 实验一.client;

import java.io.IOException;
import java.net.*;

/**
 * 〈一句话功能简述〉<br> 
 * 〈〉
 *
 * @author ITryagain
 * @create 2020/6/6
 * @since 1.0.0
 */

public class ClientMain {

    public static void main(String[] args){
        try {
            DatagramSocket datagramSocket = new DatagramSocket();

            byte[] buf = "Hello".getBytes();
            DatagramPacket datagramPacket = new DatagramPacket(buf, buf.length, InetAddress.getByName("localhost"), 8000);

            datagramSocket.send(datagramPacket);
            datagramSocket.close();
        } catch (SocketException e) {
            e.printStackTrace();
        } catch (UnknownHostException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
