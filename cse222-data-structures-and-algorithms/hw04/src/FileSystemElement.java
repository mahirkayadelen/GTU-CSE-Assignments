/**
 * The FileSystemElement class is an abstract class representing a file system element,
 * which can be either a file or a directory. It provides common attributes and methods
 * for managing file system elements, such as name, creation date, parent directory,
 * and methods for printing the element's name and printing the name with a timestamp.
 */
import java.sql.Timestamp;

public abstract class FileSystemElement {
    protected String name;
    protected Timestamp dateCreated;
    protected FileSystemElement parent;

    /**
     * Constructs a new FileSystemElement object with the specified name and parent element.
     *
     * @param name    The name of the file system element.
     * @param parent  The parent element (directory) of the file system element.
     */
    public FileSystemElement(String name, FileSystemElement parent) {
        this.name = name;
        this.parent = parent;
        this.dateCreated = new Timestamp(System.currentTimeMillis());
    }

    /**
     * Retrieves the name of the file system element.
     *
     * @return The name of the file system element.
     */
    public String getName() {
        return name;
    }

    /**
     * Retrieves the creation date of the file system element.
     *
     * @return The creation date of the file system element.
     */
    public Timestamp getDateCreated() {
        return dateCreated;
    }

    /**
     * Retrieves the parent directory of the file system element.
     *
     * @return The parent directory of the file system element.
     */
    public FileSystemElement getParent() {
        return parent;
    }

    /**
     * Sets the parent directory of the file system element.
     *
     * @param parent The parent directory to be set.
     */
    public void setParent(FileSystemElement parent) {
        this.parent = parent;
    }

    /**
     * Abstract method to print the name of the file system element.
     *
     * @param prefix The prefix to prepend to the element's name when printing.
     */
    public abstract void print(String prefix);

    /**
     * Abstract method to print the name of the file system element along with its timestamp.
     *
     * @param prefix The prefix to prepend to the element's name when printing.
     */
    public abstract void printWithTimestamp(String prefix);
}
