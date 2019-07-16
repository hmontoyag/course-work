import java.util.UUID;

/**
 * Created by hmontoya on 10/22/15.
 */
public class MP3 extends AudioProduct implements Downloadable {


    public MP3 (String productName) {
        super(productName, 1);

    }

    double getPrice() {
        return 0.99;
    }

    public String generateDownloadCode() {
        return UUID.randomUUID().toString();
    }
}
