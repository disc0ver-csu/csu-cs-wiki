/**
 * Copyright (C), 2015-2020, XXX有限公司
 * FileName: EchoClient
 * Author:   ITryagain
 * Date:     2020/6/10 15:32
 * Description:
 * History:
 * <author>          <time>          <version>          <desc>
 * 作者姓名           修改时间           版本号              描述
 */
package 实验三.echo.data.client;

import javax.xml.crypto.Data;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.util.Scanner;

/**
 * 〈一句话功能简述〉<br> 
 * 〈〉
 *
 * @author ITryagain
 * @create 2020/6/10
 * @since 1.0.0
 */

public class EchoClient {

    private final static int PORT = 8000;
    private final static String HOST = "localhost";

    public static void main(String[] args){
        try {
            DatagramSocket datagramSocket = new DatagramSocket();
            Scanner scanner = new Scanner(System.in);
            scanner.useDelimiter("\n");
            InetAddress host = InetAddress.getByName(HOST);
            System.out.println("包 echo 程序客户端，请输入命令，输入 #exit 退出");
            while(scanner.hasNext()){
                String str = scanner.next();
                System.out.println("输入：" + str);
                if(!str.equals("#exit")){
                    byte[] bytes = str.getBytes();
                    int len = bytes.length;
                    DatagramPacket request = new DatagramPacket(bytes, len, host, PORT);
                    DatagramPacket response = new DatagramPacket(new byte[len], len);

                    datagramSocket.send(request);
                    datagramSocket.receive(response);

                    String result = new String(response.getData(), 0, response.getLength());
                    System.out.println("服务器发来命令：" + result);
                }else{
                    System.out.println("退出");
                    break;
                }
            }
        } catch (java.io.IOException e) {
            e.printStackTrace();
        }
    }
}
