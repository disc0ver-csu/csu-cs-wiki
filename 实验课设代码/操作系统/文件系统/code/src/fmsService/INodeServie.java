package fmsService;

import java.util.Stack;

import static fmsConfig.MainConfig.*;
import static fmsService.BlockService.*;
import static fmsService.DiskService.superBlock;

public class INodeServie {
    private static Stack<Integer> blockStack;
    /**
     * 从索引区获取一个新的可以存索引节点的空盘块的id
     * @return new indexBlock id
     */
    public static int getIndexBlock(){
        if(blockStack==null||blockStack.size()==0){//如果blockStack未初始化，则说明是重启后第一次调用本函数，要从超级块中获取索引块栈的信息。
            initIndexBlockStack();
        }
        while(blockStack.size()==1){//如果栈里只有一个blockId了的话
            int status=addBlockToStack();//把这一个block里存的所有blockId都加到栈里
            if(status!=0) return INODEBLOCKSTART+INODEBLOCKNUM-1;//如果addBlockToStack没有正常返回,getIndexBlock返回最后一个索引块的id
        }
        if(blockStack.size()>1) return blockStack.pop();
        else{
            return INODEBLOCKSTART+INODEBLOCKNUM-1;
        }
    }

    /**
     * 回收一个索引块
     * @param blockId 索引块id
     */
    public static void recoverIndexBlock(int blockId){
        if(blockId>=INODEBLOCKSTART+INODEBLOCKNUM-1){
            System.out.println("盘块id所在区错误！");
            return;
        }
        if(blockStack==null||blockStack.size()==0){//如果blockStack未初始化，则说明是重启后第一次调用本函数，要从超级块中获取索引块栈的信息。
            initIndexBlockStack();
        }
        formatBlock(blockId);
        blockStack.push(blockId);
    }

    private static int addBlockToStack(){
        if(blockStack==null||blockStack.size()!=1){
            System.out.println("addBlockToStack出现错误！");
            return 1;
        }
        int indexBlockId=blockStack.pop();
        if(indexBlockId==0){
            blockStack.push(indexBlockId);
            System.out.println("索引块已满，无法继续存储！");
            return 2;
        }
        String[] indexBlockIds=readBlock(indexBlockId).trim().split(",");
        for (int i = indexBlockIds.length-1; i >=0 ; i--) {
            blockStack.push(Integer.parseInt(indexBlockIds[i]));
        }
        formatBlock(indexBlockId);
        blockStack.push(indexBlockId);
        return 0;//正常返回
    }

    /**
     * 关闭时保存索引块分配栈
     * @return 状态码
     */
    public static int saveStack(){
        if(blockStack==null||blockStack.size()==0) return 0;
        int blockId=blockStack.pop();
        StringBuilder indexBlockIds=new StringBuilder();
        while(blockStack.size()>1) {
            indexBlockIds.append(blockStack.pop()+",");
        }
        if(blockStack.size()>0) indexBlockIds.append(blockStack.pop());
        if(writeBlock(blockId,indexBlockIds.toString())==0) return blockId;
        else{
            System.out.println("索引块需要覆盖写入！");
            return blockId;
        }
    }

    /**
     * 初始化索引块分配栈
     */
    public static void initIndexBlockStack(){
        blockStack=new Stack<Integer>();
        int firstIndexBlock= superBlock.getEmptyIndexBlock();
        blockStack.push(firstIndexBlock);//将第一个索引块的数据push进去
    }
}
