/**
 * Created by hmontoya on 9/24/15.
 * perfmor basic math funtioncs
 * @author Hardy Montoya
 */
import java.util.Scanner;

public class MathToolsClient {
    public static void main(String[] args) {
        MathTools m = new MathTools();
        boolean exit = false;

        while(exit == false) {

            boolean valid;
            System.out.println("Select a number from the menu choices: ");
            System.out.println("1 - Absolute Value");
            System.out.println("2 - Power");
            System.out.println("3 - Nth Root");
            System.out.println("4 -  Scientific Notation");
            Scanner scan = new Scanner(System.in);
            String input = scan.nextLine();
            switch (input) {
                case "1":

                    System.out.println("Enter a number (double)");
                    double a = scan.nextDouble();
                    System.out.println(m.absoluteValue(a));
                    break;

                case "2":

                    System.out.println("Enter a base");
                    double b = scan.nextDouble();
                    System.out.println("Enter an exponent");
                    int c = scan.nextInt();
                    System.out.println(m.power(b, c));
                    break;

                case "3":

                    System.out.println("Enter a value");
                    double d = scan.nextDouble();
                    System.out.println("Enter a root");
                    int e = scan.nextInt();
                    System.out.println(m.nthRoot(d, e));
                    break;

                case "4":

                    System.out.println("Enter a number (double)");
                    double f = scan.nextDouble();
                    System.out.println(m.scientificNotation(f));
                    break;

                default:
                    System.out.println("Invalid option");
                    break;

            }
            System.out.println("Return to the menu? (yes/no)");
            String prompt = scan.nextLine();
            if(prompt.equalsIgnoreCase("yes")) {
                exit = false;
            } else {
                exit = true;
            }
        }
    }
}
