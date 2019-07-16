/**
 * Created by hmontoya on 10/15/15.
 */
import java.util.UUID;
public class MP4 implements Sellable, Downloadable {
    String productName;
    double price = 4.99;
    VideoType type;

    public String getProductName() {
        return this.productName;
    }

    public double getPrice() {
        return 4.99;
    }

    public String generateDownloadCode() {
        return UUID.randomUUID().toString();
    }

    public MP4(String productName, VideoType type) {
        this.productName = productName;
        this.type = type;
    }
    VideoType getType() {
        return this.type;
    }
}
