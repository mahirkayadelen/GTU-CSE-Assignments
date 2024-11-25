

public class Player extends basePW {

    public Player() {  //  Default Constructor
        super();
    }

    public Player(String playerName) {   //  One Parameter Constructor 
        super(playerName);
    }

    public mediaBase currently_playing() {      //  Returns currently playing object
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
    
    @Override
    public void next(String mediaType) {
        if (mediaType == "audio" || mediaType == "video") {   //  Checking if the type is valid
            if (this.current < medias.size() - 1) { //  Checking if there are any objects to skip to
                for (int i = this.current + 1; i < medias.size(); ++i) {
                    String classType = medias.get(i).getClass().toString();   //  Getting the current class's type
                    for (int j = 0; j < classType.length(); ++j) {
                        if (classType.charAt(j) == '.') { //  Splitting the string into 2 from the '.' because we only need after '.'
                            ++j;
                            if (classType.charAt(j) == mediaType.charAt(0)) //  If the type of one of the next objects is same with type string then that object will be currentlyPlaying object.
                            {                                    
                                this.current = i;                
                                return;
                            }
                        }
                    }
                }
                System.out.println("Couldn't find that type among the next tracks.");
            } else {
                System.out.println("Can't skip to next one because playlist has ended.");
            }
        } else {
            System.out.println("Type is wrong.");
        }

    }

    @Override
    public void previous(String mediaType) {
        if (mediaType == "audio" || mediaType == "video") {
            if (this.current > 0) {     //  if current object has 0 index then there's no previous objects
                for (int i = this.current - 1; i >= 0; --i) {
                    String classType = medias.get(i).getClass().toString();   //  Getting the class's type
                    for (int j = 0; j < classType.length(); ++j) {
                        if (classType.charAt(j) == '.') { //  Splitting the string into 2 from the '.' because we only need after '.'
                            ++j;
                            if (classType.charAt(j) == mediaType.charAt(0)) //  If the type of one of the next objects is same with type string then that object will be currentlyPlaying object.
                            {                                    
                                this.current = i;                
                                return;
                            }
                        }
                    }
                }
                System.out.println("Couldn't find that type previous the next tracks.");
            } else {
                System.out.println("Can't go back to previous one because playlist has just started.");
            }
        } else {
            System.out.println("Type is wrong!");
        }

    }
}
