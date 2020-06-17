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
package 实验三.daytime.stream.client;

import java.io.*;
import java.net.Socket;
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
        try {
            Socket s = new Socket(HOST, PORT);
            OutputStream os = s.getOutputStream();
            InputStream is = s.getInputStream();
            BufferedReader brd = new BufferedReader(new InputStreamReader(is));
            System.out.println("流 Socket daytime 程序，输入1获取时间，输入2退出");
            Scanner scanner = new Scanner(System.in);
            while(scanner.hasNext()){
                String str = scanner.next();
                if(str.equals("1")){
                    str = "time" + str + "\r\n";
                    os.write(str.getBytes());
                    os.flush();

                    String response = brd.readLine();
                    System.out.println("当前时间: " + response);
                }else if(str.equals("2")){
                    str = "end" + str + "\r\n";
                    os.write(str.getBytes());
                    os.flush();

                    os.close();
                    is.close();
                    brd.close();
                    s.close();
                    break;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
