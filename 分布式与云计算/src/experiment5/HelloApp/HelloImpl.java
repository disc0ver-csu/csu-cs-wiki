/**
 * Copyright (C), 2015-2020, XXX有限公司
 * FileName: HelloImpl
 * Author:   ITryagain
 * Date:     2020/6/12 12:28
 * Description:
 * History:
 * <author>          <time>          <version>          <desc>
 * 作者姓名           修改时间           版本号              描述
 */
package experiment5.HelloApp;

/**
 * 〈一句话功能简述〉<br> 
 * 〈〉
 *
 * @author ITryagain
 * @create 2020/6/12
 * @since 1.0.0
 */

public class HelloImpl extends _HelloImplBase {

    public HelloImpl(){
        super();
    }

    @Override
    public String asyHello(String message) {
        System.out.println("It's server, client is invoking ...");
        System.out.println("Hello" + message);
        return message;
    }
}
