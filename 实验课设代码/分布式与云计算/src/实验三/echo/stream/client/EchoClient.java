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
package 实验三.echo.stream.client;

import java.io.*;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.Socket;
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
            Socket socket = new Socket(HOST, PORT);
            Scanner scanner = new Scanner(System.in);
            scanner.useDelimiter("\n");
            System.out.println("流 echo 程序客户端，请输入命令，输入 #exit 退出");
            OutputStream os = socket.getOutputStream();
            InputStream is = socket.getInputStream();
            BufferedReader brd = new BufferedReader(new InputStreamReader(is));
            while(scanner.hasNext()){
                String str = scanner.next();
                if(!str.equals("#exit")){
                    str =  str + "\r\n";
                    os.write(str.getBytes());
                    os.flush();

                    String response = brd.readLine();
                    System.out.println("服务器发来命令：" + response);
                }else {
                    str =  str + "\r\n";
                    os.write(str.getBytes());
                    os.flush();

                    os.close();
                    is.close();
                    brd.close();
                    socket.close();
                    System.out.println("退出");
                    break;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
}
