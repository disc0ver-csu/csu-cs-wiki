package fmsModel;

import javax.swing.*;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.TreePath;

import java.awt.*;
import java.awt.event.*;
import java.io.IOException;

import static fmsService.DirService.*;
import static fmsService.DiskService.initDisk;
import static fmsService.DiskService.releaseDisk;
import static fmsService.FileService.printTree;
import static fmsService.UserService.login;
import static fmsService.UserService.register;

import fmsService.AllService;
import fmsService.FileService;
import fmsService.FileTreeService;

public class fmsInterface extends JFrame implements MouseListener, Action, TreeSelectionListener {
    private JPanel treePanel;

    public FileTree fileTree;

    private String currentPath;	//鼠标当前选择的文件地址
    public String userName;

    private JPopupMenu popMenu1;
    private JPopupMenu popMenu2;
    private JPopupMenu popMenu3;

    private JMenuItem attrItem;
    private JMenuItem delItem;

    private JMenuItem newDir;
    private JMenuItem newFile;

    private JMenuItem attrItem2;
    private JMenuItem delItem2;
    private JMenuItem newDir2;
    private JMenuItem newFile2;

    public fmsInterface(String user) throws IOException{
        initDisk(); //初始化磁盘
        printTree();
        this.fileTree = new FileTree();
        this.userName = user;
        try{
            User newUser=new User(user);
            register(newUser);
        }catch (Exception e){}
        login(user);
        System.out.println("Now:"+ HostHolder.getUser().getUserName());
    }


    public void showInterface(){
        treePanel = new JPanel();
        JScrollPane fileTree = new JScrollPane(this.fileTree.tree);
        fileTree.setPreferredSize(new Dimension(290, 350));
        treePanel.add(fileTree, BorderLayout.CENTER);
        treePanel.setPreferredSize(new Dimension(295,355));

        add(treePanel, BorderLayout.NORTH);
        setFileMenu();
        setSize(300, 400);
        setTitle("文件管理器");
        //System.out.println(FileService.user);
        
        //窗口通用设置
        //ImageIcon icon = new ImageIcon("icon/icon2.png");
        //setIconImage(icon.getImage());
        setResizable(true);
        setLocationRelativeTo(null);
        //setDefaultCloseOperation(EXIT_ON_CLOSE);
        addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e) {
                releaseDisk();
                System.exit(0);
            }
        });
        setVisible(true);
    }

    public void setFileMenu() {	//设置文件目录的显示
        fileTree.tree.setEditable(true);
        //设置右键菜单栏
        popMenu1 = new JPopupMenu();
        popMenu2 = new JPopupMenu();
        popMenu3 = new JPopupMenu();


        attrItem = new JMenuItem("属性");
        attrItem.addActionListener(this);
        delItem = new JMenuItem("删除");
        delItem.addActionListener(this);
        popMenu1.add(delItem);
        popMenu1.add(attrItem);

        newDir = new JMenuItem("新建文件夹");
        newDir.addActionListener(this);
        newFile = new JMenuItem("新建文件");
        newFile.addActionListener(this);
        popMenu2.add(newDir);
        popMenu2.add(newFile);

        attrItem2 = new JMenuItem("属性");
        attrItem2.addActionListener(this);
        delItem2 = new JMenuItem("删除");
        delItem2.addActionListener(this);
        newDir2 = new JMenuItem("新建文件夹");
        newDir2.addActionListener(this);
        newFile2 = new JMenuItem("新建文件");
        newFile2.addActionListener(this);
        popMenu3.add(delItem2);
        popMenu3.add(newDir2);
        popMenu3.add(newFile2);
        popMenu3.add(attrItem2);

        fileTree.tree.addTreeSelectionListener(this);
        fileTree.tree.addMouseListener(this);
    }

    //@Override
    public void actionPerformed(ActionEvent e) {
        DefaultMutableTreeNode node = (DefaultMutableTreeNode)fileTree.tree.getLastSelectedPathComponent();  //获得右键选中的节点
        if (e.getSource() == delItem || e.getSource() == delItem2) {
            if (node.isRoot()) {
                JOptionPane.showMessageDialog(null, "这是根目录文件夹！", "错误！", JOptionPane.ERROR_MESSAGE);
                return;
            }
            int choice = JOptionPane.showConfirmDialog(null, "确定删除该文件?", "确认",JOptionPane.YES_NO_OPTION);
            if (choice == 1) return;
            //删除文件
            int res = 0;
            try {
                res = AllService.remove(currentPath);
            } catch (Exception e1) {
                e1.printStackTrace();
                return;
            }
            if(res==1)
            //在视图中删除文件
                ((DefaultTreeModel) fileTree.tree.getModel()).removeNodeFromParent(node);
            else JOptionPane.showMessageDialog(null, "没有修改权限！", "错误！", JOptionPane.ERROR_MESSAGE);
        }
        else if (e.getSource() == newDir || e.getSource() == newDir2) {
            String name = JOptionPane.showInputDialog("输入新建文件夹名称:");
            if(name == null || name.equals("")) {
                return;
            }
            String tempP = currentPath + "/" + name;
            //创建文件夹
            int res = 0;
            try {
                res = AllService.newDir(tempP);
            } catch (Exception e1) {
                e1.printStackTrace();
            }
            if(res==1) {
                ((DefaultTreeModel) fileTree.tree.getModel()).insertNodeInto(new DefaultMutableTreeNode(name), node, node.getChildCount());
                fileTree.tree.expandPath(fileTree.tree.getSelectionPath());
            }
            else JOptionPane.showMessageDialog(null, "没有修改权限！", "错误！", JOptionPane.ERROR_MESSAGE);
        }
        else if (e.getSource() == newFile || e.getSource() == newFile2) {
            String name = JOptionPane.showInputDialog("输入新建文件名称:");
            if(name == null || name.equals("")) {
                return;
            }
            String tempP = currentPath + "/" + name;
            //创建文件
            int res = 0;
            try {
                res = AllService.create(tempP);
            } catch (Exception e1) {
                e1.printStackTrace();
            }
            if(res==1) {
                ((DefaultTreeModel) fileTree.tree.getModel()).insertNodeInto(new DefaultMutableTreeNode(name), node, node.getChildCount());
                fileTree.tree.expandPath(fileTree.tree.getSelectionPath());
            }
            else JOptionPane.showMessageDialog(null, "没有修改权限！", "错误！", JOptionPane.ERROR_MESSAGE);
        }
        else if(e.getSource() == attrItem || e.getSource() == attrItem2){
            int cur = curDir.getId();//getCurDir()
            System.out.println("Attr");
            if(changeDir(currentPath) != null)
                cur = changeDir(currentPath).getId();
            String info = getInfo(cur);
            JOptionPane.showMessageDialog(null, info, "属性", JOptionPane.PLAIN_MESSAGE);
        }
    }


    @Override
    public Object getValue(String key) {
        // TODO Auto-generated method stub
        return null;
    }
    @Override
    public void putValue(String key, Object value) {
        // TODO Auto-generated method stub

    }
    @Override
    public void mouseClicked(MouseEvent e) {
        try {
            if (e.getButton() == MouseEvent.BUTTON3) {
                TreePath path = fileTree.tree.getPathForLocation(e.getX(), e.getY());
                //获取当前节点的绝对地址
                DefaultMutableTreeNode node = (DefaultMutableTreeNode) fileTree.tree.getLastSelectedPathComponent();
                currentPath = FileTreeService.getPath(node.getPath());
                System.out.println("当前选中路径:"+currentPath);
                int type;
                if(currentPath.equals("/root")){
                    type = 2;
                }
                else {
                    type = FileService.fileType(currentPath);
                }
                String fileType;
                if(type==0) fileType = "File";
                else if(type==1) fileType = "EmptyDir";
                else fileType = "NotEmptyDir";

                if (fileType.equals("File")) { //右键单击文件
                    fileTree.tree.setSelectionPath(path);
                    this.popMenu1.show(fileTree.tree, e.getX(), e.getY());
                }
                else if (fileType.equals("NotEmptyDir")) { //右键单击非空文件夹
                    fileTree.tree.setSelectionPath(path);
                    this.popMenu3.show(fileTree.tree, e.getX(), e.getY());
                }
                else if (fileType.equals("EmptyDir")) { //右键单击空文件夹
                    fileTree.tree.setSelectionPath(path);
                    this.popMenu3.show(fileTree.tree, e.getX(), e.getY());
                }
            }
            else if(e.getClickCount() == 2){
                TreePath path = fileTree.tree.getPathForLocation(e.getX(), e.getY());
                //获取当前节点的绝对地址
                DefaultMutableTreeNode node = (DefaultMutableTreeNode) fileTree.tree.getLastSelectedPathComponent();
                currentPath = FileTreeService.getPath(node.getPath());
                System.out.println("当前选中路径:"+currentPath);
                int type;
                if(currentPath.equals("/root")){
                    type = 2;
                }
                else {
                    type = FileService.fileType(currentPath);
                }
                String fileType;
                if(type==0) fileType = "File";
                else if(type==1) fileType = "EmptyDir";
                else fileType = "NotEmptyDir";
                if (fileType.equals("File")) { //双击文件
                    fileTree.tree.setSelectionPath(path);
                    String content = AllService.read(currentPath);
                    if(content.equals("*&*"))
                        JOptionPane.showMessageDialog(null, "没有修改权限！", "错误！", JOptionPane.ERROR_MESSAGE);
                    else{
                        Editor edt = new Editor(currentPath, content);
                    }
                }

            }

        }
        catch (Exception exception) {exception.printStackTrace();}
    }
    @Override
    public void mousePressed(MouseEvent e) {
        // TODO Auto-generated method stub

    }
    @Override
    public void mouseReleased(MouseEvent e) {
        // TODO Auto-generated method stub

    }
    @Override
    public void mouseEntered(MouseEvent e) {
        // TODO Auto-generated method stub

    }
    @Override
    public void mouseExited(MouseEvent e) {
        // TODO Auto-generated method stub

    }
    @Override
    public void valueChanged(TreeSelectionEvent e) {
        // TODO Auto-generated method stub

    }

    public static void main(String[] args) throws IOException{
        fmsInterface interf = new fmsInterface("c");
        interf.showInterface();
    }

}
