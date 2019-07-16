/**
 * Created by hmontoya on 10/22/15.
 */
public abstract class AudioProduct  extends Product{
    int totalSongs;

    public AudioProduct(String productName, int totalSongs) {
        super(productName);
        this.totalSongs = totalSongs;
    }

    public int getTotalSongs() {
        return this.totalSongs;
    }
}
