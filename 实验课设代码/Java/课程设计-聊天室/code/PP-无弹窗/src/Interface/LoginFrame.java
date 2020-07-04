package Interface;

import javax.swing.*;
import javax.swing.border.Border;
import javax.swing.text.html.ImageView;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginFrame extends JFrame implements ActionListener {
    private Container container;
    private JPanel mainPanel;

    private JLabel img;
    private JPanel imgArea;

    private JPanel loginArea;
    private JPanel inputArea;

    private JPanel userNameArea;
    private JPanel passwordArea;
    //private JLabel userNameLabel;
    //private JLabel passwordLabel;

    private JTextField userNameInput;
    private JTextField passwordInput;
    private JPanel btnArea;
    private JButton loginBtn;
    private JButton signupBtn;
    private JLabel loginResult;

    public LoginFrame(){
        this.mainPanel = new JPanel();
        this.mainPanel.setBackground(Color.WHITE);

        this.img = new JLabel(new ImageIcon("img/loginBg.jpg"));
        this.imgArea = new JPanel();
        this.imgArea.setPreferredSize(new Dimension(420, 150));
        this.imgArea.add(this.img);

        this.loginArea = new JPanel();
        this.loginArea.setPreferredSize(new Dimension(225, 150));
        this.loginArea.setBackground(Color.WHITE);
        this.inputArea = new JPanel();
        this.inputArea.setPreferredSize(new Dimension(220, 85));
        this.inputArea.setBackground(Color.WHITE);

        this.userNameArea = new JPanel();
        this.userNameArea.setPreferredSize(new Dimension(210, 35));
        //this.userNameLabel = new JLabel("ÓÃ»§Ãû");
        //this.userNameLabel.setFont(new Font("Î¢ÈíÑÅºÚ",Font.BOLD, 15));
        //this.userNameLabel.setPreferredSize(new Dimension(50, 30));
        this.userNameInput = new JTextField();
        this.userNameInput.addFocusListener(new JTextFieldHintListener(this.userNameInput, "ÓÃ»§Ãû"));
        this.userNameInput.setPreferredSize(new Dimension(200, 30));
        this.userNameInput.setFont(new Font("ËÎÌå",Font.PLAIN, 15));
        this.userNameInput.setBorder(new RoundBorder(Color.BLACK));
        //this.userNameArea.add(this.userNameLabel, BorderLayout.WEST);
        this.userNameArea.add(this.userNameInput, BorderLayout.EAST);
        this.userNameArea.setBackground(Color.WHITE);

        this.passwordArea = new JPanel();
        this.passwordArea.setPreferredSize(new Dimension(210, 35));
        //this.passwordLabel = new JLabel("ÃÜÂë");
        //this.passwordLabel.setFont(new Font("Î¢ÈíÑÅºÚ",Font.BOLD, 15));
        //this.passwordLabel.setPreferredSize(new Dimension(50, 30));
        this.passwordInput = new JTextField();
        this.passwordInput.addFocusListener(new JTextFieldHintListener(this.passwordInput, "ÃÜÂë"));
        this.passwordInput.setPreferredSize(new Dimension(200,30));
        this.passwordInput.setFont(new Font("ËÎÌå",Font.PLAIN, 15));
        this.passwordInput.setBorder(new RoundBorder(Color.BLACK));
        //this.passwordArea.add(this.passwordLabel, BorderLayout.WEST);
        this.passwordArea.add(this.passwordInput, BorderLayout.EAST);
        this.passwordArea.setBackground(Color.WHITE);


        this.btnArea = new JPanel();
        this.btnArea.setPreferredSize(new Dimension(220, 35));
        this.btnArea.setBackground(Color.WHITE);

        this.loginBtn = new JButton("µÇÂ¼");
        this.loginBtn.setPreferredSize(new Dimension(90,30));
        this.loginBtn.setFont(new Font("Î¢ÈíÑÅºÚ",Font.BOLD, 14));
        //this.loginBtn.setBorder(new RoundBorder(new Color(51,153,255)));
        this.loginBtn.setBackground(new Color(51,153,255));
        this.loginBtn.setForeground(Color.WHITE);

        this.signupBtn = new JButton("×¢²á");
        this.signupBtn.setPreferredSize(new Dimension(90,30));
        this.signupBtn.setFont(new Font("Î¢ÈíÑÅºÚ",Font.BOLD, 14));
        //this.signupBtn.setBorder(new RoundBorder(new Color(51,153,255)));
        this.signupBtn.setBackground(new Color(51,153,255));
        this.signupBtn.setForeground(Color.WHITE);

        this.btnArea.add(loginBtn, BorderLayout.WEST);
        this.btnArea.add(signupBtn, BorderLayout.EAST);

        this.loginResult = new JLabel();
        this.loginResult.setFont(new Font("ËÎÌå",Font.PLAIN, 10));
        this.loginResult.setPreferredSize(new Dimension(140,30));

        this.inputArea.add(this.userNameArea);
        this.inputArea.add(this.passwordArea);
        this.loginArea.add(this.inputArea);
        this.loginArea.add(this.btnArea);
        this.loginArea.add(this.loginResult);

        this.mainPanel.add(this.imgArea);
        this.mainPanel.add(this.loginArea);

        this.loginBtn.addActionListener(this);
        this.signupBtn.addActionListener(this);
    }

    public void showInterface(){
        setSize(420, 330);
        setTitle("ÓÃ»§µÇÂ¼/×¢²á");

        this.mainPanel.setFocusable(true);
        this.container = this.getContentPane();
        this.container.add(this.mainPanel);
        this.container.setPreferredSize(new Dimension(420, 330));

        setResizable(false);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e){
        if(e.getSource()==this.loginBtn){
            String userName = this.userNameInput.getText();
            String password = this.passwordInput.getText();
            System.out.println(userName);
            System.out.println(password);
        }
        if(e.getSource()==this.signupBtn){
            String userName = this.userNameInput.getText();
            String password = this.passwordInput.getText();
            System.out.println(userName);
            System.out.println(password);
        }
    }

    public void setLoginResult(String result){
        this.loginResult.setText(result);
    }

    public void close(){
        setVisible(false);
    }

    public static void main(String[] args){
        LoginFrame lf = new LoginFrame();
        lf.showInterface();
    }
}
