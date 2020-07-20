package fmsModel;

public class SuperBlock extends Block{
    //超级块
    private int root;   //根目录位置
    //空闲栈
    private int emptyUserBlock;	//空用户块
    private int emptyFileBlock;	//空文件块
    private int emptyIndexBlock;//空索引块

    public SuperBlock(int root, int emptyUserBlock, int emptyFileBlock, int emptyIndexBlock) {
        this.root = root;
        this.emptyUserBlock = emptyUserBlock;
        this.emptyFileBlock = emptyFileBlock;
        this.emptyIndexBlock = emptyIndexBlock;
    }

    public SuperBlock(){
    }

    public int getRoot() {
        return root;
    }

    public void setRoot(int root) {
        this.root = root;
    }

    public int getEmptyUserBlock() {
        return emptyUserBlock;
    }

    public void setEmptyUserBlock(int emptyUserBlock) {
        this.emptyUserBlock = emptyUserBlock;
    }

    public int getEmptyFileBlock() {
        return emptyFileBlock;
    }

    public void setEmptyFileBlock(int emptyFileBlock) {
        this.emptyFileBlock = emptyFileBlock;
    }

    public int getEmptyIndexBlock() {
        return emptyIndexBlock;
    }

    public void setEmptyIndexBlock(int emptyIndexBlock) {
        this.emptyIndexBlock = emptyIndexBlock;
    }

}
