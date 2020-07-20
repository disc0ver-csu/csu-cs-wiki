package fmsService;

import java.util.Enumeration;
import java.util.Vector;
import javax.swing.JTree;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.TreeNode;
import javax.swing.tree.TreePath;

import fmsModel.FileTree;
import fmsModel.fmsInterface;

public class FileTreeService {
    public static void reloadTree(fmsInterface interf) {
        Vector<TreePath> v=new Vector<TreePath>();
        DefaultMutableTreeNode root = interf.fileTree.Node;
        DefaultMutableTreeNode user = getUserNode(interf);
        if(user == null) {
            root.add(new DefaultMutableTreeNode(interf.userName));
            user = getUserNode(interf);
        }
        getExpandNode(interf, user, v);
        root.remove(user);
        root.add(FileTree.traverseFolder(FileService.root));
        interf.fileTree.newModel.reload();

        int n=v.size();
        for(int i=0;i<n;i++){
            Object[] objArr = v.get(i).getPath();
            Vector<Object> vec=new Vector<Object>();
            int len = objArr.length;
            for(int j=0;j<len;j++){
                vec.add(objArr[j]);
            }
            expandNode(interf.fileTree.tree,root,vec);
        }
    }
    private static Vector<TreePath> getExpandNode(fmsInterface interf, TreeNode node,Vector<TreePath> v){
        if (node.getChildCount() > 0) {
            TreePath treePath=new TreePath(interf.fileTree.newModel.getPathToRoot(node));
            if(interf.fileTree.tree.isExpanded(treePath)) v.add(treePath);
            for (Enumeration e=node.children(); e.hasMoreElements(); ) {
                TreeNode n = (TreeNode)e.nextElement();
                getExpandNode(interf, n,v);
            }
        }
        return v;
    }
    private static void expandNode(JTree myTree, DefaultMutableTreeNode currNode, Vector<Object> vNode){
        if(currNode.getParent()==null){
            vNode.removeElementAt(0);
        }
        if(vNode.size() <= 0) return;

        int childCount = currNode.getChildCount();
        String strNode = vNode.elementAt(0).toString();
        DefaultMutableTreeNode child = null;
        boolean flag=false;
        for(int i=0; i<childCount; i++){
            child = (DefaultMutableTreeNode)currNode.getChildAt(i);
            if(strNode.equals(child.toString())){
                flag=true;
                break;
            }
        }
        if(child != null && flag){
            vNode.removeElementAt(0);
            if(vNode.size()>0){
                expandNode(myTree,child, vNode);
            }
            else{
                myTree.expandPath(new TreePath(child.getPath()));
            }
        }
    }
    public static DefaultMutableTreeNode getUserNode(fmsInterface interf) {
        DefaultMutableTreeNode root = interf.fileTree.Node;
        int childCount = root.getChildCount();
        DefaultMutableTreeNode user = null;
        for(int i=0; i<childCount; i++){
            user = (DefaultMutableTreeNode)root.getChildAt(i);
            if(interf.userName.equals(user.toString())){
                return user;
            }
        }
        return null;
    }
    private static void collapsePathTree(JTree tree, TreePath parent) {
        TreeNode node = (TreeNode) parent.getLastPathComponent();
        if (node.getChildCount() >= 0) {
            for (Enumeration<?> e = node.children(); e.hasMoreElements();) {
                TreeNode n = (TreeNode) e.nextElement();
                TreePath path = parent.pathByAddingChild(n);
                collapsePathTree(tree, path);
            }
        }
        tree.collapsePath(parent);
    }

    public static String getPath(TreeNode[] OriginPath) {
        String path = "/";
        for(int i=0; i<OriginPath.length; i++){
            if(i!=OriginPath.length-1){
                path += OriginPath[i] + "/";
            }else{
                path += OriginPath[i];
            }
        }
        return path;
    }
}