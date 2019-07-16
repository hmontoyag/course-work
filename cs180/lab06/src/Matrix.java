/**
 * Created by hmontoya on 10/1/15.
 */
public class Matrix {
    public boolean isSymmetric( int[][] matrix) {
        if (matrix.length != matrix[0].length) {
            return false;
        }
        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix[0].length; j++) {
                if (matrix[i][j] != matrix[j][i]) {
                    return false;
                }
            }
        }
        return true;
    }
    public boolean isDiagonal(int[][] matrix) {
        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix[0].length; j++) {
                if (i != j) {
                    if (matrix[i][j] != 0) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
    public boolean isIdentity(int[][] matrix) {
        if (matrix.length != matrix[0].length) {
            return false;
        }
        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix[0].length; j++) {
                if (i != j) {
                    if (matrix[i][j] != 0) {
                        return false;
                    }
                } else {
                    if (matrix[i][j] != 1) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
    public boolean isUpperTriangular(int[][] matrix) {
        if (matrix.length != matrix[0].length) {
            return false;
        }
        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix[0].length; j++) {
                if (i > j) {
                    if (matrix[i][j] != 0) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
    public boolean isTriDiagonal(int[][] matrix) {
        if (matrix.length != matrix[0].length) {
            return false;
        }
        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix[0].length; j++) {
                if (Math.abs(i - j) != 1 && i != j) {
                    if (matrix[i][j] != 0) {
                        return false;
                    }
                }

            }
        }
        return true;
    }
}
