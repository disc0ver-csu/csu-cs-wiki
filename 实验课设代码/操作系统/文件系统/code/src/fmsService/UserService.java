package fmsService;

import fmsModel.HostHolder;
import fmsModel.User;
import com.alibaba.fastjson.JSON;

import static fmsConfig.MainConfig.*;
import static fmsService.BlockService.*;

public class UserService {
    /**
     * su xxx
     * @param userName 用户名
     * @return 成功与否
     */
    public static boolean login(String userName){
        // 先查看该userName是否存在
        User user=findUser(userName);
        if(user==null){//如果不存在这个用户，就返回false
            System.out.println("用户"+userName+"不存在！");
            return false;
        }
        User now=HostHolder.getUser();
        if(now.getUserName().equals("root")){//如果当前是root用户，直接就可以登录其他用户
            HostHolder.setUser(user);
            return true;
        }
        else{
            HostHolder.setUser(user);
            return true;
        }
    }

    /**
     * useradd xxx 注册用户
     * @param user 用户
     * @return 成功与否
     */
    public static boolean register(User user){
        User user2=findUser(user.getUserName());
        if(user2!=null){//如果已存在该用户名，注册失败
            System.out.println("用户"+user.getUserName()+"已存在！");
            return false;
        }
        int blockId=getUserBlock();
        if(blockId==-1){
            System.out.println("用户空间已满，无法创建新用户！");
            return false;
        }
        writeBlock(blockId,JSON.toJSONString(user));
        return true;
    }

    /**
     * 删除用户
     * @param userName 用户名
     * @return 成功与否
     */
    public static boolean deleteUser(String userName){
        if(userName.equals("root")){
            System.out.println("root用户无法被删除！");
            return false;
        }
        User user=HostHolder.getUser();
        if(!user.getUserName().equals("root")){
            System.out.println("非root用户无权删除其他用户！");
            return false;
        }
        for (int i = USERBLOCKSTART; i <USERBLOCKSTART+USERBLOCKNUM ; i++) {
            String userBlockContent=readBlock(i).trim();
            if(userBlockContent.length()==0) continue;
            user= JSON.parseObject(userBlockContent,User.class);
            if(user.getUserName().equals(userName)){
                recoverUserBlock(i);
                return true;
            }
        }
        return true;//没有这个用户也返回true
    }

    /**
     * 获取一个用户区的盘块以存储新用户的信息
     * @return
     */
    private static int getUserBlock(){
        for (int i = USERBLOCKSTART; i <USERBLOCKSTART+USERBLOCKNUM ; i++) {
            String userBlockContent = readBlock(i).trim();
            if (userBlockContent.length() == 0) return i;
        }
        return -1;
    }

    /**
     * 回收用户盘块
     * @param blockId
     */
    private static void recoverUserBlock(int blockId){
        formatBlock(blockId);
    }

    /**
     * 根据用户名获取User类型用户
     * @param userName
     * @return
     */
    private static User findUser(String userName){
        boolean userExist=false;
        User user=null;
        for (int i = USERBLOCKSTART; i <USERBLOCKSTART+USERBLOCKNUM ; i++) {//在用户块中循环找到要登录的用户
            String userBlockContent=readBlock(i).trim();
            if(userBlockContent.length()==0) continue;
            user= JSON.parseObject(userBlockContent,User.class);
            if(user.getUserName().equals(userName)){
                userExist=true;
                break;
            }
        }
        if(userExist) return user;
        else return null;
    }
}
