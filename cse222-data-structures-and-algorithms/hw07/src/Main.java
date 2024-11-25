import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

/**
 * Main class for managing and analyzing stock data using the StockDataManager.
 */
public class Main {

    /**
     * The main method to execute the program.
     *
     * @param args command-line arguments where the first argument is the input file path
     */
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java Main <input_file>");
            return;
        }

        String inputFile = args[0];
        StockDataManager manager = new StockDataManager();

        // Generate and process random script
        generateRandomScript("random_script.txt", 100);
        processFile("random_script.txt", manager);

        // Process the input file provided as an argument
        processFile(inputFile, manager);

        // Perform a simple performance analysis
        List<Long> addTimes = new ArrayList<>();
        List<Long> removeTimes = new ArrayList<>();
        List<Long> searchTimes = new ArrayList<>();
        List<Long> updateTimes = new ArrayList<>();
        performPerformanceAnalysis(manager, 100000, addTimes, removeTimes, searchTimes, updateTimes);

        // Visualize performance
        GUIVisualization.visualize(addTimes, removeTimes, searchTimes, updateTimes);
    }

    /**
     * Processes a file containing stock commands and executes them using the StockDataManager.
     *
     * @param fileName the name of the file to be processed
     * @param manager  the StockDataManager to manage stock data
     */
    private static void processFile(String fileName, StockDataManager manager) {
        try (BufferedReader br = new BufferedReader(new FileReader(fileName))) {
            String line;
            while ((line = br.readLine()) != null) {
                processCommand(line, manager);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Processes a single command and executes it using the StockDataManager.
     *
     * @param line    the command line to be processed
     * @param manager the StockDataManager to manage stock data
     */
    private static void processCommand(String line, StockDataManager manager) {
        String[] tokens = line.split(" ");
        String command = tokens[0];

        switch (command) {
            case "ADD":
                manager.addOrUpdateStock(tokens[1], Double.parseDouble(tokens[2]), Long.parseLong(tokens[3]), Long.parseLong(tokens[4]));
                break;
            case "REMOVE":
                manager.removeStock(tokens[1]);
                break;
            case "SEARCH":
                Stock stock = manager.searchStock(tokens[1]);
                if (stock != null) {
                    System.out.println(stock);
                } else {
                    System.out.println("Stock not found: " + tokens[1]);
                }
                break;
            case "UPDATE":
                manager.updateStock(tokens[1], Double.parseDouble(tokens[3]), Long.parseLong(tokens[4]), Long.parseLong(tokens[5]));
                break;
            default:
                System.out.println("Unknown command: " + command);
                break;
        }
    }

    /**
     * Performs performance analysis of stock operations using the StockDataManager.
     *
     * @param manager     the StockDataManager to manage stock data
     * @param size        the number of operations to perform for each type
     * @param addTimes    list to store times for add operations
     * @param removeTimes list to store times for remove operations
     * @param searchTimes list to store times for search operations
     * @param updateTimes list to store times for update operations
     */
    private static void performPerformanceAnalysis(StockDataManager manager, int size, List<Long> addTimes, List<Long> removeTimes, List<Long> searchTimes, List<Long> updateTimes) {
        long startTime, endTime;
        Random rand = new Random();

        // Measure time for ADD operation
        for (int i = 0; i < size; i++) {
            startTime = System.nanoTime();
            manager.addOrUpdateStock("MHR" + i, Math.random() * 100, (long) (Math.random() * 1000000), (long) (Math.random() * 1000000000));
            endTime = System.nanoTime();
            if (i % 100 == 0)
                addTimes.add(endTime - startTime);
        }
        System.out.println("Average ADD time: " + addTimes.stream().mapToLong(Long::longValue).average().orElse(0.0) + " ns");

        // Measure time for REMOVE operation
        for (int i = 0; i < size; i++) {
            startTime = System.nanoTime();
            manager.removeStock("MHR" + rand.nextInt(size));
            endTime = System.nanoTime();
            if (i % 100 == 0)
                removeTimes.add(endTime - startTime);
        }
        System.out.println("Average REMOVE time: " + removeTimes.stream().mapToLong(Long::longValue).average().orElse(0.0) + " ns");

        // Measure time for SEARCH operation
        for (int i = 0; i < size; i++) {
            startTime = System.nanoTime();
            manager.searchStock("MHR" + rand.nextInt(size));
            endTime = System.nanoTime();
            if (i % 100 == 0)
                searchTimes.add(endTime - startTime);
        }
        System.out.println("Average SEARCH time: " + searchTimes.stream().mapToLong(Long::longValue).average().orElse(0.0) + " ns");

    }

    /**
     * Generates a random script file with stock commands.
     *
     * @param fileName         the name of the script file to be generated
     * @param totalOperations the total number of operations to generate
     */
    private static void generateRandomScript(String fileName, int totalOperations) {
        Random rand = new Random();
        String[] commands = {"ADD", "REMOVE", "SEARCH", "UPDATE"};
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(fileName))) {
            for (int i = 0; i < totalOperations; i++) {
                String command = commands[rand.nextInt(commands.length)];
                String symbol = "MHR" + rand.nextInt(10000);
                switch (command) {
                    case "ADD":
                        double price = rand.nextDouble() * 100;
                        long volume = (long) (rand.nextDouble() * 1000000);
                        long marketCap = (long) (rand.nextDouble() * 1000000000);
                        bw.write(String.format("ADD %s %.2f %d %d%n", symbol, price, volume, marketCap));
                        break;
                    case "REMOVE":
                        bw.write(String.format("REMOVE %s%n", symbol));
                        break;
                    case "SEARCH":
                        bw.write(String.format("SEARCH %s%n", symbol));
                        break;
                    case "UPDATE":
                        double newPrice = rand.nextDouble() * 100;
                        long newVolume = (long) (rand.nextDouble() * 1000000);
                        long newMarketCap = (long) (rand.nextDouble() * 1000000000);
                        bw.write(String.format("UPDATE %s %s %.2f %d %d%n", symbol, symbol, newPrice, newVolume, newMarketCap));
                        break;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}