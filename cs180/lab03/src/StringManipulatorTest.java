import static org.junit.Assert.*;
import org.junit.*;

/**
 * Created by hmontoya on 9/10/15.
 * JUnit test case class for testing the functionality of methods from the StringManipulator class
 *
 */
public class StringManipulatorTest {
    private StringManipulator sm;

    @Before
    public void setUp() throws Exception {
        sm = new StringManipulator();
    }
/**
 * Test makeUserName
 * Dont check correct case
 *
 */
    @Test(timeout = 100)
    public void testMakeUserNameBasic() {
        String ret = sm.makeUserName("john doe");
        String message = "makeUserName(); check if username follows the basic Unix style structure";
        assertEquals(message, "jdoe", ret);
    }
    @Test(timeout = 100)
    public void testMakerUserNameLower(){
        String ret = sm.makeUserName("John Doe");
        String message = "makeUserName(); check style structure";
        assertEquals(message, "jdoe", ret);

    }
    @Test(timeout = 100)
    public void testMakeEmail(){
        String ret = sm.makeEmail("jdoe", "purdue.edu");
        String message  = "makeUserName(); check style structure";
        assertEquals(message, "jdoe@purdue.edu", ret);



    }

}