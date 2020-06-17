/**
 * Copyright (C), 2015-2020, XXX有限公司
 * FileName: MyStreamServerSocket
 * Author:   ITryagain
 * Date:     2020/6/8 12:09
 * Description:
 * History:
 * <author>          <time>          <version>          <desc>
 * 作者姓名           修改时间           版本号              描述
 */
package 实验二;

import java.io.IOException;
import java.net.*;

/**
 * 〈一句话功能简述〉<br> 
 * 〈〉
 *
 * @author ITryagain
 * @create 2020/6/8
 * @since 1.0.0
 */

public class MyStreamServerSocket extends ServerSocket {


    public MyStreamServerSocket() throws IOException {
    }

    public MyStreamServerSocket(int port) throws IOException {
        super(port);
    }

    public MyStreamServerSocket(int port, int backlog) throws IOException {
        super(port, backlog);
    }

    public MyStreamServerSocket(int port, int backlog, InetAddress bindAddr) throws IOException {
        super(port, backlog, bindAddr);
    }

    @Override
    public Socket accept() throws IOException {
        if(isClosed())
            if (isClosed())
                throw new SocketException("Socket is closed");
        if (!isBound())
            throw new SocketException("Socket is not bound yet");
        final Socket s = new MyStreamSocket((SocketImpl) null);
        implAccept(s);
        return s;
    }
}
