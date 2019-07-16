/**
 * Created by hmontoya on 10/15/15.
 */
public class CD implements Sellable {
    String productName;
    double price;
    int totalSongs;
    public String getProductName() {
        return this.productName;
    }


    public double getPrice() {
        return this.price;
    }

    public CD(String productName, int totalSongs, double price) {
        this.productName = productName;
        this.totalSongs= totalSongs;
        this.price = price;
    }
    int getTotalSongs() {
        return this.totalSongs;
    }
}
