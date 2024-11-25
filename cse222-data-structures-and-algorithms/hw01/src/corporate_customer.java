public class corporate_customer extends Customer {
    String company_name;

    public corporate_customer(String name, String surname, String address, String phone, int ID, int operator_ID, String company_name) {
        super(name, surname, address, phone, ID, operator_ID);
        this.company_name = company_name;
    }

    @Override
    public void print_customer() {
        System.out.println("Name & Surname: " + name + " " + surname);
        System.out.println("Address: " + address);
        System.out.println("Phone: " + phone);
        System.out.println("ID: " + ID);
        System.out.println("Operator ID:" + operator_ID);
        System.out.println("Company name: " + company_name); // Print the additional company name
        print_orders(); // This method is inherited and will print all orders associated with this customer
    }
}