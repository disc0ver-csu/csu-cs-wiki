package fmsService;

import java.util.Stack;

import static fmsConfig.MainConfig.BLOCKNUM;
import static fmsConfig.MainConfig.DATABLOCKSTACKSIZE;
import static fmsService.DiskService.superBlock;
import static fmsService.BlockService.*;

public class DataService {
    private static Stack<Integer> blockStack;

    /**
     * 获取一个新的可以存数据的空盘块的id
     * @return new dataBlock id
     */
    public static int getDataBlock(){
        if(blockStack==null||blockStack.size()==0){//如果blockStack未初始化，则说明是重启后第一次调用本函数，要从超级块中获取盘块栈的信息。
            initDataBlockStack();
        }
        while(blockStack.size()==1){//如果栈里只有一个blockId了的话
            int status=addBlockToStack();//把这一个block里存的所有blockId都加到栈里
            if(status!=0) return BLOCKNUM-1;//如果addBlockToStack没有正常返回,getDataBlock返回BLOCKNUM-1
        }
        if(blockStack.size()>1) return blockStack.pop();
        else{
            return BLOCKNUM-1;
        }
    }

    /**
     * 回收盘块，将盘块清空，再将盘块号加到栈中，以供下次重新分配。
     * @param blockId 盘块号
     */
    public static void recoverDataBlock(int blockId){
        if(blockStack==null||blockStack.size()==0){//如果blockStack未初始化，则说明是重启后第一次调用本函数，要从超级块中获取盘块栈的信息。
            initDataBlockStack();
        }
        formatBlock(blockId);
        if(blockStack.size()>= DATABLOCKSTACKSIZE){
            removeBlockFromStack(blockId);
        }
        blockStack.push(blockId);
    }

    /**
     * 内部函数
     * 当栈里只有一个盘块时，这个盘块里应该存着新的一批盘块的id。本函数就是把那新一批盘块id加到栈中。
     * @return status(0代表正常，1代表未知错误，2代表磁盘已满)
     */
    private static int addBlockToStack(){
        if(blockStack==null||blockStack.size()!=1){
            System.out.println("addBlockToStack出现错误！");
            return 1;
        }
        int dataBlockId=blockStack.pop();
        if(dataBlockId==0){
            blockStack.push(dataBlockId);
            System.out.println("磁盘已满，无法继续存储！");
            return 2;
        }
        String[] dataBlockIds=readBlock(dataBlockId).trim().split(",");
        for (int i = dataBlockIds.length-1; i >=0 ; i--) {
            blockStack.push(Integer.parseInt(dataBlockIds[i]));
        }
        formatBlock(dataBlockId);
        blockStack.push(dataBlockId);
        return 0;//正常返回
    }

    /**
     * 内部函数
     * 当栈内盘块多于100个时，将100个盘块的id写到最后那个盘块中，栈中只保留最新要回收的盘块
     */
    private static void removeBlockFromStack(int blockId){
        StringBuilder dataBlockIds=new StringBuilder();
        for (int i = 0; i < DATABLOCKSTACKSIZE -1 ; i++) {
            dataBlockIds.append(blockStack.pop()+",");
        }
        dataBlockIds.append(blockStack.pop());
        writeBlock(blockId,dataBlockIds.toString());
    }

    /**
     * 关闭磁盘时保留栈信息到超级块中
     * @return blockId
     */
    public static int saveStack(){
        if(blockStack==null||blockStack.size()==0) return 0;
        int blockId=blockStack.pop();
        StringBuilder dataBlockIds=new StringBuilder();
        while(blockStack.size()>1) {
            dataBlockIds.append(blockStack.pop()+",");
        }
        if(blockStack.size()>0) dataBlockIds.append(blockStack.pop());
        if(writeBlock(blockId,dataBlockIds.toString())==0) return blockId;
        else{
            System.out.println("数据块需要覆盖写入！");
            return blockId;
        }
    }

    /**
     * 内部函数
     * 从超级块中获取盘块栈的信息
     */
    public static void initDataBlockStack(){
        blockStack=new Stack<Integer>();
        int firstDataBlock= superBlock.getEmptyFileBlock();
        blockStack.push(firstDataBlock);//将第一个块的数据push进去
    }
}
