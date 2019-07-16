/**
 * Created by hmontoya on 10/29/15.
 */
public class Divider implements Runnable {
    int start;
    int end;
    private static int counter = 0;
    private static Object NoRace = new Object();

    public Divider(int start, int end) {
        this.start = start;
        this.end = end;

    }


    public void run() {
        for (int i=this.start; i <this.end; i++) {
            if (i%7 == 0) {
                synchronized (NoRace){
                    counter++;
                }
            }
        }
    }

    public static void main(String[] args) {
        Thread t1 = new Thread(new Divider(1, 1000));
        Thread t2 = new Thread(new Divider(1001, 2000));
        Thread t3 = new Thread(new Divider(2001, 3000));
        t1.start();
        t2.start();
        t3.start();
        try {
            t1.join();
            t2.join();
            t3.join();
        } catch (InterruptedException error) {
            System.out.println( "Big problem");
        }
        System.out.println(counter);
    }
}
