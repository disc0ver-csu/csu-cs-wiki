package fmsService;

import fmsModel.*;
import com.alibaba.fastjson.JSON;
import javafx.util.Pair;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

import static fmsConfig.MainConfig.*;
import static fmsService.BlockService.*;
import static fmsService.DataService.getDataBlock;
import static fmsService.FileService.*;
import static fmsService.INodeServie.getIndexBlock;

public class DirService {
    /**
     * 该目录是否可访问，包括目录存在性验证、权限验证
     * @param dir 目录地址
     * @return 是或否
     */
    public static IndexNode curDir;
    public static String user;

    public static boolean canViewDir(String dir){
        if(dir.equals("..")&&HostHolder.getCurDir().getId()!=INODEBLOCKSTART) return true;//非根目录的返回上一目录无条件允许
        INode node=dirLegality(dir);
        String now=HostHolder.getUser().getUserName();
        if(node==null) return false;
        // 权限是否符合
        // 如果当前用户是root或目录创建者，则肯定可以访问
        if(now.equals(node.getCreator())||now.equals("root")){
            return true;
        }
        // 否则查询目录的mode
        else if(node.getMode().size()==0){
            System.out.println("无权限访问该目录！");
            return false;
        }
        else{
            Permissions myPermissions=getDirPermissions(node);
            if(myPermissions==null){
                System.out.println("无权限访问该目录！");
                return false;
            }
            else{
                if(myPermissions.canRead()) return true;
                else {
                    System.out.println("无权限访问该目录！");
                    return false;
                }
            }
        }
    }

    /**
     * 目录是否允许写入（create、mkdir等）
     * @param dir 目录地址
     * @return 是否
     */
    public static boolean canWriteDir(String dir){
        INode node = dirLegality(dir);
        //String now=HostHolder.getUser().getUserName();
        String now = user;
        if(node==null) return false;
        // 权限是否符合
        // 如果当前用户是root或目录创建者，则肯定可以访问
        if(now.equals(node.getCreator())||now.equals("root")){
            return true;
        }
        // 否则查询目录的mode
        else if(node.getMode().size()==0){
            System.out.println("无权限写入该目录！");
            return false;
        }
        else{
            Permissions myPermissions=getDirPermissions(node);
            if(myPermissions==null){
                System.out.println("无权限写入该目录！");
                return false;
            }
            else{
                if(myPermissions.canRead()&&myPermissions.canWrite()) return true;
                else {
                    System.out.println("无权限写入该目录！");
                    return false;
                }
            }
        }
    }

    /**
     * 获取目录对当前用户的权限
     * @param node 内存节点
     * @return Permissions
     */
    public static Permissions getDirPermissions(INode node){
        Permissions myPermissions=null;
        String now=HostHolder.getUser().getUserName();
        for(Permissions p:node.getMode()){
            if(now.equals(p.getUserName())) myPermissions=p;
            break;
        }
        if(myPermissions==null){
            for(Permissions p:node.getMode()){
                if(p.getUserName()==null) myPermissions=p;
                break;
            }
        }
        return myPermissions;
    }

    /**
     * 输入地址合法性验证
     * @param dir
     * @return 合法地址的INode或null
     */
    private static INode dirLegality(String dir){
        INode node;
        if(dir.substring(0,1).equals("/")) node=findFileByFullName(dir);// 如果fileName是文件全名
        else node=findFileOnCur(dir);// 否则就在当前目录查询
        if(node==null){
            System.out.println("找不到该目录！");
            return null;
        }
        // 是否为目录
        if(node.getType()!=1){
            System.out.println("输入非目录，无法访问");
            return null;
        }
        return node;
    }

    /**
     * 根据某个I结点编号返回它的格式化信息
     * @param inodeId 内存节点id
     */
    public static void showInfo(int inodeId) {
        IndexNode inode = JSON.parseObject(readBlock(inodeId).trim(), IndexNode.class);
        String name = inode.getFileName();
        if(inode.getType() == 1){
            name = inode.getFileName()+"/";
        }
        System.out.println( "Name: "+name+"\t"+
                "Type: "+inode.getType()+"\t"+
                "Size: "+inode.getSize()+"\t"+
                "Creator: "+inode.getCreator()+"\t"+
                "CreateTime: "+inode.getChangeTime()+"\t"+
                "ChangeTime: "+inode.getChangeTime());
    }
    public static String getInfo(int inodeId) {
        IndexNode inode = JSON.parseObject(readBlock(inodeId).trim(), IndexNode.class);
        String name = inode.getFileName();
        if(inode.getType() == 1){
            name = inode.getFileName()+"/";
        }
        String res =  "名称: "+name+"\n"+
                "类型: "+inode.getType()+"\n"+
                "大小: "+inode.getSize()+"\n"+
                "起始块: "+inode.getIndirectData()+"\n"+
                "创建者: "+inode.getCreator()+"\n"+
                "创建时间: "+inode.getChangeTime()+"\n"+
                "修改时间: "+inode.getChangeTime();
        return res;
    }

    /**
     * 找一个目录的子目录
     * @param dirId
     * @param dirName
     * @return 找到了返回子目录的i节点号，否则返回-1
     */
    private static int findSubDir(int dirId, String dirName){
        //找一个目录的子目录
        IndexNode nowInode = JSON.parseObject(readBlock(dirId).trim(), IndexNode.class);
        DirBlock nowDir = JSON.parseObject(readBlock(nowInode.getIndirectData()).trim(), DirBlock.class);
        if(nowDir.getSonDirId().size() == 0){
            return -1; //没有
        }else{
            for(Integer x : nowDir.getSonDirId()){
                nowInode = JSON.parseObject(readBlock(x).trim(), IndexNode.class);
                nowDir = JSON.parseObject(readBlock(nowInode.getIndirectData()).trim(), DirBlock.class);
                if(nowDir.getDirName().equals(dirName)){
                    return nowInode.getId();
                }
            }
            //System.out.println(dirId+""+dirName);
            return -1; //没有
        }
    }

    /**
     * 创建一个目录
     * @param dirName 目录名字或者路径+目录名字
     * @return 返回目录的i结点号，创建失败返回BLOCKNUM-1s
     */
    public static int mkdir(String dirName) {
        //创建一个目录,返回的是该目录的i节点号(创建失败返回 - 1)

        String[] subdir = dirName.split("\\/");
        System.out.println("dirName:"+dirName);
        if(dirName.substring(dirName.length()-1,dirName.length()).equals("\\/")){
            dirName=dirName.substring(0,dirName.length()-1);
        }
        dirName = dirName.replaceFirst(subdir[subdir.length-1],"");
        System.out.println("dirName:"+dirName);
        if(changeDir(dirName) == null || (!canWriteDir(dirName) && !dirName.equals("/root/"))){
            return -1;
        }
        int curDir = changeDir(dirName).getId();
        dirName = subdir[subdir.length-1];

        //当前目录下已经有同名文件，返回-2
        if(findSubDir(curDir,dirName) != -1){
            return -2;
        }

        int inodeNum = getIndexBlock(); //申请一个空闲i节点
        int dirBlockNum = getDataBlock(); //申请一个空闲数据块
        //System.out.println("hhh "+inodeNum+" "+dirBlockNum);
        if(inodeNum == INODEBLOCKSTART+INODEBLOCKNUM-1 && dirBlockNum ==BLOCKNUM - 1 ){
            return -1;
        }

        //写入i节点信息
        IndexNode inode = new IndexNode();
        inode.setId(inodeNum);
        inode.setType(1);
        //mode是空的，表示只有root和自己能有全部权限
        inode.setUsed(true);
        inode.setSize(0); //空目录，若新建文件要在这里标记增加

        inode.setFileName(dirName);
        inode.setCreator(user); //HostHolder.getUser().getUserName()

        inode.setCreateTime(new Date());
        inode.setChangeTime(new Date());

        //inode.setOffset(); ??
        inode.setIndirectData(dirBlockNum); //指向自己，如果一个目录存不下，可能会扩增，indirect指向下一个

        //写入dirBlock信息
        DirBlock dirBlock = new DirBlock();
        dirBlock.setDirName(dirName);
        dirBlock.setIndexId(inodeNum);

        //System.out.println(getCurDir().getId());
        dirBlock.setFaDirId(curDir); //父目录设置为当前目录，如果在初始化root目录时需要设置为空

        //新建目录以下两项都是空
        //dirBlock.setSonDirId(BLOCKNUM - 1); //表示没有
        dirBlock.setNextDirId(BLOCKNUM - 1);   //表示没有


        //寻找父亲目录的子目录，添加到子目录(root还没有)
        IndexNode nowInode = JSON.parseObject(readBlock(curDir).trim(), IndexNode.class);
        DirBlock nowDir = JSON.parseObject(readBlock(nowInode.getIndirectData()).trim(), DirBlock.class);
        List<Integer> sonDir = nowDir.getSonDirId();
        sonDir.add(inodeNum);
        //System.out.println(JSON.toJSONString(sonDir));
        nowDir.setSonDirId(sonDir);
        //System.out.println(getCurDir().getIndirectData());
        overwriteBlock(nowInode.getIndirectData(),JSON.toJSONString(nowDir));



        dirBlock.setUsed(true);

        //写入磁盘
        //System.out.println(JSON.toJSONString(inode));
        writeBlock(inodeNum, JSON.toJSONString(inode));
        //System.out.println(inodeNum+" "+readBlock(inodeNum));
        writeBlock(dirBlockNum, JSON.toJSONString(dirBlock));
        // System.out.println(dirBlockNum+" "+readBlock(dirBlockNum));
        getTree();
        return inodeNum;
    }

    /**
     * 用来递归解析子目录
     * @param dirName
     * @return i节点号+目录名
     */

    private static Pair<Integer,String> cdAutomation(Pair<Integer,String> dirName){
        if(dirName.getValue().equals("")){
            return dirName;
        }
        if(dirName.getValue().substring(0,1).equals("/")){
            dirName = new Pair<>(dirName.getKey(),dirName.getValue().substring(1));
        }
        //System.out.println(dirName.getKey()+" "+dirName.getValue());
        if(dirName.getKey() == -1){
            return dirName; //出错了
        }else if(dirName.getValue().equals( "\\/")){
            return dirName; //找到了
        }else{
            String dir = dirName.getValue().trim();
            String subDir[] = dir.split("\\/");
            int find = findSubDir(dirName.getKey(),subDir[0]);
            if(find != -1){
                if(subDir.length == 1){

                    //就剩一个目录了，直接返回
                    return new Pair<Integer, String>(find,subDir[0]);
                }
                //找到子目录里面有，进入子目录
                String subDirName = dirName.getValue().replaceFirst(subDir[0]+"\\/","");
                return cdAutomation(new Pair<Integer, String>(find,subDirName.trim()));
            }else{
                if(subDir[0].equals(".")){
                    String subDirName = dirName.getValue().replaceFirst(subDir[0]+"\\/","");
                    return cdAutomation(new Pair<Integer, String>(dirName.getKey(),subDirName.trim()));
                }else if(subDir[0].equals("..")){
                    String subDirName = dirName.getValue().replaceFirst(subDir[0]+"\\/","");
                    IndexNode nowInode = JSON.parseObject(readBlock(dirName.getKey()).trim(), IndexNode.class);
                    DirBlock nowDir = JSON.parseObject(readBlock(nowInode.getIndirectData()).trim(), DirBlock.class);
                    return cdAutomation(new Pair<Integer, String>(nowDir.getFaDirId(),subDirName.trim()));
                }
                return new Pair<Integer, String>(find,dirName.getValue()); //子目录里面没有
            }
        }
    }

    /**
     * 解析路径
     * @param dirName 路径
     * @return i结点号
     */
    public static IndexNode changeDir(String dirName){
        //解析路径返回进入的目录的i节点号
        /*
        if(!dirName.matches("^[\\/](\\w+\\/?)+$")){
            return -1; //输入进来的路径不合法
        }
        */
        System.out.println(dirName);
        if(dirName.equals("")){
            return curDir;//getCurDir()
        }
        int cur = curDir.getId(); //默认从当前目录开始解析 getCurDir()
        String subDir[] = dirName.split("\\/");
        if(!subDir[0].equals(".") && !subDir[0].equals("..")) {
            if(!subDir[0].equals("root") &&(subDir.length > 1 &&!subDir[1].equals("root"))) {
                //System.out.println("fukc");
                if(dirName.substring(0,1).equals("/")){
                    dirName=dirName.replaceFirst("\\/","");
                }
                cur = curDir.getId();//getCurDir()
            }
            //System.out.println("Fuck!!!");
            dirName = dirName.replaceFirst("\\/root\\/","");
            //System.out.println(dirName);
        }else if(subDir[0].equals(".")){
            cur = curDir.getId();//getCurDir()
        }else{
            IndexNode nowInode = JSON.parseObject(readBlock(curDir.getId()).trim(), IndexNode.class);//getCurDir()
            DirBlock nowDir = JSON.parseObject(readBlock(nowInode.getIndirectData()).trim(), DirBlock.class);
            cur = nowDir.getFaDirId();
            dirName = dirName.replaceFirst("..","");
        }
        //System.out.println(cur+" "+dirName);
        Pair<Integer, String> res = cdAutomation(new Pair<Integer, String>(cur,dirName));
        if(res.getKey() == -1){
            return null; //没找到
        }else{
            return JSON.parseObject(readBlock(res.getKey()).trim(), IndexNode.class);
        }
    }

    /**
     * 输出路径下所有子目录和子文件的名字
     * @param dirName 路径
     * @return 一个存名字的list
     */
    public static List<String> listDir(String dirName){

        int cur = curDir.getId();//getCurDir()
        if(changeDir(dirName) != null)
            cur = changeDir(dirName).getId();

        //对应ls指令，列出所有子文件,存到一个List<String>里面
        //找一个目录的子目录
        List<String> result = new ArrayList<String>();
        IndexNode nowInode = JSON.parseObject(readBlock(cur).trim(), IndexNode.class);
        DirBlock nowDir = JSON.parseObject(readBlock(nowInode.getIndirectData()).trim(), DirBlock.class);
        //先读取所有目录输出
        for(Integer x : nowDir.getSonDirId()){
            nowInode = JSON.parseObject(readBlock(x).trim(), IndexNode.class);
            result.add(nowInode.getFileName()+"/");
        }
        //再读取所有子文件输出
        for(Integer x : nowDir.getSonDataId()){
            nowInode = JSON.parseObject(readBlock(x).trim(), IndexNode.class);
            result.add(nowInode.getFileName());
        }
        return result;
    }

    /**
     * 格式化输出路径下的文件信息
     * @param dirName 目录名
     */
    public static void ListInfo(String dirName){

        int cur = curDir.getId();//getCurDir()
        if(changeDir(dirName) != null)
            cur = changeDir(dirName).getId();

        List<String> result = new ArrayList<String>();
        IndexNode nowInode = JSON.parseObject(readBlock(cur).trim(), IndexNode.class);
        DirBlock nowDir = JSON.parseObject(readBlock(nowInode.getIndirectData()).trim(), DirBlock.class);
        //先读取所有目录输出
        for(Integer x : nowDir.getSonDirId()){
            showInfo(x);
        }
        //再读取所有子文件输出
        for(Integer x : nowDir.getSonDataId()){
            showInfo(x);
        }
    }
}