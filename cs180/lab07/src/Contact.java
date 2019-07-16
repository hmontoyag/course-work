/**
 * Created by hmontoya on 10/8/15.
 */
public class Contact {
    private String name;
    private long number;
    private String address;

    public Contact(String name) {
        this(name, 0, null);
    }
    public Contact(String name, long number) {
        this(name, number, null);
    }
    public Contact(String name, long number, String address) {
        this.name = name;
        this.number = number;
        this.address = address;
    }

    // getters

    public String getName() {
        return name;
    }

    public long getNumber() {
        return number;
    }

    public String getAddress() {
        return address;
    }

    //setters


    public void setName(String name) {
        this.name = name;
    }

    public void setNumber(long number) {
        this.number = number;
    }

    public void setAddress(String address) {
        this.address = address;
    }


    public boolean equals(Contact contact ) {
        if (contact.getName().equals(this.name)){
            return true;
        } else {
            return false;
        }
    }
}
