

import java.util.ArrayList;
import java.util.List;


public class Viewer extends basePW {

    public Viewer() {  //  Default Constructor
        super();
    }

    public Viewer(String viewerName) {   //  One Parameter Constructor 
        super(viewerName);
    }

    @Override
    public void next(String mediaType) {
        if (mediaType == "text" || mediaType == "image") {    //  Checking if the type is valid
            if (this.current < medias.size() - 1) { //  Checking if there are any previous objects
                for (int index = this.current + 1; index < medias.size(); ++index) {
                    String className = medias.get(index).getClass().toString();   //  Getting the current class's type
                    for (int charIndex = 0; charIndex < className.length(); ++charIndex) {
                        if (className.charAt(charIndex) == '.') { //  Splitting the string into 2 from the '.'
                            ++charIndex;
                            if (className.charAt(charIndex) == mediaType.charAt(0)) {  //  If the type of one of the previous objects
                                this.current = index;                   //  object will be currentlyPlaying object.
                                return;
                            }
                        }
                    }
                }
                System.out.println("Couldn't find that type among the previous tracks.");
            } else {
                System.out.println("Can't skip to next one because playlist has ended.");
            }
        } else {
            System.out.println("Type is wrong.");
        }
    }

    @Override
    public void previous(String mediaType) {
        if (mediaType == "text" || mediaType == "image") {    //  Checking if the type is valid
            if (this.current > 0) {     //  Checking if there are any previous objects
                for (int index = this.current - 1; index >= 0; --index) {
                    String className = medias.get(index).getClass().toString();   //  Getting the current class's type
                    for (int charIndex = 0; charIndex < className.length(); ++charIndex) {
                        if (className.charAt(charIndex) == '.') { //  Splitting the string into 2 from the '.'
                            ++charIndex;
                            if (className.charAt(charIndex) == mediaType.charAt(0)) {  //  If the type of one of the previous objects
                                this.current = index;                   //  object will be currentlyPlaying object.
                                return;
                            }
                        }
                    }
                }
                System.out.println("Couldn't find that type among the previous tracks.");
            } else {
                System.out.println("Can't go back to previous one because playlist has just started.");
            }
        } else {
            System.out.println("Type is wrong!");
        }

    }
    
    public mediaBase currently_viewing() {      //  Returns currently playing object
        try
        {
            return medias.get(current);          
        }
        catch(Exception e)  //  If there are no currently playing object then method returns empty object
        {
            current = 0;    //  Also resets current
            return new mediaBase(); //  Return empty object
        }

    }
}
