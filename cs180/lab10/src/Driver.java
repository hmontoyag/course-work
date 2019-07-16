/**
 * Created by hmontoya on 10/29/15.
 */
public class Driver {
    public static void main(String[] args) {
        Thread t = new A();
        t.start();
        Runnable r = new B();
        Thread f = new Thread(r);
        f.start();
    }
}
