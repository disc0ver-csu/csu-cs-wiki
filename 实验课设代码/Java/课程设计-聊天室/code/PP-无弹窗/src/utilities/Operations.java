package utilities;

import java.io.*;
import java.text.SimpleDateFormat;
import java.util.ArrayList;

public class Operations {

    //发送一条指令
    public static void sendMsg(String msg, PrintStream ps) throws IOException {
        ps.println(msg);
    }
    //发送1条信息+消息类型
    public static void sendMsg(String msgType, String msg, PrintStream ps) throws IOException {
        ps.println(msgType);
        ps.println(msg);
    }
    //发送2条信息+消息类型
    public static void sendMsg(String msgType, String msg1, String msg2, PrintStream ps) throws IOException {
        ps.println(msgType);
        ps.println(msg1);
        ps.println(msg2);
    }

    //发送私聊信息
    public static void sendChat(Message msg, PrintStream ps) throws IOException{
        try {
            ps.println("chatMsg");
            ps.println(msg.getUserFrom());
            ps.println(msg.getUserTo());
            ps.println(msg.getContent());
        } catch (Exception e) {System.out.println("发送聊天信息失败");e.printStackTrace();}
    }
    //接收私聊信息
    public static Message receiveChat(BufferedReader bf){
        try {
            String userFrom = bf.readLine();
            String userTo = bf.readLine();
            String message = bf.readLine();
            Message msg = new Message(userFrom, userTo, message);
            return msg;
        } catch (Exception e) {
            System.out.println("聊天消息接收错误！"+e.getMessage());
            return null;
        }
    }

    //发送群聊信息
    public static void sendGroupChat(ArrayList<String> clients, Message msg, PrintStream ps) throws IOException{
        try {
            for(int i=0; i<clients.size(); i++) {
                System.out.println("给"+clients.get(i)+"发送消息");
                ps.println("groupChatMsg");
                ps.println(msg.getGroupName());
                ps.println(msg.getUserFrom());
                ps.println(clients.get(i));
                ps.println(msg.getContent());
            }
        } catch (Exception e) {System.out.println("发送聊天信息失败");e.printStackTrace();}
    }

    //接收群聊消息
    public static Message receiveGroupChat(BufferedReader bf){
        try {
            String groupName = bf.readLine();
            String userFrom = bf.readLine();
            String userTo = bf.readLine();
            String message = bf.readLine();
            Message msg = new Message(groupName, userFrom, userTo, message);
            return msg;
        } catch (Exception e) {
            System.out.println("聊天消息接收错误！"+e.getMessage());
            return null;
        }
    }

    public static String getCurrentTime(){
        SimpleDateFormat dateFormat = new SimpleDateFormat("HH:mm:ss"); //"yyyy-MM-dd HH:mm:ss"
        String current = dateFormat.format(System.currentTimeMillis());
        return current;
    }

}
