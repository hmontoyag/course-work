import java.util.UUID;

/**
 * Created by hmontoya on 10/22/15.
 */
public class MP4 extends VideoProduct implements Downloadable {

    public MP4(String productName, VideoType type) {
        super(productName, type);
    }
    double getPrice() {
        if (getType() == VideoType.MOVIE) {
            return 4.99;
        } else {
            return 19.99;
        }
    }
    public String generateDownloadCode() {
        return UUID.randomUUID().toString();
    }
}
