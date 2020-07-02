/**
 * Copyright (C), 2015-2020, XXX有限公司
 * FileName: PersonClient
 * Author:   ITryagain
 * Date:     2020/6/9 12:59
 * Description:
 * History:
 * <author>          <time>          <version>          <desc>
 * 作者姓名           修改时间           版本号              描述
 */
package 实验四.实验四_RMI.client;

import 实验四.实验四_RMI.Person;

/**
 * 〈一句话功能简述〉<br> 
 * 〈〉
 *
 * @author ITryagain
 * @create 2020/6/9
 * @since 1.0.0
 */

public class PersonClient {

    public static void main(String[] args){
        try {
            Person person = new PersonStub();
            int age = person.getAge();
            String name = person.getName();
            System.out.println(name + " is " + age + " years old");
        } catch (Throwable throwable) {
            throwable.printStackTrace();
        }

    }

}
