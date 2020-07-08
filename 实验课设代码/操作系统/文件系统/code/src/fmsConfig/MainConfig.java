package fmsConfig;

/**
 * 一些最基础的配置
 */
public class MainConfig {
    public final static int BLOCKSIZE=512;//盘块大小
    public final static int BLOCKNUM=500;//盘块数量
    public final static int DISKSIZE=BLOCKNUM*BLOCKSIZE;//盘块大小乘盘块数量就是磁盘大小

    public final static int SUPERBLOCKNUM=1;//超级块数量
    public final static int SUPERBLOCKSTART=0;//第一个超级块的物理地址（盘块id）

    public final static int INODEBLOCKNUM=64;//用来存放i节点的盘块的数量
    public final static int INODEBLOCKSTART=SUPERBLOCKSTART+SUPERBLOCKNUM;//存i节点的第一个盘块的id

    public final static int USERBLOCKNUM=10;//存放用户信息的盘块数量
    public final static int USERBLOCKSTART=INODEBLOCKSTART+INODEBLOCKNUM;//存放用户信息的第一个盘块的id

    public final static int DATABLOCKNUM=BLOCKNUM-SUPERBLOCKNUM-INODEBLOCKNUM-USERBLOCKNUM;//剩下的都是数据块
    public final static int DATABLOCKSTART =USERBLOCKNUM+USERBLOCKSTART;//数据区的第一个盘块的id

    public final static int DATABLOCKSTACKSIZE =100;//成组链接法时数据块栈的容量
    public final static int INODEBLOCKSTACKSIZE =64;//成组链接法时索引块栈的容量

}
