/**
 * Copyright (C), 2015-2020, XXX有限公司
 * FileName: Client
 * Author:   ITryagain
 * Date:     2020/6/8 9:53
 * Description:
 * History:
 * <author>          <time>          <version>          <desc>
 * 作者姓名           修改时间           版本号              描述
 */
package 实验二;

import java.io.IOException;

/**
 * 〈一句话功能简述〉<br> 
 * 〈〉
 *
 * @author ITryagain
 * @create 2020/6/8
 * @since 1.0.0
 */

public class Client {

    public static void main(String[] args) throws IOException {
        MyStreamSocket socket = new MyStreamSocket("localhost", 8000);
        System.out.println("客户端收到信息：" + socket.reciveMessage());
        socket.sendMessage("Hello World");
    }

}
