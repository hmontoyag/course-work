/**
 * Created by hmontoya on 8/27/15.
 * CS180 -Lab 01
 * Converts Fahrenheit to Celsius
 * @author Hardy Montoya, hmontoya@purdue.edu, section 814
 */

import java.util.Scanner;

public class Temperature {
    public static void main(String[]args) {
        double fahrenheit;
        double celsius;
        Scanner s=new Scanner(System.in);
        System.out.println("Enter the temperature in Fahrenheit: ");
        fahrenheit =s.nextDouble();
        celsius=((fahrenheit-32)*5)/9;
        System.out.println("Fahrenheit: " + fahrenheit);
        System.out.println("Celsius: " + celsius);


    }
}
