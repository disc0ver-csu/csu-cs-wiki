/**
 * Copyright (C), 2015-2020, XXX有限公司
 * FileName: DaytimeClient
 * Author:   ITryagain
 * Date:     2020/6/9 17:25
 * Description:
 * History:
 * <author>          <time>          <version>          <desc>
 * 作者姓名           修改时间           版本号              描述
 */
package 实验三.daytime.data.client;

import java.io.IOException;
import java.net.*;
import java.util.Scanner;

/**
 * 〈一句话功能简述〉<br> 
 * 〈〉
 *
 * @author ITryagain
 * @create 2020/6/9
 * @since 1.0.0
 */

public class DaytimeClient {

    private final static int PORT = 8000;
    private final static String HOST = "localhost";

    public static void main(String[] args){
        System.out.println("包 Socket daytime 程序，输入1获取时间，输入2退出");
        Scanner s = new Scanner(System.in);
        try {
            DatagramSocket datagramSocket = new DatagramSocket();
            datagramSocket.setSoTimeout(5000);
            InetAddress host = InetAddress.getByName(HOST);
            while(s.hasNext()){
                String str = s.next();
                if(str.equals("1")){
                    DatagramPacket request = new DatagramPacket(new byte[1], 1, host, PORT);
                    DatagramPacket response = new DatagramPacket(new byte[1024], 1024);
                    datagramSocket.send(request);
                    datagramSocket.receive(response);
                    String result = new String(response.getData(), 0, response.getLength(), "US-ASCII");
                    System.out.println("当前时间: " + result);
                }else if(str.equals("2")){
                    System.out.println("退出");
                    break;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
