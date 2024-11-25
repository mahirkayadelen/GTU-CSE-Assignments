

import java.util.ArrayList;
import java.util.ArrayList;
import java.util.List;

public class dataset {

    private final List<basePW> observers = new ArrayList<>();  //  Holds the observers
    private final List<mediaBase> mediaObjects = new ArrayList<>();   //  Holds the media objects
    
    public void register(basePW newObserver) {    
        boolean isPresent = true;
        for (basePW i : observers) //  Checking if the player or viewer is already in the list
        {
            if (newObserver == i) {
                isPresent = false;
                break;
            }
        }
        if (isPresent) {
            observers.add(newObserver);
            for(mediaBase i : mediaObjects)
            {
                if(observers.get(observers.size()-1) instanceof Player && i instanceof playable)
                    observers.get(observers.size()-1).add(i);
                else if(observers.get(observers.size()-1) instanceof Viewer && i instanceof nonPlayable)
                    observers.get(observers.size()-1).add(i);
            }
                
        }   
    }

    public void remove_observer(Player observerToRemove) {
        observers.remove(observerToRemove);   //  Removes observer from arraylist
    }

    public void add(mediaBase newMedia) {     //  Adds new obj to arraylist , player and viewers

        for(mediaBase i : mediaObjects)   // Doesn't add media to array if it already exists
            if(i == newMedia)
               return;
            
        mediaObjects.add((newMedia));   //  adds to arraylist
        for (basePW i : observers) {   // adds playable to players and nonplayables to viewers
            if (newMedia instanceof playable && i instanceof Player) {
                i.add(newMedia);
            }else if(newMedia instanceof nonPlayable && i instanceof Viewer)
            {
                i.add(newMedia);
            }
        }
    }

    public void remove(baseInterface mediaInterface)   //  Removes objects from observers
    {
        for(basePW i: observers)
            if(mediaInterface instanceof playable && i instanceof Player) 
                i.remove((mediaBase)mediaInterface);
            else if (mediaInterface instanceof nonPlayable && i instanceof Viewer)
                i.remove((mediaBase)mediaInterface);
            
    }
    @Override
    public String toString() {
        String result = "";
        for (basePW i : observers) {
            result += i.getName() + "\n";
        }
        return result;
    }
}
