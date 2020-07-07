package utilities;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.PrintStream;

public class ChatWindow {
    private String fromUser;
    private String toUser;
    private PrintStream ps;

    private JPanel ChatWindow;
    private JTextArea ChatMsgArea;
    private JTextArea EditMsg;
    private JButton SengMsgBtn;
    private JPanel EditMsgArea;

    public ChatWindow(String fromUser, String toUser, PrintStream ps) {
        this.fromUser = fromUser;
        this.toUser = toUser;
        this.ps = ps;

        SengMsgBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String text = EditMsg.getText();
                Message msg = new Message(fromUser, toUser, text);
                try {
                    Operations.sendChat(msg, ps);
                } catch (Exception expt){expt.printStackTrace();}
            }
        });
    }
}
