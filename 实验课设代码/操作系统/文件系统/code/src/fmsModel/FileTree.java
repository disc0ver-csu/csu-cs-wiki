package fmsModel;

import javax.swing.*;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;

import fmsModel.INode;
import fmsService.FileService;

public class FileTree extends JFrame{
	public JTree tree;
	public DefaultTreeModel newModel;
	public DefaultMutableTreeNode Node;

	public FileTree() {
		Node = traverseFolder(FileService.root);
		newModel = new DefaultTreeModel(Node);
		tree = new JTree(newModel);
	}

	public static DefaultMutableTreeNode traverseFolder(INode node) {
		if(FileService.root==null) FileService.getTree();
		DefaultMutableTreeNode r = new DefaultMutableTreeNode(node.getFileName());
		for(INode n:node.getFileSon()){
			DefaultMutableTreeNode temp=new DefaultMutableTreeNode(n.getFileName());
			r.add(temp);
		}
		for(INode n:node.getDirSon()){
			r.add(traverseFolder(n));
		}
		return r;
	}
}

