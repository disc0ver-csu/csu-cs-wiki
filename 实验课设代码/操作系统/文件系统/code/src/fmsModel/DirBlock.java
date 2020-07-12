package fmsModel;

import java.util.ArrayList;
import java.util.List;

public class DirBlock extends Block {
    //目录文件
    private String dirName; //目录名
    private int indexId; //目录所指向的i节点号

    private int faDirId; //父亲目录id
    private List<Integer> sonDirId= new ArrayList<Integer>(); //儿子目录id
    private int nextDirId; //存不下了，下一个盘区

    private List<Integer> sonDataId= new ArrayList<Integer>(); //当前目录下存放的文件

    private boolean used=false; //是否正被使用

    public DirBlock(String dirName, int indexId,int faDirId) {
        super("DirBlock");
        this.dirName = dirName;
        this.indexId = indexId;
        this.faDirId = faDirId;
    }

    public void removeSon(int id){
        for (int i = 0; i <sonDataId.size() ; i++) {
            if(sonDataId.get(i)==id){
                sonDataId.remove(i);
                return;
            }
        }
        for (int i = 0; i <sonDirId.size() ; i++) {
            if(sonDirId.get(i)==id) {
                sonDirId.remove(i);
                return;
            }
        }
    }

    public DirBlock() {
        super("DirBlock");
    }

    public String getDirName() {
        return dirName;
    }

    public void setDirName(String dirName) {
        this.dirName = dirName;
    }

    public int getIndexId() {
        return indexId;
    }

    public void setIndexId(int indexId) {
        this.indexId = indexId;
    }

    public int getFaDirId() {
        return faDirId;
    }

    public void setFaDirId(int faDirId) {
        this.faDirId = faDirId;
    }

    public List<Integer> getSonDirId() {
        return sonDirId;
    }

    public void setSonDirId(List<Integer> sonDirId) {
        this.sonDirId = sonDirId;
    }

    public List<Integer> getSonDataId() {
        return sonDataId;
    }

    public void setSonDataId(List<Integer> sonDataId) {
        this.sonDataId = sonDataId;
    }

    public int getNextDirId() {
        return nextDirId;
    }

    public void setNextDirId(int nextDirId) {
        this.nextDirId = nextDirId;
    }

    public boolean isUsed() {
        return used;
    }

    public void setUsed(boolean used) {
        this.used = used;
    }
}
