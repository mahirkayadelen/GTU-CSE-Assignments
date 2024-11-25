import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Inventory inventory = new Inventory();

        // Create 5 device
        Device phone1 = new SmartPhone("Galaxy S21", 800.00, 10);
        Device laptop1 = new Laptop("Dell XPS 13", 1200.00, 5);
        Device tv1 = new TV("LG OLED55", 1400.00, 7);
        Device headphones1 = new Headphones("Sony WH-1000XM4", 350.00, 15);
        Device watch1 = new SmartWatch("Apple Watch Series 6", 399.00, 12);

        // add them to inventory
        inventory.addDevice(phone1);
        inventory.addDevice(laptop1);
        inventory.addDevice(tv1);
        inventory.addDevice(headphones1);
        inventory.addDevice(watch1);
        
        while (true) {
            System.out.println("\nWelcome to the Electronics Inventory Management System!");
            System.out.println("Please select an option:");
            System.out.println("1. Add a new device");
            System.out.println("2. Remove a device");
            System.out.println("3. Update device details");
            System.out.println("4. List all devices");
            System.out.println("5. Find the cheapest device");
            System.out.println("6. Sort devices by price");
            System.out.println("7. Calculate total inventory value");
            System.out.println("8. Restock a device");
            System.out.println("9. Export inventory report");
            System.out.println("0. Exit");

            System.out.print("Enter your choice: ");
            int choice = scanner.nextInt();
            scanner.nextLine(); 

            switch (choice) {
                case 1:
                    addItem(inventory);
                    break;
                case 2:
                    System.out.print("Enter the name of the device to remove: ");
                    String removeName = scanner.nextLine();
                    inventory.removeDevice(removeName);
                    break;
                case 3:
                    updateItem(inventory);
                    break;
                case 4:
                    inventory.displayAllDevices();
                    break;
                case 5:
                    Device cheapest = inventory.findCheapestDevice();
                    if (cheapest != null) {
                        System.out.println("The cheapest device is: " + cheapest.getName() + " at $" + cheapest.getPrice());
                    } else {
                        System.out.println("No devices found.");
                    }
                    break;
                case 6:
                    inventory.sortDevicesByPrice();
                    break;
                case 7:
                    double totalValue = inventory.calculateTotalInventoryValue();
                    System.out.println("Total inventory value: $" + totalValue);
                    break;
                case 8:
                    restockItem(inventory);
                    break;
                case 9:
                    // Export inventory report
                    System.out.print("Enter the filename to export the report to: ");
                    String fileName = scanner.nextLine();
                    inventory.exportInventoryReport(fileName);
                    System.out.println("Inventory report exported to " + fileName);
                    break;
                case 0:
                    System.out.println("Exiting the system.");
                    return;
                default:
                    System.out.println("Invalid choice. Please enter a number between 0 and 9.");
            }
        }
    }

    /**
     * Prompts the user to add a new device to the inventory by specifying its details such as category, name, price, and quantity.
     * Validates the input for price and quantity to ensure they are greater than 0.
     * Based on the category specified, creates an instance of the corresponding device subclass and adds it to the inventory.
     * Displays a message indicating whether the device was successfully added or if an incorrect category was specified.
     * @param inventory The inventory to which the device will be added.
     */
    public static void addItem(Inventory inventory){
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter category name: ");
        String categoryName = scanner.nextLine();
        System.out.print("Enter device name: ");
        String deviceName = scanner.nextLine();
        System.out.print("Enter price: ");
        double price = scanner.nextDouble();
        System.out.print("Enter quantity: ");
        int quantity = scanner.nextInt();
        if(quantity <= 0){
            System.out.println("Quantity should be at least 1");
            return;
        }
        if(price <= 0){
            System.out.println("Price should be bigger than 0");
            return;
        }
        
        Device toAdd;
        boolean isAdded = false;
        switch(categoryName){
            case "Smart Phone":
                toAdd = new SmartPhone(deviceName, price, quantity);
                inventory.addDevice(toAdd);
                isAdded = true;
                break;
            case "Laptop":
                toAdd = new Laptop(deviceName, price, quantity);
                inventory.addDevice(toAdd);
                isAdded = true;

                break;
            case "TV":
                toAdd = new TV(deviceName, price, quantity);
                inventory.addDevice(toAdd);
                isAdded = true;
                break;
            case "Headphones":
                toAdd = new Headphones(deviceName, price, quantity);
                inventory.addDevice(toAdd);
                isAdded = true;
                break;
            case "Smart Watch":
                toAdd = new Headphones(deviceName, price, quantity);
                inventory.addDevice(toAdd);
                isAdded = true;
                break;
            default:
                System.out.println("Incorrect Device Category!");
                break;
        }
        if(isAdded){
            System.out.println(categoryName + ", " + deviceName + ", " + price + "$, " + quantity + " amount added..." );
        }
    }

    /**
     * Updates the details of a specific device in the inventory based on user input.
     * The user is prompted to enter the name of the device and then they can specify a new price and/or quantity for the device.
     * If the new price or quantity is not entered, the current values are retained. Validation ensures that any new price or quantity specified is greater than 0.
     * It calls {@code Inventory.updateDeviceDetails} to apply the updates.
     * @param inventory The inventory where the device details will be updated.
     */
    public static void updateItem(Inventory inventory){
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the name of the device to update: ");
        String toUpdate = scanner.nextLine();
        
        // For price, accept the input as String first
        System.out.print("Enter new price (leave blank to keep current price): ");
        String priceInput = scanner.nextLine();
        double updatedPrice = 0.0; // Default value indicating no change
        if (!priceInput.isBlank()) { // Check if the input is not blank
            double tempPrice = Double.parseDouble(priceInput); // Convert to double
            if(tempPrice <= 0){
                System.out.println("Price should be bigger than 0");
                return;
            }
            updatedPrice = tempPrice;
        }

        System.out.print("Enter new quantity (leave blank to keep current quantity): ");
        String quantityInput = scanner.nextLine();
        int updatedQuantity = 0; // Default value indicating no change
        if (!quantityInput.isBlank()) { // Check if the input is not blank
            int tempQuantity = Integer.parseInt(quantityInput); // Convert to int
            if(tempQuantity <= 0){
                System.out.println("Quantity should be at least 1");
                return;
            }
            updatedQuantity = tempQuantity;
        }
        inventory.updateDeviceDetails(toUpdate,updatedPrice,updatedQuantity);
    }

    /**
     * Allows for the restocking of a specified device in the inventory, either by adding to or removing from its current stock.
     * The user is prompted to enter the name of the device they wish to restock and then choose whether to add to or remove from the stock.
     * Depending on the user's choice, they are then asked to specify the quantity to add or remove.
     * Its calling {@code Inventory.restockDevice}.
     * @param inventory The inventory where the device's stock will be adjusted.
     */
    public static void restockItem(Inventory inventory){
        int restockAmount;
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the name of the device to restock: ");
        String toRestock = scanner.nextLine();

        System.out.print(" Do you want to add or remove stock? (Add/Remove): ");
        String addOrRemove = scanner.nextLine();

        switch(addOrRemove){
            case "Add":
                System.out.print("Enter the quantity to add: ");
                restockAmount = scanner.nextInt();
                inventory.restockDevice(toRestock,restockAmount,true);
                break;
            
            case "Remove":
                System.out.print("Enter the quantity to remove: ");
                restockAmount = scanner.nextInt();
                inventory.restockDevice(toRestock,restockAmount,false);
                break;
        }
    }
}