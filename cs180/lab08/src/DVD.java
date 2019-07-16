/**
 * Created by hmontoya on 10/15/15.
 */
public class DVD implements Sellable {
    String productName;
    double price;
    VideoType type;

    public String getProductName() {
        return this.productName;
    }

    public double getPrice() {
        return this.price;
    }

    public DVD(String productName, double price, VideoType type) {
        this.productName = productName;
        this.price = price;
        this.type = type;
    }
    VideoType getType() {
        return this.type;
    }

}
