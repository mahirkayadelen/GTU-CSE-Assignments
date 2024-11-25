/**
 * The Directory class represents a directory in the file system.
 * It extends the FileSystemElement class and provides methods for managing its children (files and directories),
 * printing its name along with the names of its children, and printing its name along with timestamps
 * for itself and its children.
 */
import java.util.LinkedList;
import java.util.List;

public class Directory extends FileSystemElement {
    private List<FileSystemElement> children;

    /**
     * Constructs a new Directory object with the specified name and parent element.
     *
     * @param name    The name of the directory.
     * @param parent  The parent element (directory) of the directory.
     */
    public Directory(String name, FileSystemElement parent) {
        super(name, parent);
        children = new LinkedList<>();
    }

    /**
     * Adds a child element (file or directory) to this directory.
     *
     * @param child The child element to be added.
     */
    public void addChild(FileSystemElement child) {
        children.add(child);
    }

    /**
     * Removes a child element (file or directory) from this directory.
     *
     * @param child The child element to be removed.
     */
    public void removeChild(FileSystemElement child) {
        children.remove(child);
    }

    /**
     * Retrieves the list of children (files and directories) of this directory.
     *
     * @return The list of children elements.
     */
    public List<FileSystemElement> getChildren() {
        return children;
    }

    /**
     * Prints the name of this directory along with the names of its children.
     *
     * @param prefix The prefix to prepend to the directory name.
     */
    @Override
    public void print(String prefix) {
        System.out.println(prefix + "* " + name + "/");
        for (FileSystemElement child : children) {
            child.print(prefix + "  ");
        }
    }

    /**
     * Prints the name of this directory along with its timestamp,
     * and recursively prints the names of its children along with timestamps.
     *
     * @param prefix The prefix to prepend to the directory name.
     */
    public void printWithTimestamp(String prefix) {
        String formattedTimestamp = dateCreated.toString().substring(0, dateCreated.toString().indexOf('.'));
        System.out.println(prefix + "* " + name + "/ (" + formattedTimestamp + ")");
        for (FileSystemElement child : children) {
            if (child instanceof Directory) {
                ((Directory) child).printWithTimestamp(prefix + "  ");
            } else {
                child.printWithTimestamp(prefix + "  ");
            }
        }
    }
}
