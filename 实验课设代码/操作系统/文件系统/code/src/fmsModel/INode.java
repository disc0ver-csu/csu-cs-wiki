package fmsModel;

import com.alibaba.fastjson.JSON;

import java.util.ArrayList;
import java.util.List;

public class INode extends IndexNode {
    List<INode> dirSon=new ArrayList<>();
    List<INode> fileSon=new ArrayList<>();
    INode father;

    public void addDirSon(INode iNode){
        dirSon.add(iNode);
    }

    public void addFileSon(INode iNode){
        fileSon.add(iNode);
    }

    public List<INode> getDirSon() {
        return dirSon;
    }

    public List<INode> getFileSon() {
        return fileSon;
    }

    public INode getFather() {
        return father;
    }

    public void setFather(INode father) {
        this.father = father;
    }

    public String toString(){
        return getFileName()+" "+getId();
    }
}
