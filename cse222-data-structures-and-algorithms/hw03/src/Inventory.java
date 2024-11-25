import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.Iterator;

public class Inventory {
    private LinkedList<ArrayList<Device>> deviceLists;

    public Inventory() {
        deviceLists = new LinkedList<>();

        for (int i = 0; i < 5; i++) { 
            deviceLists.add(new ArrayList<Device>());
        }
    }

    /**
     * The time complexity of the addDevice method is O(1), as it performs a constant number of operations regardless of the input size.
     * LinkedList has fixed size which is 5 so get() function of Linked Lists time complexity is O(1)
     * ArrayLists add function is O(1)
     * @param device
     */
    public void addDevice(Device device) {
        // Determine the index based on the device instance type
        int index = -1;
        if (device instanceof SmartPhone) {
            index = 0;
        } else if (device instanceof Laptop) {
            index = 1;
        } else if (device instanceof TV) {
            index = 2;
        } else if (device instanceof Headphones) {
            index = 3;
        } else if (device instanceof SmartWatch) {
            index = 4;
        }
    
        if (index != -1) {
            deviceLists.get(index).add(device);
        }
    }
    /**
     * O(n) because its iterating in ArrayLists till find device its doing this operation 5 times in worst case
     * @param deviceName
     * @return
     */
    public boolean removeDevice(String deviceName) {
        for (ArrayList<Device> deviceList : deviceLists) {
            Iterator<Device> iterator = deviceList.iterator();
            while (iterator.hasNext()) {
                Device device = iterator.next();
                if (device.getName().equalsIgnoreCase(deviceName)) {
                    iterator.remove();
                    return true;
                }
            }
        }
        // If no device with the specified name was found, return false
        return false;
    }
    /**
     * Time complexity is O(n) because its iterating in ArrayLists till find device , its doing this operation 5 times in worst case
     * @param deviceName
     * @param newPrice
     * @param newQuantity
     */
    public void updateDeviceDetails(String deviceName, double newPrice, int newQuantity) {
        // Flag to indicate if the device was found and updated
        boolean isUpdated = false;
        boolean isFound = false;
        // Iterate over each ArrayList<Device> in the LinkedList
        for (ArrayList<Device> deviceList : deviceLists) {
            // Iterate over each Device in the ArrayList
            for (Device device : deviceList) {
                // Check if the device name matches the name to be updated
                if (device.getName().equalsIgnoreCase(deviceName)) {
                    isFound = true;
                    // Update the device's price and quantity
                    if(newPrice > 0 ){ // dont change price if price 0
                        device.setPrice(newPrice);
                        isUpdated = true;
                    }
                    else{ // for display correctly
                        newPrice = device.getPrice();
                    }
                    if(newQuantity > 0){ // dont change quantity if its 0
                        device.setQuantity(newQuantity);
                        isUpdated = true;
                    }
                    else{ // for display correctly
                        newQuantity = device.getQuantity();
                    }
                    // Once the device is updated, break out of the loop
                    break;
                }
            }
            // If the device has been updated, no need to continue searching
            if (isUpdated){
                System.out.println(deviceName +" details updated: Price-" + newPrice + "Quantity-" + newQuantity );
            }

        }
        
        if (!isFound) {
            System.out.println("Device not found.");
        }
    }
    
    /**
     * Time complexity is O(n) because its iterating in ArrayLists , its doing this operation 5 times in worst case
     */
    public void displayAllDevices() {
        int deviceNumber = 1;
    
        for (ArrayList<Device> deviceList : deviceLists) {
            if (!deviceList.isEmpty()) {
                for (Device device : deviceList) {
                    System.out.println(deviceNumber + ". " +
                                       "Category: " + device.getCategory() + ", " +
                                       "Name: " + device.getName() + ", " +
                                       "Price: $" + String.format("%.2f", device.getPrice()) + ", " +
                                       "Quantity: " + device.getQuantity());
                    deviceNumber++;
                }
            }
        }
    
        if (deviceNumber == 1) {
            System.out.println("No devices found in the inventory.");
        }
    }

    /**
     * Time complexity is O(n) because its iterating in ArrayLists , its doing this operation 5 times in worst case
     * @return returns cheapest Device
     */
    public Device findCheapestDevice() {
        Device cheapestDevice = null;
        double minPrice = Double.MAX_VALUE; // Initialize with the maximum possible value
    
        // Iterate over each ArrayList<Device> in the LinkedList
        for (ArrayList<Device> deviceList : deviceLists) {
            // Iterate over each Device in the ArrayList
            for (Device device : deviceList) {
                // If the current device's price is lower than the current minPrice, update minPrice and cheapestDevice
                if (device.getPrice() < minPrice) {
                    minPrice = device.getPrice();
                    cheapestDevice = device;
                }
            }
        }
    
        return cheapestDevice;
    }

    /**
     * Time complexity is O(NlogN), where N is the total number of devices, due to the sorting step which dominates the overall complexity
     */
    public void sortDevicesByPrice() {
        // ArrayList to hold all devices
        ArrayList<Device> allDevices = new ArrayList<>();

        for (ArrayList<Device> deviceList : deviceLists) {
            allDevices.addAll(deviceList);
        }

        // Sort devices by price
        Collections.sort(allDevices, new Comparator<Device>() {
            @Override
            public int compare(Device device1, Device device2) {
                return Double.compare(device1.getPrice(), device2.getPrice());
            }
        });

        System.out.println("Devices sorted by price:");
        for (Device device : allDevices) {
            System.out.println("Category: " + device.getCategory() +
                            ", Name: " + device.getName() +
                            ", Price: $" + String.format("%.2f", device.getPrice()) +
                            ", Quantity: " + device.getQuantity());
        }
    }

    /**
     * Time complexity is O(n) because its iterating in ArrayLists , its doing this operation 5 times in worst case
     * @return returns price of cheapest Device
     */
    public double calculateTotalInventoryValue() {
        double totalValue = 0.0;
    
        // Iterate over each ArrayList<Device> in the LinkedList
        for (ArrayList<Device> deviceList : deviceLists) {
            // Iterate over each Device in the ArrayList
            for (Device device : deviceList) {
                // Add the product of the device's price and quantity to the total value
                totalValue += device.getPrice() * device.getQuantity();
            }
        }
    
        return totalValue;
    }

    /**
     * Time complexity is O(n)
     * It iterates over ArrayList which is O(n) and when it finds restocking device, it just calls once remove function and its also O(n) total O(2n) which is O(n)
     * @param deviceName
     * @param quantity
     * @param isAddingStock
     */
    public void restockDevice(String deviceName, int quantity, boolean isAddingStock) {
        boolean deviceFound = false;
    
        
        for (ArrayList<Device> deviceList : deviceLists) {
            
            for (Device device : deviceList) {
                // Check if the device name matches
                if (device.getName().equalsIgnoreCase(deviceName)) {
                    deviceFound = true;
                    
                    int newQuantity = isAddingStock ? device.getQuantity() + quantity : device.getQuantity() - quantity;

                    if(newQuantity < 0){ // quantity cannot be negative
                        System.out.println("Device quantity is " + device.getQuantity() + " You cannot remove " + quantity);
                    }
                    else if(newQuantity == 0){ // if there is no any stock left, remove device
                        removeDevice(deviceName);
                    }
                    else{ // Update the device's quantity
                        device.setQuantity(newQuantity);
                        if(isAddingStock)
                            System.out.println("Device " + deviceName + " restocked. New quantity: " + newQuantity);
                        else
                            System.out.println("Device " + deviceName + " reduced. New quantity: " + newQuantity);
                    }
                    // Once the device is found and updated, exit the loop
                    break;
                }
            }
            if (deviceFound) break;
        }
    
        if (!deviceFound) {
            System.out.println("Device not found.");
        }
    }

    /**
     * Time complexity is O(n) because its iterating in ArrayLists , its doing this operation 5 times(each category in LinkedList)
     * @param fileName
     */
    public void exportInventoryReport(String fileName) {
        try {

            PrintWriter out = new PrintWriter(new FileWriter(fileName, false));

            out.println("Electronics Shop Inventory Report");
            out.println("Generated on: " + java.time.LocalDate.now());
            out.println("-------------------------------------------------");
            out.println("| No. | Category | Name | Price | Quantity |");
            out.println("-------------------------------------------------");

            int deviceNumber = 1;

            for (ArrayList<Device> deviceList : deviceLists) {
                for (Device device : deviceList) {
                    out.printf("| %d | %s | %s | $%.2f | %d |\n",
                                deviceNumber++,
                                device.getCategory(),
                                device.getName(),
                                device.getPrice(),
                                device.getQuantity());
                }
            }
            out.println("-------------------------------------------------");
            out.println("\n\nSummary");
            out.println("-Total Number of Devices: " + deviceNumber);
            out.println("-Total Inventory Value: $" + calculateTotalInventoryValue());

            out.println("\nEnd of Report");

            // Check if no devices were found
            if (deviceNumber == 1) {
                out.println("No devices found in the inventory.");
            }

            out.close();
        } catch (IOException e) {
            System.out.println("An error occurred while writing to the file: " + e.getMessage());
        }
    }
}
