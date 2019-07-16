/**
 * Created by hmontoya on 9/24/15.
 */
public class MathTools {
    public static double absoluteValue(double n) {
        if (n >= 0) {
            return n;
        } else {
            return -n;
        }
    }
    public static double power(double base, int exponent) {
        double v = 1;
        if (exponent == 0) {
            return 1;
        } else if (exponent > 0) {
            for (int i = 0; i < exponent; i++) {
                v = v * base;
            }
            return v;
        } else {
            for (int i = 0; i < absoluteValue(exponent); i++) {
                v = v * base;
            }
            return 1/v;
        }
    }
    public static double nthRoot(double value, int root) {
        double original = value;
        if (value <= 0) {
            return 0;
        }
        if (root == 0) {
            return 0;
        } else if (root > 0) {
            value = value;
        } else {
            value = 1 / value;
        }
        double xk1;
        double tolerance = 0.000000001;
        double change;
        do {
            xk1 = (1 / (double)root) * ((root - 1) * value + original / (power(value, root - 1)));
            change = absoluteValue(xk1 - value);
            value = xk1;
        } while (change > tolerance);
        return xk1;
    }
    public static String scientificNotation(double n) {
        int exponent =0;
        if (absoluteValue(n) >= 1 && absoluteValue(n) < 10) {

        } else if (absoluteValue(n) <1) {
            do {
                n = n * 10;
                exponent = exponent - 1;
            } while (absoluteValue(n) < 1);

        } else {
            do {
                n = n * 0.1;
                exponent = exponent + 1;
            } while (absoluteValue(n) >= 10);
        }
        n = ((int)(n * 1000000)) / 1000000.0;
        return n + " x 10 ^ " + exponent;
    }
}
