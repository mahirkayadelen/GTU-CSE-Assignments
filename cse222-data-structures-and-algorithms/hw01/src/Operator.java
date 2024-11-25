public class Operator extends Person {
    int wage;
    Customer[] customers;

    public Operator(String name, String surname, String address, String phone, int ID, int wage) {
        super(name, surname, address, phone, ID);
        this.wage = wage;
        define_customers();
    }

    public void print_operator() {
        System.out.println("Name & Surname: " + name + " " + surname);
        System.out.println("Address: " + address);
        System.out.println("Phone: " + phone);
        System.out.println("ID: " + ID);
        System.out.println("Wage: " + wage);
        print_customers();
        System.out.println("----------------------------");

    }

    public void print_customers() {
        String customer_type = "unknown";
        if (customers != null) {
            for (int i = 0; i < customers.length; i++) {
                if (customers[i] != null) { // Check if the customer at this index is not null
                    System.out.println("----------------------------");
                    if(customers[i].getClass().getSimpleName() == "retail_customer")
                        customer_type = "a retail customer";
                    else if(customers[i].getClass().getSimpleName() == "corporate_customer")
                        customer_type = "a corporate customer";
                    System.out.println("Customer #" + (i + 1) + " (" + customer_type + "):");
                    customers[i].print_customer();
                }
            }
            if(customers.length == 0){
                System.out.println("----------------------------");
                System.out.println("This operator doesn't have any customer.");
            }
        }
    }

    public void define_customers() {
        int customerCount = 0;

        // First, count how many customers are linked to this operator
        for (Customer customer : CustomerTracking.retail_customers) {
            if (customer != null && customer.operator_ID == this.ID) {
                customerCount++;
            }
        }
        for (Customer customer : CustomerTracking.corporate_customers) {
            if (customer != null && customer.operator_ID == this.ID) {
                customerCount++;
            }
        }

        // Initialize the customers array with the correct size
        this.customers = new Customer[customerCount];

        // Then, assign the customers to this operator
        int index = 0;
        for (Customer customer : CustomerTracking.retail_customers) {
            if (customer != null && customer.operator_ID == this.ID) {
                this.customers[index++] = customer;
            }
        }
        for (Customer customer : CustomerTracking.corporate_customers) {
            if (customer != null && customer.operator_ID == this.ID) {
                this.customers[index++] = customer;
            }
        }
    }
}
