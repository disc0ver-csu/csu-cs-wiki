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
package 实验三.echo.stream.server;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
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
    private static ServerSocket ss;

    public static void main(String[] args){
        try {
            ss = new ServerSocket(PORT);
            System.out.println("服务器启动成功");
        } catch (IOException e) {
            e.printStackTrace();
        }
        while(true) {
            Socket socket = null;
            try {
                socket = ss.accept();
            } catch (IOException e) {
                e.printStackTrace();
            }
            Socket finalSocket = socket;
            new Thread(() -> {
                try {
                    System.out.println("一个客户机加入了连接");
                    OutputStream os = finalSocket.getOutputStream();
                    InputStream is = finalSocket.getInputStream();
                    BufferedReader brd = new BufferedReader(new InputStreamReader(is));

                    while (true) {
                        String msg = brd.readLine();
                        if (!msg.startsWith("#exit")) {
                            msg += "\r\n";
                            os.write(msg.getBytes());
                            System.out.println("发送消息:" + msg);
                            os.flush();
                        } else {
                            System.out.println("一个客户机断开了连接");
                            brd.close();
                            is.close();
                            os.close();
                            finalSocket.close();
                            break;
                        }
                    }

                } catch (IOException e) {
                    e.printStackTrace();
                }

            }).start();
        }
    }

}
