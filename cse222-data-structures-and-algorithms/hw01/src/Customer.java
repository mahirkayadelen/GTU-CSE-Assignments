public class Customer extends Person {
    Order[] orders;
    int operator_ID;

    public Customer(String name, String surname, String address, String phone, int ID, int operator_ID) {
        super(name, surname, address, phone, ID);
        this.operator_ID = operator_ID;
        define_orders();
    }

    public void print_customer() {
        System.out.println("Name & Surname: " + name + " " + surname);
        System.out.println("Address: " + address);
        System.out.println("Phone: " + phone);
        System.out.println("ID: " + ID);
        System.out.println("Operator ID:" + operator_ID);
        print_orders(); // Call print_orders() to print all orders associated with this customer
    }

    public void print_orders() {
        if (orders != null) {
            for (int i = 0; i < orders.length; i++) {
                if (orders[i] != null) { // Check if the order at this index is not null
                    System.out.print("Order #" + (i + 1) + " => ");
                    orders[i].print_order(); // Updated method name to print_order
                }
            }
        }
    }

    public void define_orders() {
        int orderCount = 0;

        // First, count how many orders belong to this customer
        for (Order order : CustomerTracking.allOrders) {
            if (order != null && order.customer_id == this.ID) {
                orderCount++;
            }
        }

        // Initialize the orders array with the correct size
        this.orders = new Order[orderCount];

        // Then, assign the orders to this customer
        int index = 0;
        for (Order order : CustomerTracking.allOrders) {
            if (order != null && order.customer_id == this.ID) {
                this.orders[index++] = order;
            }
        }
    }
}
