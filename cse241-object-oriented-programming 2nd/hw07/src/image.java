

public class image extends mediaBase implements visual, nonPlayable {
    //  Image objects  are inherited from mediaBase.
    //  They are nonplayable and visual.
    
    private int imgHeight; //  Holds height of image
    private int imgWidth;  //  Holds width of image
    
    public image() {   //  Default Constructor
        super();
        imgHeight = 0;
        imgWidth = 0;
    }

    public image(String name, int height, int width) { //  Three Paramater Constructor
        super(name);
        this.imgHeight = height;
        this.imgWidth = width;
    }
    
    @Override
    public int getHeight()  //  Getter for Height
    {
        return this.imgHeight;
    }
    
    @Override
    public int getWidth()   //  Getter for Width
    {
        return this.imgWidth;
    }
    
    @Override
    public void setHeight(int height)   //  Setter for Height
    {
        if(height > 0)
            this.imgHeight = height;
    }
    
    @Override
    public void setWidth(int width) //  Setter for Width
    {
        if(width > 0)
            this.imgWidth = width;
    }
    
    public double getAspectRatio()  //  Return Aspect Ratio
    {
        try
        {
            return (double) imgHeight / imgWidth;  //  Returns aspect ratio
        }
        catch(Exception e)
        {
            return 0;   //  if width is 0 returns 0
        }
    }
    
    @Override
    public void info() {
        System.out.println(name + " " + imgHeight + " " + imgWidth + " " + getAspectRatio() + "\n"); 
    }
}
