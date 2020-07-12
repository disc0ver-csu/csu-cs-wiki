package fmsModel;

public class User {
    //用来存储用户信息的块
    private String userName; //用户名称，长度<20
    private int mod; //权限
    private int inode; //用户根目录i节点

    public User() {
    }

    public User(String userName) {
        this.userName = userName;
    }

    public User(String userName, int mod, int inode) {
        this.userName = userName;
        this.mod = mod;
        this.inode = inode;
    }

    public String getUserName() {
        return userName;
    }

    public void setUserName(String userName) {
        this.userName = userName;
    }

    public int getMod() {
        return mod;
    }

    public void setMod(int mod) {
        this.mod = mod;
    }

    public int getInode() {
        return inode;
    }

    public void setInode(int inode) {
        this.inode = inode;
    }
}
