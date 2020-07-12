import fmsModel.fmsInterface;

import java.io.IOException;

public class main2_with_frame {
    public static void main(String[] args) throws IOException {
        /**
         * 带界面的文件管理系统。
         * @param userName 用户名，管理员为"root"，其他用户自定义（若之前没有此用户，登录时会自动注册）。
         *                 管理员有最高权限，可以修改所有用户文件，普通用户只能修改自己创建的文件。
         *                 启动时默认读取上一次退出时的磁盘信息。
         *                 注：退出时点界面右上角的×，不要在IDE中强行停止进程，否则下次打开时会发生错误。
         */
        String userName = "root";
        fmsInterface interf1 = new fmsInterface(userName);
        interf1.showInterface();
    }
}
