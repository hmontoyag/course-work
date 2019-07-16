import java.util.Scanner;

/**
 * CS180 - Lab03
 * Created by hmontoya on 9/10/15.
 * Generates e-mail adress from full name
 * @author Hardy Montoya, hmontoya@purdue.edu, sec. 814
 *
 */
public class StringManipulator {
    public String makeUserName(String fullname) {
        if (fullname == null) return null;
        String lower = fullname.toLowerCase();
        String result = lower.charAt(0) + lower.substring(lower.indexOf(' ')+1);
        return result;
    }
/**
 * @param name user name returned by the makeUserNAme methord
 * @param domain Internet domain
 * @return e-mail
 *
 */
    public String makeEmail(String name, String domain) {
        String lowdomain = domain.toLowerCase();
        String username = name + "@" + lowdomain;
        return username;
    }

    public static void main(String[] args) {
        StringManipulator m = new StringManipulator();
        Scanner s = new Scanner(System.in);
        System.out.println("Enter the Full NAme of the person.  First Name followed by Last Name.");
        String nameInput = s.nextLine();
        System.out.println("Enter the domain.");
        String domainInput = s.nextLine();
        String userName = m.makeUserName(nameInput);
        String finalUsr = m.makeEmail(userName, domainInput);
        System.out.println("The user name for the person is: " + userName);
        System.out.println("The email id for the person is: " + finalUsr);



    }


}
