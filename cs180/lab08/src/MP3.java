/**
 * Created by hmontoya on 10/15/15.
 */
import java.util.UUID;
public class MP3 implements Sellable, Downloadable {
    String productName;
    double price = 0.99;
    public String getProductName() {
        return this.productName;
    }
    public double getPrice() {
        return 0.99;
    }
    public String generateDownloadCode() {
        return UUID.randomUUID().toString();
    }

    public MP3(String productName) {
        this.productName = productName;
    }
}
