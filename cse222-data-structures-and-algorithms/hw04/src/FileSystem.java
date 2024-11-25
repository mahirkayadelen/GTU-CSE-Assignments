/**
 * The FileSystem class represents a file system structure consisting of directories and files.
 * It provides methods for creating, deleting, moving, and searching elements within the file system,
 * as well as listing directory contents, printing directory trees, and sorting contents by date created.
 */
import java.util.Optional;
import java.util.Collections;

public class FileSystem {
    private Directory root;

    /**
     * Constructs a new FileSystem object with a root directory named "root".
     */
    public FileSystem() {
        this.root = new Directory("root", null);
    }

    /**
     * Creates a new file with the specified name in the given parent directory.
     *
     * @param name   The name of the file to be created.
     * @param parent The parent directory in which the file will be created.
     * @return true if the file is successfully created, false otherwise.
     */
    public boolean createFile(String name, Directory parent) {
        if (parent == null) return false;
        File newFile = new File(name, parent);
        parent.addChild(newFile);
        return true;
    }

    /**
     * Creates a new directory with the specified name in the given parent directory.
     *
     * @param name   The name of the directory to be created.
     * @param parent The parent directory in which the directory will be created.
     * @return true if the directory is successfully created, false otherwise.
     */
    public boolean createDirectory(String name, Directory parent) {
        if (parent == null) return false;
        Directory newDirectory = new Directory(name, parent);
        parent.addChild(newDirectory);
        return true;
    }

    /**
     * Deletes the file with the specified name from the given parent directory.
     *
     * @param name   The name of the file to be deleted.
     * @param parent The parent directory from which the file will be deleted.
     */
    public void deleteFile(String name, Directory parent) {
        if (parent != null) {
            if(parent.getChildren().removeIf(child -> child.getName().equals(name) && child instanceof File))
                System.out.println("File deleted: " + name);
        }
    }

    /**
     * Deletes the directory with the specified name from the given parent directory.
     *
     * @param name   The name of the directory to be deleted.
     * @param parent The parent directory from which the directory will be deleted.
     */
    public void deleteDirectory(String name, Directory parent) {
        if (parent != null) {
            if(parent.getChildren().removeIf(child -> child.getName().equals(name) && child instanceof Directory))
                System.out.println("Directory deleted: " + name);
        }
    }

    /**
     * Moves the file or directory with the specified name to the new parent directory.
     *
     * @param name      The name of the file or directory to be moved.
     * @param newParent The new parent directory to which the file or directory will be moved.
     * @return true if the element is successfully moved, false otherwise.
     */
    public boolean moveElement(String name, Directory newParent) {

        if (newParent == null) return false;
        Optional<FileSystemElement> element = findElement(name, root);
        if (element.isPresent()) {

            FileSystemElement fsElement = element.get();
            if (fsElement instanceof Directory) {  // Check if it's a Directory before casting
                Directory parentDir = (Directory) fsElement.getParent();
                if (parentDir != null) {
                    parentDir.getChildren().remove(fsElement);
                }
                fsElement.setParent(newParent);
                newParent.addChild(fsElement);
                return true;
            }
            else if(fsElement instanceof File){
                Directory parentDir = (Directory) fsElement.getParent();
                if (parentDir != null) {
                    parentDir.getChildren().remove(fsElement);
                    fsElement.setParent(newParent);
                    newParent.addChild(fsElement);
                    return true;

                }


            }
        }
        return false;
    }

    /**
     * Retrieves the current path of the given directory within the file system.
     *
     * @param dir The directory for which to retrieve the current path.
     * @return The current path of the directory.
     */
    public String getCurrentPath(Directory dir) {
        if (dir == null) return "/";
        return dir == root ? "/" : getCurrentPath((Directory) dir.getParent()) + dir.getName() + "/";
    }

    /**
     * Searches for the file or directory with the specified name starting from the given directory.
     *
     * @param name     The name of the file or directory to search for.
     * @param startDir The directory from which to start the search.
     * @param path     The current path during the search.
     * @return The path of the found file or directory, or an empty string if not found.
     */
    public String search(String name, Directory startDir, String path) {
        if (startDir.getName().equals(name)) {
            return path + "/" + name;
        }
        for (FileSystemElement element : startDir.getChildren()) {
            String foundPath = search(name, element, path + "/" + startDir.getName());
            if (!foundPath.isEmpty()) {
                return foundPath;
            }
        }
        return "";
    }

    private String search(String name, FileSystemElement element, String path) {
        if (element instanceof Directory) {
            return search(name, (Directory) element, path);
        } else {
            if (element.getName().equals(name)) {
                return path + "/" + name;
            }
        }
        return "";
    }

    private Optional<FileSystemElement> findElement(String name, FileSystemElement current) {
        if (current.getName().equals(name)) {
            return Optional.of(current);
        }
        if (current instanceof Directory) {
            for (FileSystemElement child : ((Directory) current).getChildren()) {
                Optional<FileSystemElement> found = findElement(name, child);
                if (found.isPresent()) {
                    return found;
                }
            }
        }
        return Optional.empty();
    }

    /**
     * Prints the directory tree starting from the root directory.
     */
    public void printDirectoryTree() {
        root.print("");
    }

    /**
     * Lists the contents (files and directories) of the given directory.
     *
     * @param dir The directory whose contents are to be listed.
     */
    public void listContents(Directory dir) {
        if (dir != null) {
            for (FileSystemElement child : dir.getChildren()) {
                child.print("  ");
            }
        }
    }

    /**
     * Sorts the contents of the given directory by date created.
     *
     * @param dir The directory whose contents are to be sorted.
     */
    public void sortDirectoryByDate(Directory dir) {
        if (dir != null) {
            dir.getChildren().sort((a, b) -> a.getDateCreated().compareTo(b.getDateCreated()));
            System.out.println("Sorted contents of " + getCurrentPath(dir) + " by date created:");
            for (FileSystemElement child : dir.getChildren()) {
                child.printWithTimestamp(" ");
            }
        } else {
            System.out.println("Directory is null, cannot sort.");
        }
    }

    /**
     * Changes the current directory to the one specified by the given path.
     *
     * @param path The path to the new directory.
     * @return The new directory if found, null otherwise.
     */
    public Directory changeDirectory(String path) {
        String[] parts = path.split("/");
        return navigate(parts, root, 0);
    }

    private Directory navigate(String[] parts, Directory current, int index) {
        if (index >= parts.length || current == null) return current;
        if (parts[index].isEmpty() || parts[index].equals(".")) return navigate(parts, current, index + 1);
        if (parts[index].equals("..")) return navigate(parts, (Directory) current.getParent(), index + 1);

        for (FileSystemElement child : current.getChildren()) {
            if (child.getName().equals(parts[index]) && child instanceof Directory) {
                return navigate(parts, (Directory) child, index + 1);
            }
        }
        return null; // Not found
    }

    /**
     * Retrieves the root directory of the file system.
     *
     * @return The root directory.
     */
    public Directory getRoot() {
        return root;
    }
}
