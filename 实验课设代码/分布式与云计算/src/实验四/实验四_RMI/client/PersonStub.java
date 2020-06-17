/**
 * Copyright (C), 2015-2020, XXX有限公司
 * FileName: PersonStub
 * Author:   ITryagain
 * Date:     2020/6/9 11:31
 * Description:
 * History:
 * <author>          <time>          <version>          <desc>
 * 作者姓名           修改时间           版本号              描述
 */
package 实验四.实验四_RMI.client;

import 实验四.实验四_RMI.Person;

import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;

/**
 * 〈一句话功能简述〉<br> 
 * 〈〉
 *
 * @author ITryagain
 * @create 2020/6/9
 * @since 1.0.0
 */

public class PersonStub implements Person {

    private Socket socket;
    private ObjectOutputStream oos;
    private ObjectInputStream ois;

    public PersonStub()throws Throwable{
        this.socket = new Socket("localhost", 8000);
        this.oos = new ObjectOutputStream(this.socket.getOutputStream());
        this.ois = new ObjectInputStream((this.socket.getInputStream()));
    }

    @Override
    public int getAge() throws Throwable {
        this.oos.writeObject("age");
        this.oos.flush();
        return this.ois.readInt();
    }

    @Override
    public String getName() throws Throwable {
        this.oos.writeObject("name");
        this.oos.flush();
        return (String)this.ois.readObject();
    }
}
