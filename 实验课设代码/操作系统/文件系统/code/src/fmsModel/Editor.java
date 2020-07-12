package fmsModel;

import fmsService.AllService;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Editor extends JFrame implements ActionListener {
    private String originContent;
    private String fileName;

    private JPanel mainPanel;

    private JPanel editArea;
    private JTextArea jta;
    private JScrollPane jsp;

    private JPanel btnArea;
    private JButton saveBtn;
    private JButton cancelBtn;

    public Editor(String fileName, String content){
        originContent = content;
        this.fileName = fileName;

        mainPanel = new JPanel();
        editArea = new JPanel();
        btnArea = new JPanel();

        jta = new JTextArea();
        jta.setPreferredSize(new Dimension(390, 290));
        jta.setFont(new Font("微软雅黑", Font.PLAIN, 18));
        jta.setLineWrap(true);
        jsp = new JScrollPane(jta);
        jsp.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
        jsp.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED);
        jsp.setPreferredSize(new Dimension(400, 300));
        editArea.add(jsp, BorderLayout.CENTER);
        editArea.setPreferredSize(new Dimension(410, 310));

        saveBtn = new JButton("保存");
        cancelBtn = new JButton("还原");
        saveBtn.setPreferredSize(new Dimension(100, 40));
        cancelBtn.setPreferredSize(new Dimension(100, 40));
        btnArea = new JPanel();
        btnArea.add(saveBtn, BorderLayout.WEST);
        btnArea.add(cancelBtn, BorderLayout.EAST);
        btnArea.setPreferredSize(new Dimension(390, 50));

        setSize(430, 390);
        add(editArea, BorderLayout.NORTH);
        add(btnArea, BorderLayout.SOUTH);

        setTitle(fileName);
        jta.setText(content);
        saveBtn.addActionListener(this);
        cancelBtn.addActionListener(this);

        setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e){
        if(e.getSource()==this.saveBtn) {
            String content = jta.getText();
            try {
                AllService.overwrite(fileName, content);
                originContent = content;
            }catch (Exception e1){
                JOptionPane.showMessageDialog(null, "没有修改权限！", "错误！", JOptionPane.ERROR_MESSAGE);
            }
        }else if(e.getSource()==cancelBtn) {
            jta.setText(originContent);
        }
    }


    public static void main(String[] args){
        Editor e = new Editor("Test","Contentasdashkdjsahdksabdksbdsalhbdaskhdbak");
    }
}
