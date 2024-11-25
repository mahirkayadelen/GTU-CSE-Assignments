/**
 * The Main class provides a simple command-line interface for managing a file system.
 * Users can perform various operations such as changing directories, listing contents,
 * creating files/directories, deleting files/directories, moving files/directories,
 * searching for files/directories, printing directory trees, sorting contents by date,
 * and exiting the program.
 */
import java.util.Scanner;

public class Main {
    private static FileSystem fileSystem = new FileSystem();
    private static Directory currentDirectory;

    /**
     * The main method initializes the file system, sets the current directory to the root,
     * and starts the command-line interface for file system management.
     *
     * @param args The command-line arguments (not used).
     */
    public static void main(String[] args) {
        currentDirectory = fileSystem.getRoot();
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("\n===== File System Management Menu =====");
            System.out.println("1. Change directory");
            System.out.println("2. List directory contents");
            System.out.println("3. Create file/directory");
            System.out.println("4. Delete file/directory");
            System.out.println("5. Move file/directory");
            System.out.println("6. Search file/directory");
            System.out.println("7. Print directory tree");
            System.out.println("8. Sort contents by date created");
            System.out.println("9. Exit");
            System.out.print("Please select an option: ");
            int choice = scanner.nextInt();
            scanner.nextLine(); // Consume newline

            switch (choice) {
                case 1:
                    handleChangeDirectory(scanner);
                    break;
                case 2:
                    System.out.print(" Listing contents of " + fileSystem.getCurrentPath(currentDirectory)+"\n");
                    fileSystem.listContents(currentDirectory);
                    break;
                case 3:
                    handleCreateFileOrDirectory(scanner);
                    break;
                case 4:
                    handleDeleteFileOrDirectory(scanner);
                    break;
                case 5:
                    handleMoveElement(scanner);
                    break;
                case 6:
                    handleSearch(scanner);
                    break;
                case 7:
                    fileSystem.printDirectoryTree();
                    break;
                case 8:
                    handleSortContentsByDate();
                    break;
                case 9:
                    scanner.close();
                    System.out.println("Exiting...");
                    return;
                default:
                    System.out.println("Invalid option. Please select again.");
            }
        }
    }

    /**
     * Allows the user to change the current directory.
     *
     * @param scanner The Scanner object for user input.
     */
    private static void handleChangeDirectory(Scanner scanner) {
        System.out.print("Current directory: " + fileSystem.getCurrentPath(currentDirectory)+"\n");
        System.out.print("Enter new directory path: ");
        String path = scanner.nextLine();
        Directory newDir = fileSystem.changeDirectory(path);
        if (newDir != null) {
            currentDirectory = newDir;
            System.out.println("Directory changed to: " + fileSystem.getCurrentPath(currentDirectory));
        } else {
            System.out.println("Directory not found.");
        }
    }

    /**
     * Allows the user to create a new file or directory in the current directory.
     *
     * @param scanner The Scanner object for user input.
     */
    private static void handleCreateFileOrDirectory(Scanner scanner) {
        System.out.print("Current directory: " + fileSystem.getCurrentPath(currentDirectory)+"\n");
        System.out.print("Create file or directory (f/d): ");
        String type = scanner.nextLine();
        System.out.print("Enter name for new " + (type.equals("f") ? "file" : "directory") + ": ");
        String name = scanner.nextLine();
        if (type.equals("f")) {
            boolean created = fileSystem.createFile(name, currentDirectory);
            if (created) {
                System.out.println("File created: " + name);
            } else {
                System.out.println("Failed to create file.");
            }
        } else if (type.equals("d")) {
            boolean created = fileSystem.createDirectory(name, currentDirectory);
            if (created) {
                System.out.println("Directory created: " + name + "/");
            } else {
                System.out.println("Failed to create directory.");
            }
        } else {
            System.out.println("Invalid type. Use 'f' for file or 'd' for directory.");
        }
    }

    /**
     * Allows the user to delete a file or directory from the current directory.
     *
     * @param scanner The Scanner object for user input.
     */
    private static void handleDeleteFileOrDirectory(Scanner scanner) {
        System.out.print("Current directory: " + fileSystem.getCurrentPath(currentDirectory)+"\n");
        System.out.print("Enter name of file/directory to delete: ");
        String name = scanner.nextLine();
        fileSystem.deleteFile(name, currentDirectory);
        fileSystem.deleteDirectory(name, currentDirectory);
    }

    /**
     * Allows the user to move a file or directory to a new location.
     *
     * @param scanner The Scanner object for user input.
     */
    private static void handleMoveElement(Scanner scanner) {
        System.out.print("Current directory: " + fileSystem.getCurrentPath(currentDirectory)+"\n");
        System.out.print("Enter the name of file/directory to move: ");
        String name = scanner.nextLine();
        System.out.print("Enter new directory path: ");
        String newPath = scanner.nextLine();
        Directory newParent = fileSystem.changeDirectory(newPath);
        if (newParent != null && fileSystem.moveElement(name, newParent)) {
            System.out.println("Moved " + name + " to " + newPath);
        } else {
            System.out.println("Failed to move " + name);
        }
    }

    /**
     * Allows the user to search for a file or directory.
     *
     * @param scanner The Scanner object for user input.
     */
    private static void handleSearch(Scanner scanner) {
        System.out.print("Search query: ");
        String name = scanner.nextLine();
        System.out.println("Searching from root...");
        String foundPath = fileSystem.search(name, fileSystem.getRoot(), "");
        if (!foundPath.isEmpty()) {
            System.out.println("Found: " + foundPath);
        } else {
            System.out.println("No such file or directory found.");
        }
    }

    /**
     * Sorts the contents of the current directory by date created.
     */
    private static void handleSortContentsByDate() {
        if (currentDirectory != null) {
            fileSystem.sortDirectoryByDate(currentDirectory);
        } else {
            System.out.println("No current directory set.");
        }
    }
}
