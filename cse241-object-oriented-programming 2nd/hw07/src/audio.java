


public class audio extends mediaBase implements playable, nonVisual {   
    //  Audio objects  are inherited from mediaBase.
    //  They are playable and nonvisual.
    
    private double soundLength;   
    
    public audio() {   //  Default Constructor
        super();
    }

    public audio(String audioName, double soundLength) {   //  Two Parameter Constructor
        super(audioName);
        this.soundLength = soundLength;
    }

    @Override
    public void info() {    //  Prints info about object
        //  Prints name and duration
        System.out.println(name + " " + soundLength); 
    }
    
    @Override
    public double getDuration() //  Getter for Duration
    {
        return soundLength;
    }
    
    @Override
    public void setDuration(double soundLength)    //  Setter for Duration
    {
       this.soundLength = soundLength;
    }
    

}