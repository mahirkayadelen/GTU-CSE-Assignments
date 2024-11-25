public abstract class ExtendedDevice implements Device {
    private String category;
    private String name;
    private double price;
    private int quantity;
    
    @Override
    public String getCategory() { return category; }
    @Override
    public void setCategory(String category) { this.category = category; }

    @Override
    public String getName() { return name; }
    @Override
    public void setName(String name) { this.name = name; }

    @Override
    public double getPrice() { return price; }
    @Override
    public void setPrice(double price) { this.price = price; }

    @Override
    public int getQuantity() { return quantity; }
    @Override
    public void setQuantity(int quantity) { this.quantity = quantity; }
    
}
