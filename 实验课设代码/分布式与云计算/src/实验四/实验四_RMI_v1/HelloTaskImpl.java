/**
 * Copyright (C), 2015-2020, XXX有限公司
 * FileName: HelloTaskImpl
 * Author:   ITryagain
 * Date:     2020/6/8 17:17
 * Description:
 * History:
 * <author>          <time>          <version>          <desc>
 * 作者姓名           修改时间           版本号              描述
 */
package 实验四.实验四_RMI_v1;

import java.io.Serializable;

/**
 * 〈一句话功能简述〉<br> 
 * 〈〉
 *
 * @author ITryagain
 * @create 2020/6/8
 * @since 1.0.0
 */

public class HelloTaskImpl implements HelloTask, Serializable {

    private static final long serialVersionUID = 1267074506158948214L;

    @Override
    public String execute() {
        return "Hello World!";
    }
}
