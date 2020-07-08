package fmsModel;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class Permissions {
    private int mode = 0;
    private String userName;

    private boolean execute = false;//执行权限，x，1
    private final int x = (int) Math.pow(2, 0);

    private boolean write = false;//写权限，w，2
    private final int w = (int) Math.pow(2, 1);

    private boolean read = false;//读权限，r，4
    private final int r = (int) Math.pow(2, 2);

    /**
     * 输入int类型权限值，修改执行、写入、读取权限
     * 如7，则三个权限都有，0则都没有
     *
     * @param mode 权限值
     * @return 状态码 0正常，1错误
     */
    public int chmod(int mode) {
        this.mode = mode;
        if (!(mode >= 0 && mode <= 7)) {
            System.out.println("chmod权限值错误！");
            return 1;
        }
        if (mode >= r) {
            read = true;
            mode -= r;
        }
        else read=false;
        if (mode >= w) {
            write = true;
            mode -= w;
        }
        else write=false;
        if (mode >= x) {
            execute = true;
            mode -= x;
        }
        else execute=false;
        return 0;
    }

    /**
     * 修改某一权限后重新计算权限值的内部函数
     */
    private void recalculateMode(){
        int mod=0;
        if(execute) mod+=x;
        if(write) mod+=w;
        if(read) mod+=r;
        this.mode=mod;
    }

    public int getMode() {
        return mode;
    }

    public void setMode(int mode) {
        chmod(mode);
    }

    public boolean canExecute() {
        return execute;
    }

    public void setExecute(boolean execute) {
        this.execute = execute;
        recalculateMode();
    }

    public boolean canWrite() {
        return write;
    }

    public void setWrite(boolean write) {
        this.write = write;
        recalculateMode();
    }

    public boolean canRead() {
        return read;
    }

    public void setRead(boolean read) {
        this.read = read;
        recalculateMode();
    }

    public String getUserName() {
        return userName;
    }

    public void setUserName(String userName) {
        this.userName = userName;
    }

    public Permissions(boolean execute, boolean write, boolean read, String userName) {
        this.userName=userName;
        this.execute = execute;
        this.write = write;
        this.read = read;
        recalculateMode();
    }

    public Permissions(int mode, String userName) {
        this.userName=userName;
        chmod(mode);
    }

    public Permissions(boolean execute, boolean write, boolean read) {
        this.execute = execute;
        this.write = write;
        this.read = read;
        recalculateMode();
    }

    public Permissions(int mode) {
        chmod(mode);
    }

    public Permissions() {
    }
}
