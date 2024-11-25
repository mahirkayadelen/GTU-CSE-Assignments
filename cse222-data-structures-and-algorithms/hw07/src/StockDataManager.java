/**
 * StockDataManager class that manages stock data using an AVL Tree.
 */
public class StockDataManager {
    private AVLTree avlTree;

    /**
     * Constructor to initialize the StockDataManager with an empty AVL Tree.
     */
    public StockDataManager() {
        avlTree = new AVLTree();
    }

    /**
     * Adds a new stock or updates an existing stock in the AVL Tree.
     *
     * @param symbol    the symbol of the stock
     * @param price     the price of the stock
     * @param volume    the volume of the stock
     * @param marketCap the market capitalization of the stock
     */
    public void addOrUpdateStock(String symbol, double price, long volume, long marketCap) {
        Stock existingStock = avlTree.search(symbol);
        if (existingStock != null) {
            existingStock.setPrice(price);
            existingStock.setVolume(volume);
            existingStock.setMarketCap(marketCap);
        } else {
            Stock newStock = new Stock(symbol, price, volume, marketCap);
            avlTree.insert(newStock);
        }
    }

    /**
     * Removes a stock from the AVL Tree by its symbol.
     *
     * @param symbol the symbol of the stock to be removed
     */
    public void removeStock(String symbol) {
        avlTree.delete(symbol);
    }

    /**
     * Searches for a stock in the AVL Tree by its symbol.
     *
     * @param symbol the symbol of the stock to be searched
     * @return the stock if found, otherwise null
     */
    public Stock searchStock(String symbol) {
        return avlTree.search(symbol);
    }

    /**
     * Updates the details of an existing stock in the AVL Tree.
     *
     * @param symbol      the symbol of the stock to be updated
     * @param newPrice    the new price of the stock
     * @param newVolume   the new volume of the stock
     * @param newMarketCap the new market capitalization of the stock
     */
    public void updateStock(String symbol, double newPrice, long newVolume, long newMarketCap) {
        Stock stock = avlTree.search(symbol);
        if (stock != null) {
            stock.setPrice(newPrice);
            stock.setVolume(newVolume);
            stock.setMarketCap(newMarketCap);
        }
    }

    /**
     * Main method for testing the StockDataManager class.
     *
     * @param args command-line arguments
     */
    public static void main(String[] args) {
        StockDataManager manager = new StockDataManager();
        manager.addOrUpdateStock("AAPL", 150.0, 1000000, 2500000000L);
        manager.addOrUpdateStock("GOOGL", 2800.0, 500000, 1500000000L);
        System.out.println(manager.searchStock("AAPL"));
        manager.removeStock("AAPL");
        System.out.println(manager.searchStock("AAPL"));
    }
}
