import java.util.Arrays;

/**
 * Created by hmontoya on 10/8/15.
 */
public class AddressBook {
    private int totalContacts;    // The total number of Contacts currently in this AddressBook
    private int maxContacts;      // The maximum number of Contacts this AddressBook can hold
    private Contact[] contacts;   // The array that holds the Contacts of this AddressBook

    /**
     * Constructor. Sets the initial size of the AddressBook to hold 10 Contacts.
     */
    public AddressBook() {
        totalContacts = 0;
        maxContacts = 10;
        this.contacts = new Contact[this.maxContacts];

        // TODO: initialize instance variables
    }

    /**
     * Adds the specified Contact to this AddressBook at the end of the contacts array. If
     * the Contact already exists, it updates its phone number if the argument's number is not 0 and
     * address if the argument's address is not null. If the totalContacts reaches the
     * maxContacts, then the contacts array is doubled in size and maxContacts is doubled
     * before the new Contact is added.
     *
     * @param contact The Contact to add to this AddressBook
     * @return true if the Contact was added, false otherwise
     */
    public boolean addContact(Contact contact) {

        if (contains(contact)) {
            Contact contact1 = getContactByName(contact.getName());
            if (contact.getAddress() != null) {
                contact1.setAddress(contact.getAddress());
            }
            if (contact.getNumber() != 0) {
                contact1.setNumber(contact.getNumber());
            }
            return false;
        } else {
            if (totalContacts + 1 == maxContacts) {
                maxContacts = maxContacts * 2;
                Contact[] newCont = Arrays.copyOf(contacts, maxContacts);
                contacts = newCont;
            }
            contacts[totalContacts] = contact;
            totalContacts++;
            return true;

        }
    }

    /**
     * Removes the specified Contact from this AddressBook and moves all entries
     * that follow it in the contacts array to the left so that there are no empty
     * entries between Contacts. For example:
     *
     * before -> {C1, C2, C3, C4, C5, C6, C7, C8, C9, null}
     * remove C6
     * after -> {C1, C2, C3, C4, C5, C7, C8, C9, null, null}
     *
     * @param contact The Contact to remove from this AddressBook
     * @return true if the Contact was removed, false otherwise
     */
    public boolean removeContact(Contact contact) {

        for (int i = 0; i < totalContacts; i++) {
            if (contact.equals(contacts[i])) {
                for (int j = i; j < maxContacts-1; j++) {

                        contacts[j] = contacts[j+1];

                }
                totalContacts--;
               return true;
            }
        }
        return false;

        // TODO: implement this method
    }

    /**
     * Gets a Contact by the specified name from this AddressBook.
     *
     * @param name The name of the Contact to get
     * @return The Contact if they are found, null otherwise
     */
    public Contact getContactByName(String name) {
        for (int i = 0; i < totalContacts; i++) {
            if (contacts[i].getName().equalsIgnoreCase(name)) {
                return contacts[i];
            }
        }
        // TODO: implement this method
        return null;
    }

    /**
     * Checks if the given contact is already in this AddressBook.
     *
     * @param contact The contact to find
     * @return True if the contact is found, false otherwise
     */
    public boolean contains(Contact contact) {
        int n= 0;
        for (int i = 0; i < totalContacts; i++) {
            if (contact.equals(contacts[i])) {
               return true;
            } else {
               n = n;
            }
        }
        return false;
    }

    /**
     * Prints all the Contacts in this AddressBook.
     */
    public void printAddressBook() {
        for (int i = 0; i < this.totalContacts; i++) {
            System.out.printf("Name: %s%n", this.contacts[i].getName());
            System.out.printf("Number: %d%n", this.contacts[i].getNumber());
            System.out.printf("Address: %s%n%n", this.contacts[i].getAddress());
        }
    }


}
