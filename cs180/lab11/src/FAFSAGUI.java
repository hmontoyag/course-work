/**
 * Created by hmontoya on 11/5/15.
 */
import javax.swing.JOptionPane;
import java.awt.*;

public class FAFSAGUI {
    public static void main(String[] args) {
        do {

            JOptionPane.showMessageDialog(null, "Welcome to FAFSA!", "Title", JOptionPane.INFORMATION_MESSAGE);
            boolean isAcceptedStudent;
            boolean isSSregistered;
            boolean hasSSN;
            boolean hasValidResidency;
            int age;
            int creditHours;
            double studentIncome;
            double parentIncome;
            boolean isIndependent;
            String classStanding = "";

            if (JOptionPane.showOptionDialog(null, "Hava you been accepted into a degree or certificate program?", "Program Acceptance", JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, null, null, null) == JOptionPane.YES_OPTION) {
                isAcceptedStudent = true;
            } else {
                isAcceptedStudent = false;
            }

            if (JOptionPane.showOptionDialog(null, "Are you registered for the selective service?", "Selective Service", JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, null, null, null) == JOptionPane.YES_OPTION) {
                isSSregistered = true;
            } else {
                isSSregistered = false;
            }

            if (JOptionPane.showOptionDialog(null, "Do you have a social security number?", "Social Security Number", JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, null, null, null) == JOptionPane.YES_OPTION) {
                hasSSN = true;
            } else {
                hasSSN = false;
            }

            if (JOptionPane.showOptionDialog(null, "Do you have a valid residency?", "Residency Status", JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, null, null, null) == JOptionPane.YES_OPTION) {
                hasValidResidency = true;
            } else {
                hasValidResidency = false;
            }

            do {
                age = Integer.parseInt(JOptionPane.showInputDialog(null, "How old are you?", "Age", JOptionPane.QUESTION_MESSAGE));
                if (age < 0) {
                    JOptionPane.showMessageDialog(null, "Age cannot be a negative number", "Error: Age", JOptionPane.ERROR_MESSAGE);
                }
            } while (age < 0);

            do {
                creditHours = Integer.parseInt(JOptionPane.showInputDialog(null, "How many credits do you plan on taking?", "Credit Hours", JOptionPane.QUESTION_MESSAGE));
                if (creditHours < 1 || creditHours > 24) {
                    JOptionPane.showMessageDialog(null, "Credit hours must be between 1 and 24, inclusive", "Error: Credit Hours", JOptionPane.ERROR_MESSAGE);
                }
            } while (creditHours < 1 || creditHours > 24);

            do {
                studentIncome = Double.parseDouble(JOptionPane.showInputDialog(null, "What is your total yearly income?", "Student Income", JOptionPane.QUESTION_MESSAGE));
                if (studentIncome < 0) {
                    JOptionPane.showMessageDialog(null, "Income cannot be negative", "Error: Student Income", JOptionPane.ERROR_MESSAGE);
                }
            } while (studentIncome < 0);

            do {
                parentIncome = Double.parseDouble(JOptionPane.showInputDialog(null, "What is your parent's total yearly income?", "Parent Income", JOptionPane.QUESTION_MESSAGE));
                if (parentIncome < 0) {
                    JOptionPane.showMessageDialog(null, "Income cannot be negative", "Error: Parent Income", JOptionPane.ERROR_MESSAGE);
                }
            } while (parentIncome < 0);

            if (JOptionPane.showOptionDialog(null, "Are you a  dependent?", "Dependency", JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, null, null, null) == JOptionPane.YES_OPTION) {
                isIndependent = true;
            } else {
                isIndependent = false;
            }

            String[] options = {"Freshman", "Sophomore", "Junior", "Senior", "Graduate"};
            Object clStanding = JOptionPane.showInputDialog(null, "What is your current class standing?", "Class Standing", JOptionPane.PLAIN_MESSAGE, null, options, null);
            if (clStanding.toString().equalsIgnoreCase("Graduate")) {
                classStanding = "Graduate";
            } else {
                classStanding = "Undergraduate";
            }

            FAFSA a = new FAFSA(isAcceptedStudent, isSSregistered, hasSSN, hasValidResidency, isIndependent, age, creditHours, studentIncome, parentIncome, classStanding);

            double calculatedLoan = a.calcStaffordLoan();
            double calculatedGrant = a.calcFederalGrant();
            double calculatedWorkStudy = a.calcWorkStudy();
            double calculatedFedAid = a.calcFederalAidAmount();

            JOptionPane.showMessageDialog(null, "Loans: " + calculatedLoan + "\nGrants: " + calculatedGrant + "\nWorkStudy: " + calculatedWorkStudy + "\n ---------- \n\n Total: " + calculatedFedAid, "FAFSA Results", JOptionPane.INFORMATION_MESSAGE);

        } while (JOptionPane.showOptionDialog(null, "Would you like to complete another application?", "Continue", JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, null, null,null) == JOptionPane.YES_OPTION);











    }
}
