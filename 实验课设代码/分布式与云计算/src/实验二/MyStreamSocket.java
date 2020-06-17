/**
 * Copyright (C), 2015-2020, XXX有限公司
 * FileName: MyStreamSocket
 * Author:   ITryagain
 * Date:     2020/6/6 11:39
 * Description:
 * History:
 * <author>          <time>          <version>          <desc>
 * 作者姓名           修改时间           版本号              描述
 */
package 实验二;

import java.io.*;
import java.net.Socket;
import java.net.SocketException;
import java.net.SocketImpl;
import java.util.Arrays;

/**
 * 〈一句话功能简述〉<br> 
 * 〈〉
 *
 * @author ITryagain
 * @create 2020/6/6
 * @since 1.0.0
 */

public class MyStreamSocket extends Socket {

    private ObjectOutputStream oos;
    private ObjectInputStream ois;
    private OutputStream os;
    private InputStream is;
    private BufferedReader brd;

    public MyStreamSocket(){
        super();
        System.out.println("构造 MyStreamSocket 1");
    }

    public MyStreamSocket(SocketImpl impl) throws SocketException {
        super(impl);
        System.out.println("构造 MyStreamSocket 2");
    }

    public MyStreamSocket(String host, int port) throws IOException {
        super(host, port);
        init();
        System.out.println("构造 MyStreamSocket 3");
    }

    public void sendMessage(String message) throws IOException {
        message += "\r\n";
        this.os.write(message.getBytes());
        this.os.flush();
        System.out.println("发送消息:" + message);
    }

    public String reciveMessage() throws IOException {
        String message = brd.readLine();
        return message;
    }

    public void init() throws IOException {
        this.os = getOutputStream();
        this.is = getInputStream();
        this.brd = new BufferedReader(new InputStreamReader(this.is));
    }

}
