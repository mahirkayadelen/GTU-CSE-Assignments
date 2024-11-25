import java.io.File;
import java.util.Scanner;

public class CustomerTracking {
    public static final int MAX_RECORDS = 100;
    public static Order[] allOrders = new Order[MAX_RECORDS];
    public static retail_customer[] retail_customers = new retail_customer[MAX_RECORDS];
    public static corporate_customer[] corporate_customers = new corporate_customer[MAX_RECORDS];
    public static Operator[] operators = new Operator[MAX_RECORDS];
    public static int orderCount = 0, retail_customerCount = 0, corporate_customerCount = 0, operatorCount = 0;

    public static void main(String[] args) {
        try {
            File file = new File("content.txt");
            Scanner scanner = new Scanner(file);
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                processLine(line);
            }
            scanner.close();

            
            Scanner userInputScanner = new Scanner(System.in);
            System.out.println("Please enter your ID... ");
            try{
                int inputID = userInputScanner.nextInt(); // Read the ID entered by the user
                if (findAndPrintOperator(inputID) == 0) { // Try to find and print the operator
                    if (findAndPrintCustomer(inputID) == 0) { // If not found, try to find and print the customer
                        System.out.println("No operator/customer was found with ID " + inputID + ". Please try again.");
                    }
                }
            }catch(Exception e){
                System.out.println("inputID exception");
            }
            userInputScanner.close();
        } catch (Exception e) {
            System.out.println("An error occurred.");
        }
    }


    private static int findAndPrintOperator(int id) {
        for (Operator operator : operators) {
            if (operator != null && operator.ID == id) {
                System.out.println("*** Operator Screen ***");
                System.out.println("----------------------------");
                operator.print_operator();
                return 1; // Operator found and printed
            }
        }
        return 0; // Operator not found
    }
    
    private static int findAndPrintCustomer(int id) {
        for (retail_customer customer : retail_customers) {
            if (customer != null && customer.ID == id) {
                System.out.println("*** Customer Screen ***");
                customer.print_customer();
                return 1; // Customer found and printed
            }
        }
        for (corporate_customer customer : corporate_customers) {
            if (customer != null && customer.ID == id) {
                customer.print_customer();
                return 1; // Customer found and printed
            }
        }
        return 0; // Customer not found
    }

    private static void processLine(String line) {
        if(line.endsWith(";")) // if there is an extra ; at the end of line ignore that line for make sure there is no any extra column
            return ;
        String[] parts = line.split(";");
        switch (parts[0]) {
            case "order":
                if (parts.length == 6) {
                    try {
                        if((!parts[1].isEmpty() &&!parts[2].isEmpty() &&!parts[3].isEmpty() && !parts[4].isEmpty() &&!parts[5].isEmpty() ) &&   Integer.parseInt(parts[2]) != 0 && (Integer.parseInt(parts[4]) >= 0 && Integer.parseInt(parts[4]) <= 3) ){ // if count is 0 or status is not in range[0,3] or empty string ignore that order
                            Order order = new Order(parts[1], Integer.parseInt(parts[2]), Integer.parseInt(parts[3]), Integer.parseInt(parts[4]), Integer.parseInt(parts[5]));
                            if(order.count >= 0 && order.total_price >= 0 && order.customer_id >= 0){ // it checks if orders count, total price and customer id is bigger than 0
                                order.print_order();
                                allOrders[orderCount++] = order;
                            }
                        }
                    } catch (Exception e) {
                        // Handle exception or ignore invalid line
                    }
                }
                break;
            case "retail_customer":
                if (parts.length == 7) {
                    if((!parts[1].isEmpty() &&!parts[2].isEmpty() &&!parts[3].isEmpty() && !parts[4].isEmpty() &&!parts[5].isEmpty()&&!parts[6].isEmpty() )){ // if any string is empty ignore
                        try{
                            retail_customer customer = new retail_customer(parts[1], parts[2], parts[3], parts[4], Integer.parseInt(parts[5]), Integer.parseInt(parts[6]));
                            if(isIDUnique(customer.ID) && customer.ID > 0 && customer.operator_ID > 0)
                                retail_customers[retail_customerCount++] = customer;
                        }catch (Exception e) {
                            // integer errors (too large or not convertible)
                        }
                    }
                }
                break;
            case "corporate_customer":
                if (parts.length == 8) {
                    if(!parts[1].isEmpty() &&!parts[2].isEmpty() &&!parts[3].isEmpty() && !parts[4].isEmpty() &&!parts[5].isEmpty()&&!parts[6].isEmpty() &&!parts[7].isEmpty()){ // if any string is empty ignore
                        corporate_customer customer = new corporate_customer(parts[1], parts[2], parts[3], parts[4], Integer.parseInt(parts[5]), Integer.parseInt(parts[6]), parts[7]);
                        try{
                            if(isIDUnique(customer.ID) && customer.ID > 0 && customer.operator_ID > 0)
                            corporate_customers[corporate_customerCount++] = customer;
                        }catch (Exception e) {
                            // integer errors (too large or not convertible)
                        }

                    }
                }
                break;
            case "operator":
                if (parts.length == 7) {
                    if(!parts[1].isEmpty() &&!parts[2].isEmpty() &&!parts[3].isEmpty() && !parts[4].isEmpty() &&!parts[5].isEmpty()&&!parts[6].isEmpty() ){ // if any string is empty ignore
                        Operator operator = new Operator(parts[1], parts[2], parts[3], parts[4], Integer.parseInt(parts[5]), Integer.parseInt(parts[6]));
                        try{
                            if(isIDUnique(operator.ID) && operator.ID > 0 && operator.wage > 0)
                            operators[operatorCount++] = operator;
                        }catch (NumberFormatException e) {
                            // integer errors (too large or not convertible)
                        }
                    }
                }
                break;
            default:
                // Ignore other lines doesnt match 
                break;
        }
    }


    
    public static boolean isIDUnique(int ID) {  // Check each array for the match of the ID

        for (retail_customer customer : retail_customers) {
            if (customer != null && customer.ID == ID) {
                return false; // ID found in retail_customers
            }
        }
        
        for (corporate_customer customer : corporate_customers) {
            if (customer != null && customer.ID == ID) {
                return false; // ID found in corporate_customers
            }
        }
        
        for (Operator operator : operators) {
            if (operator != null && operator.ID == ID) {
                return false; // ID found in operators
            }
        }
        
        return true; // No match found, ID is unique
    }
}
