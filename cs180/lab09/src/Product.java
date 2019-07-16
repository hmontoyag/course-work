/**
 * Created by hmontoya on 10/22/15.
 */
public abstract class Product {
    String productName;

    public Product (String productName) {

        this.productName = productName;
    }

    String getProductName() {
        return this.productName;
    }

    abstract double getPrice();

}
