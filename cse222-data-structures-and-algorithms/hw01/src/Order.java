public class Order {
    String product_name;
    int count;
    int total_price;
    int status;
    int customer_id;

    public Order(String product_name, int count, int total_price, int status, int customer_id) {
        this.product_name = product_name;
        this.count = count;
        this.total_price = total_price;
        this.status = status;
        this.customer_id = customer_id;
    }

    public void print_order() {
        String statusString = "Unknown";
        if(status == 0)
            statusString = "Initialized";
        else if(status == 1)
            statusString = "Processing";
        else if(status == 2)
            statusString = "Completed";
        else if(status == 3)
            statusString = "Cancelled";
        System.out.println("Product name: " + product_name + " - Count: " + count + " - Total price: " + total_price + " - Status: " + statusString + ".");
    }
}
