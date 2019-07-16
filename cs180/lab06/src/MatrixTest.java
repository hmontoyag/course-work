import static org.junit.Assert.*;

/**
 * Created by hmontoya on 10/1/15.
 */
import static org.junit.Assert.*;
import org.junit.*;
import sun.security.x509.Extension;

public class MatrixTest {
    private Matrix m;

    @Before
    public void setUp() throws Exception {
        m = new Matrix();
    }

    //@org.junit.Test
    //Symmetric
    @Test(timeout = 100)
    public void testIsnotSymmetric() throws Exception {
        int[][] matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        boolean actual = m.isSymmetric(matrix);
        assertEquals("isSymmetric", false, actual);

    }

    @Test(timeout = 100)
    public void testIsSymmetric() throws Exception{
        int[][] matrix = {{1, 2, 2}, {2, 1, 2}, {2, 2, 1}};
        boolean actual = m.isSymmetric(matrix);
        assertEquals("isSymmetric", true, actual);
    }
    @Test(timeout = 100)
    public void testIsnotSymmetric2() throws Exception{
        int[][] matrix = {{1, 2, 2}, {2, 1, 2}, {3, 2, 0}};
        boolean actual = m.isSymmetric(matrix);
        assertEquals("isSymmetric", false, actual);
    }


    //Diagonal
    @Test(timeout = 100)
    public void testIsDiagonal() throws Exception{
        int[][] matrix = {{1, 0, 0}, {0, 1, 0}, {0, 0, 7}};
        boolean actual = m.isDiagonal(matrix);
        assertEquals("isSymmetric", true, actual);
    }
    @Test(timeout = 100)
    public void testIsDiagonal2() throws Exception{
        int[][] matrix = {{1, 0, 0}, {0, 1, 0}, {0, 0, 7}, {0, 0, 0}};
        boolean actual = m.isDiagonal(matrix);
        assertEquals("isSymmetric", true, actual);
    }
    @Test(timeout = 100)
    public void testIsnotDiagonal() throws Exception{
        int[][] matrix = {{1, 0, 0}, {0, 1, 0}, {0, 2, 7}};
        boolean actual = m.isDiagonal(matrix);
        assertEquals("isSymmetric", false, actual);
    }


    //Identity
    @Test(timeout = 100)
    public void testIsIdentity() throws Exception{
        int[][] matrix = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
        boolean actual = m.isIdentity(matrix);
        assertEquals("isSymmetric", true, actual);
    }
    @Test(timeout = 100)
    public void testIsNotIdentity() throws Exception{
        int[][] matrix = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {0,0,0}};
        boolean actual = m.isIdentity(matrix);
        assertEquals("isSymmetric", false, actual);
    }
    @Test(timeout = 100)
    public void testIsNotIdentity2() throws Exception{
        int[][] matrix = {{1, 1, 0}, {0, 1, 0}, {0, 0, 1}};
        boolean actual = m.isIdentity(matrix);
        assertEquals("isSymmetric", false, actual);
    }


    //Upper Triangular
    @Test(timeout = 100)
    public void testIsUpperTriangular2() throws Exception{
        int[][] matrix = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
        boolean actual = m.isUpperTriangular(matrix);
        assertEquals("isSymmetric", true, actual);
    }
    @Test(timeout = 100)
    public void testIsNotUpperTriangular() throws Exception{
        int[][] matrix = {{1, 1, 1}, {0, 1, 2}, {1, 0, 1}};
        boolean actual = m.isUpperTriangular(matrix);
        assertEquals("isSymmetric", false, actual);
    }
    @Test(timeout = 100)
    public void testIsUpperTriangular() throws Exception{
        int[][] matrix = {{1, 1, 1, 1}, {0, 1, 2, 3}, {0, 0, 1, 3}, {0, 0, 0, 1}};
        boolean actual = m.isUpperTriangular(matrix);
        assertEquals("isSymmetric", true, actual);
    }


    //TriDiagonal
    @Test(timeout = 100)
    public void testIsNotTriDiagonal() throws Exception{
        int[][] matrix = {{1, 1, 1}, {0, 1, 2}, {1, 0, 1}};
        boolean actual = m.isTriDiagonal(matrix);
        assertEquals("isSymmetric", false, actual);
    }
    @Test(timeout = 100)
    public void testIsTriDiagonal() throws Exception{
        int[][] matrix = {{1, 1, 0}, {0, 1, 2}, {0, 0, 1}};
        boolean actual = m.isTriDiagonal(matrix);
        assertEquals("isSymmetric", true, actual);
    }
    @Test(timeout = 100)
    public void testIsTriDiagonal2() throws Exception{
        int[][] matrix = {{1, 1, 0, 0}, {0, 1, 2, 0}, {0, 1, 0, 1}, {0, 0, 1, 3}};
        boolean actual = m.isTriDiagonal(matrix);
        assertEquals("isSymmetric", true, actual);
    }






}