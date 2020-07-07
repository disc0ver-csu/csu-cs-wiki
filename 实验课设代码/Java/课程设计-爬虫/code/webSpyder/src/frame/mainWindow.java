package frame;

import crawler.Crawler;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.ArrayList;
import javax.swing.*;
import javax.swing.text.DefaultHighlighter;
import javax.swing.text.Highlighter;


public class mainWindow extends JFrame implements ActionListener {
    private Container container;
    private JPanel mainPanel;

    private JTextField urlInput;
    private JScrollPane urlInputScroll;
    private JPanel setUrlPanel;
    private JButton crawlUrlBtn;
    private JButton crawlUrlFileBtn;

    private result resultArea;

    public mainWindow(){
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        this.mainPanel = new JPanel();
        this.mainPanel.setPreferredSize(new Dimension(310, 105));
        this.mainPanel.setBackground(Color.WHITE);

        this.urlInput = new JTextField();
        this.urlInput.setFont(new Font("微软雅黑",Font.BOLD,18));
        this.urlInput.setForeground(new Color(43,187,216));
        this.urlInput.setBorder(BorderFactory.createEmptyBorder());
        this.urlInputScroll = new JScrollPane(this.urlInput);
        this.urlInputScroll.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
        this.urlInputScroll.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_NEVER);
        this.urlInputScroll.setPreferredSize(new Dimension(300, 50));
        this.urlInputScroll.setBorder(BorderFactory.createLineBorder(new Color(31,110,212)));

        this.setUrlPanel = new JPanel();
        this.setUrlPanel.setBackground(Color.WHITE);
        this.setUrlPanel.setPreferredSize(new Dimension(300, 45));
        this.crawlUrlBtn = new JButton("抓取输入网址");
        this.crawlUrlBtn.setBackground(new Color(252,210,113));//设置背景色
        this.crawlUrlBtn.setBorderPainted(false);
        this.crawlUrlBtn.setPreferredSize(new Dimension(145, 40));
        this.crawlUrlFileBtn = new JButton("选择网址文件");
        this.crawlUrlFileBtn.setBackground(new Color(247,141,63));//设置背景色
        this.crawlUrlFileBtn.setPreferredSize(new Dimension(145, 40));
        this.crawlUrlFileBtn.setBorderPainted(false);

        this.setUrlPanel.add(this.crawlUrlBtn,BorderLayout.WEST);
        this.setUrlPanel.add(this.crawlUrlFileBtn,BorderLayout.EAST);

        crawlUrlBtn.addActionListener(this);
        crawlUrlFileBtn.addActionListener(this);

    }

    public void showWindow(){
        setSize(310, 145);
        setTitle("网页爬虫");

        this.container = getContentPane();
        this.mainPanel.add(this.urlInputScroll, BorderLayout.NORTH);
        this.mainPanel.add(this.setUrlPanel, BorderLayout.SOUTH);
        this.container.add(this.mainPanel,BorderLayout.CENTER);

        setResizable(true);
        setLocationRelativeTo(null);
        setVisible(true);
    }

    private String readFile(){
        JFileChooser chooser = new JFileChooser(System.getProperty("user.dir"));
        chooser.setFileSelectionMode(JFileChooser.FILES_AND_DIRECTORIES);
        chooser.showDialog(new JLabel(), "选择");
        File file = chooser.getSelectedFile();
        String content = null;
        if(file!=null) {
            if (!file.exists() || file.isDirectory()) {
                JOptionPane.showMessageDialog(null, "文件不存在或不是一个单独文件", "错误", JOptionPane.ERROR_MESSAGE);
            }

            try {
                BufferedReader br = new BufferedReader(new FileReader(file));
                String tmp = br.readLine();
                content = tmp;
                while (tmp != null) {
                    tmp = br.readLine();
                    if(tmp!=null) content += tmp;
                }
            } catch (Exception e1) {
                e1.printStackTrace();
            }
        }
        return content;
    }

    @Override
    public void actionPerformed(ActionEvent e){
        Crawler c = null;
        ArrayList<String> content = new ArrayList<>();
        ArrayList<String> l = new ArrayList<>();

        if(e.getSource()==this.crawlUrlBtn) {
            String url = urlInput.getText();
            l.add(url);
            c = new Crawler(l,false);
            c.run();
            content = c.result;
            //content = c.crawl(l,false);
        }else if(e.getSource()==crawlUrlFileBtn) {
            String urls = readFile();
            this.urlInput.setText(urls);
            System.out.println(urls);

            String[]tmp = urls.split(",");
            for(int i=0; i<tmp.length; i++){
                l.add(tmp[i]);
            }
            c = new Crawler(l,true);
            c.run();
            content = c.result;
            //content = c.crawl(l,true);
        }
        String text = "\n";
        for(int i=0; i<content.size(); i++){
            text += c.parseContent(content.get(i)) + "\n\n";
        }
        this.resultArea = new result();
        this.resultArea.setText(text);
        this.resultArea.showWindow();
    }



    public static void main(String[] args){
        mainWindow c = new mainWindow();
        c.showWindow();
    }
}
