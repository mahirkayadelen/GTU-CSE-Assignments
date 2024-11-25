

public class text extends mediaBase implements nonVisual, nonPlayable {
    //  Text objects are inherited from mediaBase.
    //  They are nonplayable and nonvisual.
    public text() {
        super();
    }

    public text(String textName) {
        super(textName);
    }

    @Override
    public void info() {
        System.out.println(super.toString()); 
    }
}