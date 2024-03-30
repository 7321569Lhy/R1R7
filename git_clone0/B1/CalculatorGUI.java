import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class CalculatorGUI extends JFrame {
    private JTextField display;

    public CalculatorGUI() {
        // 设置窗口标题
        super("简易计算器");
        // 设置窗口大小
        setSize(300, 400);
        // 设置默认关闭操作
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        // 创建文本框用于显示输入和结果
        display = new JTextField();
        display.setEditable(false);

        // 创建按钮
        String[] buttonLabels = {
                "7", "8", "9", "/",
                "*", "4", "5", "6",
                "+", "-", "1", "2",
                "3", ".", "=", "0",
                "C", "←", "(", ")"
        };

        // 使用网格布局
        setLayout(new GridLayout(5, 4));

        // 添加按钮到窗口
        for (int i = 0; i < 20; i++) {
            JButton button = new JButton(buttonLabels[i]);
            button.addActionListener(new ButtonClickListener());
            add(button);
        }

        // 添加文本框到窗口
        add(display);

        // 设置窗口可见
        setVisible(true);
    }

    // 处理按钮点击事件的内部类
    private class ButtonClickListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            JButton source = (JButton) e.getSource();
            String buttonText = source.getText();

            // 处理按钮点击事件
            if (buttonText.equals("=")) {
                evaluateExpression();
            } else if (buttonText.equals("C")) {
                clearDisplay();
            } else if (buttonText.equals("←")) {
                backspace();
            } else {
                appendToDisplay(buttonText);
            }
        }
    }

    // 在文本框中追加文本
    private void appendToDisplay(String input) {
        String currentText = display.getText();
        display.setText(currentText + input);
    }

    // 清空文本框
    private void clearDisplay() {
        display.setText("");
    }

    // 实现退格功能
    private void backspace() {
        String currentText = display.getText();
        if (!currentText.isEmpty()) {
            display.setText(currentText.substring(0, currentText.length() - 1));
        }
    }

    // 计算表达式的值
    private void evaluateExpression() {
        String expression = display.getText();
        /*try {
            // 使用JavaScript引擎计算表达式的值
            ScriptEngineManager manager = new ScriptEngineManager();
            ScriptEngine engine = manager.getEngineByName("js");
            Object result = engine.eval(expression);

            // 将计算结果显示在文本框中
            display.setText(result.toString());
        } catch (ScriptException ex) {
            // 处理计算错误
            display.setText("错误");
        }*/
    }

    public static void main(String[] args) {
        // 在事件调度线程中创建并显示 GUI
        SwingUtilities.invokeLater(CalculatorGUI::new);
    }
}
