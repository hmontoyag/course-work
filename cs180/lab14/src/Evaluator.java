import java.util.Stack;

/**
 * Created by hmontoya on 12/3/15.
 */
public class Evaluator {
    static double evalute(String rpn) {
        Stack stack = new Stack();
        String[] t = rpn.split(" ");
        for (int i = 0; i < t.length; i++) {
            if (t[i].equals("+") || t[i].equals("-") || t[i].equals("*") || t[i].equals("/")) {
                double v2 = Double.parseDouble(stack.pop().toString());
                double v1 = Double.parseDouble(stack.pop().toString());
                if (t[i].equals("+")) {
                    stack.push(v2 + v1);
                } else if (t[i].equals("-")) {
                    stack.push(v1 - v2);
                } else if (t[i].equals("*")) {
                    stack.push(v2 * v1);
                } else {
                    stack.push(v2 / v1);
                }
            } else {
                stack.push(t[i]);
            }
        }
        double e = Double.parseDouble(stack.pop().toString());
        return e;
    }

    public static void main(String[] args) {
        Evaluator e = new Evaluator();
        System.out.println(e.evalute("5 1 2.2 + 4 * + 3 -"));
    }
}


