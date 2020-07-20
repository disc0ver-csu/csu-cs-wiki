package fmsModel;

import fmsService.DirService;
import fmsService.FileService;

public class HostHolder {
    /*
     * 当前用户
     */
    private static ThreadLocal<User> users=new ThreadLocal<>();
    private static ThreadLocal<IndexNode> CurDirs=new ThreadLocal<>();

    public static IndexNode getCurDir() {
        return CurDirs.get();
    }

    public static void setCurDir(IndexNode curDir) {
        CurDirs.set(curDir);
        DirService.curDir = curDir;
    }

    public static User getUser(){
        return users.get();
    }
    public static void setUser(User user){
        users.set(user);
        FileService.user = user.getUserName();
        DirService.user = user.getUserName();
    }
    public static void clearUser(){
        users.remove();
    }
    public static void clearCurDir(){
        CurDirs.remove();
    }
}
