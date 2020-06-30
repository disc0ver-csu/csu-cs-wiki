/**
 * Copyright (C), 2015-2020, XXX有限公司
 * FileName: PersonServer
 * Author:   ITryagain
 * Date:     2020/6/9 12:52
 * Description:
 * History:
 * <author>          <time>          <version>          <desc>
 * 作者姓名           修改时间           版本号              描述
 */
package 实验四.实验四_RMI.server;

import 实验四.实验四_RMI.Person;

/**
 * 〈一句话功能简述〉<br> 
 * 〈〉
 *
 * @author ITryagain
 * @create 2020/6/9
 * @since 1.0.0
 */

public class PersonServer implements Person {

    private int age;
    private String name;

    public PersonServer(String name, int age){
        this.age = age;
        this.name = name;
    }

    @Override
    public int getAge() throws Throwable {
        return this.age;
    }

    @Override
    public String getName() throws Throwable {
        return this.name;
    }

    public static void main(String[] args){
        PersonServer personServer = new PersonServer("lmw", 20);
        PersonSkeleton skeleton = new PersonSkeleton(personServer);
        skeleton.start();
    }

}
