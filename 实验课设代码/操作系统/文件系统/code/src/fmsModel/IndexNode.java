package fmsModel;

import com.alibaba.fastjson.JSON;

import java.util.ArrayList;
import java.util.Date;
import java.util.List;

public class IndexNode extends Block{
    //i节点(索引)
    private int id; //索引号

    //文件说明信息
    private int type; //文件类型 1:目录 2:文件 3:硬链接 4:软链接
    private List<Permissions> mode=new ArrayList<>(); //权限
    private boolean used; //是否空闲
    private int size; //对应文件大小

    private String fileName; //文件名称/目录名称
    private String creator; //创建者

    private Date createTime; //创建日期
    private Date changeTime; //最后一次修改时间

    //索引地址
    private int offset; //存放磁盘块的直接地址（磁盘偏移量）
    private int indirectData; //指向数据块

    public IndexNode() {
    }

    public IndexNode(int id, int type, boolean used, int size, String creator,String fileName, Date createTime, Date changeTime, int offset,int indirectData) {
        this.id = id;
        this.type = type;
        this.used = used;
        this.size = size;
        this.creator = creator;
        this.fileName=fileName;
        this.createTime = createTime;
        this.changeTime = changeTime;
        this.offset = offset;
        this.indirectData=indirectData;
    }

    public IndexNode(INode inode){
        this.id = inode.getId();
        this.type = inode.getType();
        this.used = inode.isUsed();
        this.size = inode.getSize();
        this.creator = inode.getCreator();
        this.fileName=inode.getFileName();
        this.createTime = inode.getCreateTime();
        this.changeTime = inode.getChangeTime();
        this.offset = inode.getOffset();
        this.indirectData=inode.getIndirectData();
        this.mode=inode.getMode(); //权限
    }

    public void addMode(Permissions permissions){
        mode.add(permissions);
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getType() {
        return type;
    }

    public void setType(int type) {
        this.type = type;
    }

    public List<Permissions> getMode() {
        return mode;
    }

    public boolean isUsed() {
        return used;
    }

    public void setUsed(boolean used) {
        this.used = used;
    }

    public int getSize() {
        return size;
    }

    public void setSize(int size) {
        this.size = size;
    }

    public String getFileName() {
        return fileName;
    }

    public void setFileName(String fileName) {
        this.fileName = fileName;
    }

    public String getCreator() {
        return creator;
    }

    public void setCreator(String creator) {
        this.creator = creator;
    }

    public Date getCreateTime() {
        return createTime;
    }

    public void setCreateTime(Date createTime) {
        this.createTime = createTime;
    }

    public Date getChangeTime() {
        return changeTime;
    }

    public void setChangeTime(Date changeTime) {
        this.changeTime = changeTime;
    }

    public int getOffset() {
        return offset;
    }

    public void setOffset(int offset) {
        this.offset = offset;
    }

    public int getIndirectData() {
        return indirectData;
    }

    public void setIndirectData(int indirectData) {
        this.indirectData = indirectData;
    }


    public void print(){
        System.out.println(JSON.toJSONString(this));
    }


}
