package utilities;

import java.util.*;
import java.io.*;

/*
 * 存储用户聊天记录
 * */

public class GroupChatHistory implements Serializable {
    public String groupName;
    public String thisUser;
    private ArrayList<Message> history;

    public GroupChatHistory(String thisUser, String groupName) {
        this.groupName = groupName;
        this.thisUser = thisUser;
        this.history = new ArrayList<Message>();
    }

    public void addMessage(Message msg) {this.history.add(msg);}

    public int getSize(){return this.history.size();}

    public Message getMessage(int index){return this.history.get(index);}

    public ArrayList<Message> getHistory() {return this.history;}

    public static GroupChatHistory readHistory(String thisUser,String groupName){
        //从本地文件读取聊天记录
        File file = new File("ChatHistory/"+thisUser+"/"+groupName+".dat");
        if(!file.exists()){
            GroupChatHistory history = new GroupChatHistory(thisUser,groupName);
            history.saveHistory();
            return history;
        }
        FileInputStream in;
        try {
            in = new FileInputStream(file);
            ObjectInputStream objIn = new ObjectInputStream(in);
            GroupChatHistory history = null;
            history = (GroupChatHistory)objIn.readObject();
            objIn.close();
            //System.out.println("Read chat history success!");
            return history;
        } catch (Exception e) {
            System.out.println("Read group chat history failed");
            e.printStackTrace();
            return null;
        }
    }

    public void saveHistory() {
        //存储聊天记录到本地
        File file = new File("ChatHistory");
        if(!file.exists()) file.mkdir();
        file = new File("ChatHistory/"+this.thisUser);
        if(!file.exists()) file.mkdir();
        file =new File("ChatHistory/"+this.thisUser+"/"+groupName+".dat");

        FileOutputStream out;
        try {
            out = new FileOutputStream(file);
            ObjectOutputStream objOut = new ObjectOutputStream(out);
            objOut.writeObject(this);
            objOut.flush();
            objOut.close();
            //System.out.println("Write chat history success!");
        } catch (IOException e) {
            System.out.println("Write chat history failed");
            e.printStackTrace();
        }
    }

    public static void refreshHistory(String thisUser, String groupName, Message msg){
        GroupChatHistory history = GroupChatHistory.readHistory(thisUser, groupName);
        history.addMessage(msg);
        history.saveHistory();
        System.out.println("更新历史记录成功");
    }
}

