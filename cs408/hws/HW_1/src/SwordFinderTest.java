
import org.junit.Test;
import org.junit.runners.Parameterized;

import static org.junit.Assert.assertEquals;

public class SwordFinderTest {
/*THIS 4 tests are for basic scenarios, the EVEN ones test cases where the sum of two friend's playtime yields an even average (X.0)
  the odd ones are for when the average is not an integer (X.5)
 */
    @Test
    public void testEvenNtoS_01(){
        SwordFinder sf = new SwordFinder();
        assertEquals(4,sf.operation("src/nsEvenS.txt"));
    }
    @Test
    public void testEvenStoN_02(){
        SwordFinder sf = new SwordFinder();
        assertEquals(4,sf.operation("src/sEvenNS.txt"));
    }

    @Test
    public void testOddNtoS_03(){
        SwordFinder sf = new SwordFinder();
        assertEquals(4,sf.operation("src/nsOddS.txt"));
    }
    @Test
    public void testOddStoN_04(){
        SwordFinder sf = new SwordFinder();
        assertEquals(4,sf.operation("src/sOddNS.txt"));
    }
/*The two 'lone' tests test for when theres only one friend'ss plaaytime, for NS and S respectively.*/
    @Test
    public void loneS(){
        SwordFinder sf = new SwordFinder();
        assertEquals(3,sf.operation("src/loneS.txt"));
    }
    @Test
    public void loneN(){
        SwordFinder sf = new SwordFinder();
        assertEquals(0,sf.operation("src/loneN.txt"));
    }

/*THE following two tests test the situation of finding a playtime NS bounded by S's, and viceversa. This also checks situations where an S is next to an NS, towards
both directions, considering both tests <-S NS S ->;  <-NS S NS->
*/
    @Test
    public void testBoundS_10(){
      SwordFinder sf = new SwordFinder();
      assertEquals(1,sf.operation("src/boundS.txt"));
    }
    @Test
    public void testBoundN_11(){
        SwordFinder sf = new SwordFinder();
        assertEquals(4,sf.operation("src/boundN.txt"));
    }

    /*The following tests were used in the building process, and are not particularly designed to cover any one case*/
    @Test
    public void test_0(){
        SwordFinder sf = new SwordFinder();
        assertEquals(4,sf.operation("src/test0.txt"));
    }
    @Test
    public void test_1(){
        SwordFinder sf = new SwordFinder();
        assertEquals(8,sf.operation("src/test1.txt"));
    }
    @Test
    public void test_2(){
        SwordFinder sf = new SwordFinder();
        assertEquals(18,sf.operation("src/test2.txt"));
    }
    @Test
    public void test_3(){
        SwordFinder sf = new SwordFinder();
        assertEquals(5,sf.operation("src/test3.txt"));
    }
    @Test
    public void test_4(){
        SwordFinder sf = new SwordFinder();
        assertEquals(8,sf.operation("src/test4.txt"));
    }
    @Test
    public void test_5(){
        SwordFinder sf = new SwordFinder();
        assertEquals(46660,sf.operation("src/test5.txt"));
    }
}