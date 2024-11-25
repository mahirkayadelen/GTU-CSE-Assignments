/**
 * The File class represents a file in the file system.
 * It extends the FileSystemElement class and provides methods for printing the file's name,
 * and printing the file's name with its timestamp.
 */
public class File extends FileSystemElement {

    /**
     * Constructs a new File object with the specified name and parent element.
     *
     * @param name    The name of the file.
     * @param parent  The parent element (directory) of the file.
     */
    public File(String name, FileSystemElement parent) {
        super(name, parent);
    }

    /**
     * Prints the name of the file.
     *
     * @param prefix The prefix to prepend to the file name.
     */
    @Override
    public void print(String prefix) {
        System.out.println(prefix + name);
    }

    /**
     * Prints the name of the file along with its timestamp.
     *
     * @param prefix The prefix to prepend to the file name.
     */
    public void printWithTimestamp(String prefix) {
        String formattedTimestamp = dateCreated.toString().substring(0, dateCreated.toString().indexOf('.'));
        System.out.println(prefix + name + " (" + formattedTimestamp + ")");
    }
}
