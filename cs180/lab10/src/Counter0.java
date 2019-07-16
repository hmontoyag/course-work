/**
 * Created by hmontoya on 10/29/15.
 */
public class Counter0 implements Counter {

    private int value = 0;

    public void inc() {
        value = value + 1;
    }

    public void dec() {
        value = value - 1;
    }

    public int get() {
        return value;
    }

}
