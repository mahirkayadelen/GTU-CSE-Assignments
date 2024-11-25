

import java.util.ArrayList;
import java.util.List;

public abstract class basePW {  //  A base class for player and viewer

    protected int current = 0;  //  The index of current media object
    protected final List<mediaBase> medias = new ArrayList<>(); //  All objects that can be played or viewed
    protected String pwName;  //  Name of the player or viewer

    public basePW() {  //  Default Constructor
        pwName = "nameNULL";
    }

    public basePW(String pwName) {   //  One parameter constructor
        this.pwName = pwName;
    }

    public String getName() {   //  Getter for name
        return pwName;
    }

    public void setName(String pwName) {  //  Setter for name
        this.pwName = pwName;
    }

    public void add(mediaBase newMediaItem) {   //  Adds a new media object to playlist
        boolean alreadyExists = true;
        for (mediaBase i : medias) {    //  Checking if the object is already added or not
            if (i == newMediaItem) {
                alreadyExists = false;
            }
        }
        if (alreadyExists) { //  If the same object is not in the playlist then adding it to the playlist
            medias.add(newMediaItem);
            notifyAdd();
        }
    }

    public int getCurrent() {   //  Getter for current
        return current;
    }

    public void setCurrent(int current) {   //  Setter for current
        if (current >= 0 && this.current != current) {
            this.current = current;
        }
    }

    public void showList() {    //  Prints the current playlist
        for (mediaBase i : medias) {
            System.out.println(i);
        }
    }

    public abstract void next(String mediaType); //  Currently playing goes to next "type" object

    public abstract void previous(String mediaType);    //  Currently playing goes to previous "type" object

    public void remove(mediaBase mediaObj) //  Removes object from playlist
    {
        if (mediaObj == medias.get(current) && current == medias.size() - 1) {
            current = 0;    //  If the removed object is the last one playlist returns to first object
        }
        medias.remove(mediaObj); //  Remove Object 
        notifyRemove(); //  Notify User
    }

    private void notifyAdd() //  Notify user when an object has been added
    {
        System.out.println("Object added successfully.");
    }

    private void notifyRemove() //  Notify user when an object has been removed
    {
        System.out.println("Object removed successfully.");
    }
}
