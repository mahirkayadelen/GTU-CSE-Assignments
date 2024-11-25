

public class video extends mediaBase implements visual, playable {
    //  Video objects are inherited from mediaBase.
    //  They are playable and visual.
    
    private int videoHeight;
    private int videoWidth;
    private double videoDuration;
    
    public video() {
        super();
    }

    public video(String videoName, int videoHeight, int videoWidth, double videoDuration) {
        super(videoName);
        if(videoHeight > 0 && videoWidth > 0 && videoDuration > 0)
        {
            this.videoHeight = videoHeight;
            this.videoWidth = videoWidth;
            this.videoDuration = videoDuration;
        }
    }

    @Override
    public void info() {
        System.out.println(name + " " + videoHeight + " " + videoWidth + " " + getAspectRatio() + " " + videoDuration + "\n"); 
    }
    
    @Override
    public int getHeight()
    {
        return videoHeight;
    }
    
    @Override
    public int getWidth()
    {
        return videoWidth;
    }
    
    @Override
    public void setHeight(int newHeight)
    {
        this.videoHeight = newHeight;
        if(newHeight > 0)
            this.videoHeight = newHeight;
    }
    
    @Override
    public void setWidth(int newWidth)
    {
        this.videoWidth = newWidth;
        if(newWidth > 0)
            this.videoWidth = newWidth;
    }
    
    @Override
    public double getDuration()
    {
        return videoDuration;
    }
    
    @Override
    public void setDuration(double newDuration)
    {
        if(newDuration > 0)
            this.videoDuration = newDuration;
    }
    
    @Override
    public double getAspectRatio()
    {
        try
        {   
            return videoHeight/videoWidth;
        }
        catch(Exception e)
        {
            return 0;
        }
    }
}
