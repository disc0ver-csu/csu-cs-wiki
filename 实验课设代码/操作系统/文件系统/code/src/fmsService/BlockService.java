package fmsService;

import java.nio.MappedByteBuffer;

import static fmsConfig.MainConfig.BLOCKNUM;
import static fmsConfig.MainConfig.BLOCKSIZE;


public class BlockService {
    public static MappedByteBuffer disk= DiskService.disk;
    /**
     * 读盘块，输入盘块号，输出盘块中的内容
     * @param blockId 盘块号
     * @return content
     */
    public static String readBlock(int blockId){
        if(blockId>=BLOCKNUM){
            System.out.println("盘块号大于总盘块数错误。");
            System.exit(0);
        }
        int position=blockId*BLOCKSIZE;
        StringBuilder content=new StringBuilder();
        for (int i = position; i <position+BLOCKSIZE ; i++) {
            content.append((char)disk.get(i));
        }
        return content.toString();
    }

    /**
     * 写盘块，输入盘块号和输入内容，写入盘块
     * @param blockId 盘块号
     * @param content 写入内容
     * @return 状态码 0为正常写入；1为该空间已被占用，写入失败，需要覆盖写入；2为content长度大于块的大小。
     */
    public static int writeBlock(int blockId,String content){
        if(readBlock(blockId).trim().length()!=0)
            return 1;// block不为空，不能写入
        return overwriteBlock(blockId,content);
    }

    /**
     * 覆盖重写盘块
     * @param blockId 盘块号
     * @param content 覆盖写入内容
     * @return 状态码
     */
    public static int overwriteBlock(int blockId,String content){
        if(content.length()>BLOCKSIZE) return 2;// content比块大，不能写入
        formatBlock(blockId);
        int position=blockId*BLOCKSIZE;
        disk.position(position);
        for (int i = 0; i <content.length(); i++) {
            disk.put((byte)content.charAt(i));
        }
        return 0;
    }

    /**
     * 格式化盘块，将该盘块的所有内容清空
     * @param blockId 盘块号
     */
    public static void formatBlock(int blockId){
        int position=blockId*BLOCKSIZE;
        disk.position(position);
        for (int i = 0; i <BLOCKSIZE; i++) {
            disk.put((byte)' ');
        }
    }
}
