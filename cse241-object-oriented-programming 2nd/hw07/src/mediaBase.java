

public class mediaBase {    //  Base for text,image,video and audio

    protected String name;  

    public mediaBase() {   //  Default Constructor
        name = "nameNULL";
    }

    public mediaBase(String newName) {    //  One Parameter Constructor
        this.name = newName;
    }

    public String getName() {   //  Getter for Name
        return name;
    }

    public void setName(String newName) {  //  Setter for Name
        this.name = newName;
    }
    
    @Override
    public String toString() {
        return this.name;
    }
}