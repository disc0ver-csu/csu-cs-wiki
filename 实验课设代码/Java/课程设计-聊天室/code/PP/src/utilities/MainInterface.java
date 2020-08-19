package utilities;

import javax.swing.*;
import java.awt.event.ComponentAdapter;

public class MainInterface {
    public static void main(String[] args) {
        JFrame frame = new JFrame("MainInterface");
        frame.setContentPane(new MainInterface().Container);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.pack();
        frame.setSize(200, 400);
        frame.setVisible(true);
    }

    private JPanel Container;
    private JList SessionList;

}
