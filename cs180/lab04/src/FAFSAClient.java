/**
 * Created by hmontoya on 9/17/15.
 */
import java.util.Scanner;
public class FAFSAClient {
    public static void main(String[]args) {
        Scanner scan = new Scanner(System.in);
        System.out.println("Have you been accepted into a degree or certficate program?");
        String input1 = scan.nextLine();
        if (input1.equalsIgnoreCase("yes")) {
            boolean isAcceptedStudent = true;
        } else {
            boolean isAcceptedStudent = false;
        }
        System.out.println("Are you registered for the selective service?");
        String input2 = scan.nextLine();
        if (input2.equalsIgnoreCase("yes")) {
            boolean isSSregistered = true;
        } else {
            boolean isSSregistered = false;
        }
        System.out.println("Do you have a social security number?");
        String input3 = scan.nextLine();
        if (input3.equalsIgnoreCase("yes")) {
            boolean hasSSN = true;
        } else {
            boolean hasSSN = false;
        }
        System.out.println("Do you have a valid residency status?");
        String input4 = scan.nextLine();
        if (input4.equalsIgnoreCase("yes")) {
            boolean hasValidResidency = true;
        } else {
            boolean hasValidResidency = false;
        }
        System.out.println("How old are you?");
        int input5 = scan.nextInt();
        System.out.println("How many credit hours do you plan on taking?");
        int input6 = scan.nextInt();
        System.out.println("What is your total yearly income?");
        double input7 = scan.nextDouble();
        System.out.println("What is your parent's total yearly income?");
        double input8 = scan.nextDouble();
        System.out.println("Are you dependent?");
        String input9 = scan.nextLine();
        if (input9.equalsIgnoreCase("Yes")){
            boolean isDependent = true;
        } else {
            boolean isDependent = false;
        }
        System.out.println("undergraduate or graduate?");
        String input10 = scan.nextLine();
        if (input10.equalsIgnoreCase("undergraduate")) {
            input10 = "undergraduate";
        } else if (input10.equalsIgnoreCase("graduate")){
            input10 = "graduate";
        } else {
            input10 = null;
        }
//        FAFSA f = new FAFSA(input1,input2, input3,  )



    }
}
