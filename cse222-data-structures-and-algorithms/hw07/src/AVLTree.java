/**
 * AVLTree class that represents an AVL Tree data structure for managing Stock objects.
 */
public class AVLTree {

    /**
     * Private inner class that represents a node in the AVL Tree.
     */
    private class Node {
        Stock stock;
        Node left, right;
        int height;

        /**
         * Constructor to create a new node with the given stock.
         *
         * @param stock the stock to be stored in the node
         */
        Node(Stock stock) {
            this.stock = stock;
            this.height = 1;
        }
    }

    private Node root;

    /**
     * Inserts a stock into the AVL Tree.
     *
     * @param stock the stock to be inserted
     */
    public void insert(Stock stock) {
        root = insert(root, stock);
    }

    /**
     * Helper method to insert a stock into the subtree rooted with the given node.
     *
     * @param node  the root of the subtree
     * @param stock the stock to be inserted
     * @return the new root of the subtree
     */
    private Node insert(Node node, Stock stock) {
        if (node == null) {
            return new Node(stock);
        }

        int cmp = stock.getSymbol().compareTo(node.stock.getSymbol());
        if (cmp < 0) {
            node.left = insert(node.left, stock);
        } else if (cmp > 0) {
            node.right = insert(node.right, stock);
        } else {
            // Update the stock attributes if the symbol already exists
            node.stock.setPrice(stock.getPrice());
            node.stock.setVolume(stock.getVolume());
            node.stock.setMarketCap(stock.getMarketCap());
            return node;
        }

        // Update height of this ancestor node
        node.height = 1 + Math.max(height(node.left), height(node.right));

        // Get the balance factor of this ancestor node to check whether this node became unbalanced
        int balance = getBalance(node);

        // If this node becomes unbalanced, then there are 4 cases

        // Left Left Case
        if (balance > 1 && stock.getSymbol().compareTo(node.left.stock.getSymbol()) < 0)
            return rightRotate(node);

        // Right Right Case
        if (balance < -1 && stock.getSymbol().compareTo(node.right.stock.getSymbol()) > 0)
            return leftRotate(node);

        // Left Right Case
        if (balance > 1 && stock.getSymbol().compareTo(node.left.stock.getSymbol()) > 0) {
            node.left = leftRotate(node.left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && stock.getSymbol().compareTo(node.right.stock.getSymbol()) < 0) {
            node.right = rightRotate(node.right);
            return leftRotate(node);
        }

        return node;
    }

    /**
     * Deletes a stock from the AVL Tree by its symbol.
     *
     * @param symbol the symbol of the stock to be deleted
     */
    public void delete(String symbol) {
        root = delete(root, symbol);
    }

    /**
     * Helper method to delete a stock from the subtree rooted with the given node.
     *
     * @param node   the root of the subtree
     * @param symbol the symbol of the stock to be deleted
     * @return the new root of the subtree
     */
    private Node delete(Node node, String symbol) {
        if (node == null) {
            return node;
        }

        int cmp = symbol.compareTo(node.stock.getSymbol());
        if (cmp < 0) {
            node.left = delete(node.left, symbol);
        } else if (cmp > 0) {
            node.right = delete(node.right, symbol);
        } else {
            // Node with only one child or no child
            if ((node.left == null) || (node.right == null)) {
                Node temp = null;
                if (temp == node.left) {
                    temp = node.right;
                } else {
                    temp = node.left;
                }

                // No child case
                if (temp == null) {
                    temp = node;
                    node = null;
                } else { // One child case
                    node = temp; // Copy the contents of the non-empty child
                }
            } else {
                // Node with two children: Get the inorder successor (smallest in the right subtree)
                Node temp = minValueNode(node.right);

                // Copy the inorder successor's data to this node
                node.stock = temp.stock;

                // Delete the inorder successor
                node.right = delete(node.right, temp.stock.getSymbol());
            }
        }

        if (node == null) {
            return node;
        }

        // Update height of the current node
        node.height = 1 + Math.max(height(node.left), height(node.right));

        // Get the balance factor of this node
        int balance = getBalance(node);

        // If this node becomes unbalanced, then there are 4 cases

        // Left Left Case
        if (balance > 1 && getBalance(node.left) >= 0)
            return rightRotate(node);

        // Left Right Case
        if (balance > 1 && getBalance(node.left) < 0) {
            node.left = leftRotate(node.left);
            return rightRotate(node);
        }

        // Right Right Case
        if (balance < -1 && getBalance(node.right) <= 0)
            return leftRotate(node);

        // Right Left Case
        if (balance < -1 && getBalance(node.right) > 0) {
            node.right = rightRotate(node.right);
            return leftRotate(node);
        }

        return node;
    }

    /**
     * Searches for a stock in the AVL Tree by its symbol.
     *
     * @param symbol the symbol of the stock to be searched
     * @return the stock if found, otherwise null
     */
    public Stock search(String symbol) {
        Node result = search(root, symbol);
        return (result != null) ? result.stock : null;
    }

    /**
     * Helper method to search for a stock in the subtree rooted with the given node.
     *
     * @param node   the root of the subtree
     * @param symbol the symbol of the stock to be searched
     * @return the node containing the stock if found, otherwise null
     */
    private Node search(Node node, String symbol) {
        if (node == null || node.stock.getSymbol().equals(symbol)) {
            return node;
        }

        int cmp = symbol.compareTo(node.stock.getSymbol());
        if (cmp < 0) {
            return search(node.left, symbol);
        } else {
            return search(node.right, symbol);
        }
    }

    /**
     * Gets the height of the given node.
     *
     * @param node the node whose height is to be calculated
     * @return the height of the node
     */
    private int height(Node node) {
        return (node == null) ? 0 : node.height;
    }

    /**
     * Gets the balance factor of the given node.
     *
     * @param node the node whose balance factor is to be calculated
     * @return the balance factor of the node
     */
    private int getBalance(Node node) {
        return (node == null) ? 0 : height(node.left) - height(node.right);
    }

    /**
     * Performs a right rotation on the subtree rooted with the given node.
     *
     * @param y the root of the subtree
     * @return the new root of the subtree
     */
    private Node rightRotate(Node y) {
        Node x = y.left;
        Node T2 = x.right;

        // Perform rotation
        x.right = y;
        y.left = T2;

        // Update heights
        y.height = Math.max(height(y.left), height(y.right)) + 1;
        x.height = Math.max(height(x.left), height(x.right)) + 1;

        // Return new root
        return x;
    }

    /**
     * Performs a left rotation on the subtree rooted with the given node.
     *
     * @param x the root of the subtree
     * @return the new root of the subtree
     */
    private Node leftRotate(Node x) {
        Node y = x.right;
        Node T2 = y.left;

        // Perform rotation
        y.left = x;
        x.right = T2;

        // Update heights
        x.height = Math.max(height(x.left), height(x.right)) + 1;
        y.height = Math.max(height(y.left), height(y.right)) + 1;

        // Return new root
        return y;
    }

    /**
     * Gets the node with the minimum value in the given subtree.
     *
     * @param node the root of the subtree
     * @return the node with the minimum value
     */
    private Node minValueNode(Node node) {
        Node current = node;
        while (current.left != null) {
            current = current.left;
        }
        return current;
    }

    /**
     * Performs an in-order traversal of the AVL Tree.
     * Prints the stocks in ascending order.
     */
    public void inOrderTraversal() {
        inOrderTraversal(root);
    }

    /**
     * Helper method to perform in-order traversal on the subtree rooted with the given node.
     *
     * @param node the root of the subtree
     */
    private void inOrderTraversal(Node node) {
        if (node != null) {
            inOrderTraversal(node.left);
            System.out.println(node.stock);
            inOrderTraversal(node.right);
        }
    }

    /**
     * Performs a pre-order traversal of the AVL Tree.
     * Prints the stocks in pre-order.
     */
    public void preOrderTraversal() {
        preOrderTraversal(root);
    }

    /**
     * Helper method to perform pre-order traversal on the subtree rooted with the given node.
     *
     * @param node the root of the subtree
     */
    private void preOrderTraversal(Node node) {
        if (node != null) {
            System.out.println(node.stock);
            preOrderTraversal(node.left);
            preOrderTraversal(node.right);
        }
    }

    /**
     * Performs a post-order traversal of the AVL Tree.
     * Prints the stocks in post-order.
     */
    public void postOrderTraversal() {
        postOrderTraversal(root);
    }

    /**
     * Helper method to perform post-order traversal on the subtree rooted with the given node.
     *
     * @param node the root of the subtree
     */
    private void postOrderTraversal(Node node) {
        if (node != null) {
            postOrderTraversal(node.left);
            postOrderTraversal(node.right);
            System.out.println(node.stock);
        }
    }
}
