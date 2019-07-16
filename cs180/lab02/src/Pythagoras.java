/**
 * CS180- Lab 02: Pythagoras
 * Computes the hypotenuse of a right triangle
 * @hmontoya Hardy Montoya, hmontoya@purdue.edu, Lab Sec814
 */
public class Pythagoras {
    public double getHypotenuse(int a, int b) {
        double result;
        result = Math.sqrt(a * a + b * b);
        return result;
    }
}
