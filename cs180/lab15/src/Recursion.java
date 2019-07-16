import java.io.File;

/**
 * Created by hmontoya on 12/10/15.
 */
public class Recursion {

    public static int determinant (int[][] matrix) {
        if (matrix.length == 1 && matrix[0].length == 1) {
            return matrix[0][0];
        } else {
            int d = 0;

            for (int c = 0; c < matrix.length; c++) {

                int[][] a = new int[matrix.length - 1][matrix.length - 1];



                //fill b
                for (int i = 1; i < matrix.length; i++) {
                    int col = 0;
                    for (int j = 0; j <matrix.length; j++) {
                        if (j != c) {
                            a[i - 1][col] = matrix[i][j];
                            col++;
                        }
                    }
                }
                //remove column c


                int mult = matrix[0][c] * determinant(a);
                if (c%2 == 0) {
                    d = d + mult;
                } else {
                    d = d - mult;
                }
            }
            return d;
        }
    }


    public static int filecount(File f) {
        int sum = 0;

        if (f.isFile()) {

            return 1;

        } else if (f.isDirectory()) {

            File[] content = f.listFiles();

            for (int i = 0; i < content.length; i++) {


                    sum = sum + filecount(content[i]);

                
            }
        }
        return sum;
    }


}
