package fmsService;

import static fmsService.DirService.*;
import static fmsService.FileService.*;

public class AllService {
    public static int newDir(String input) {
        int status = mkdir(input);
        if (status == -1 || status==-2) {
            System.out.println("创建失败");
            return 0;
        }
        return 1;
    }

    public static int create(String input) {
        System.out.println("CreateTarget:"+input);
        int res = createFile(input);
        if (res == -1 || res == -2) {
            System.out.println("创建失败");
            return 0;
        }
        return 1;
    }

    public static String read(String input){
        String res = "*&*";
        if(canViewFile(input)){
            res = readFile(input);
        }
        return res;
    }

    public static int remove(String input) {
        System.out.println(input);
        if (canWriteFile(input)) {
            if (!deleteAllFile(input)) {
                System.out.println("删除文件失败");
                return 0;
            }
            else {
                System.out.println("删除成功");
                return 1;
            }
        }
        else return 0;
    }

    public static void overwrite(String file, String newContent) {
        if (canWriteFile(file)) {
            deleteOneFile(file);
            createFile(file);
            writeFile(file, newContent);
        }
    }
}
