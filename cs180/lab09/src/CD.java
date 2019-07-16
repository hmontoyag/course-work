/**
 * Created by hmontoya on 10/22/15.
 */
public class CD extends AudioProduct {
    double price;

    public CD(String productName, int totalSongs, double price) {
        super(productName, totalSongs);
        this.price = price;
    }

    @Override
    public double getPrice() {
        return this.price;
    }
}
