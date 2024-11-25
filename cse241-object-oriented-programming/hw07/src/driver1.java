import java.util.Scanner;

public class driver1{
    public static void main(String args[]){
        char see = 'S';
        Tetromino mytetro = new Tetromino(see);
        Tetris mytetris = new Tetris(10,10);
        System.out.println("draw function of Tetris:");
        mytetris.Draw();

        System.out.println("Adding tetromino with add function and after draw board:");
        mytetris.Add('J');
        mytetris.Draw();

        System.out.print("Press enter any character to see animate function");
            Scanner input = new Scanner(System.in);
            System.out.print("Enter a character: ");
            char c = input.nextLine().charAt(0);
        System.out.println("Animate function:");
        mytetris.Animate();
        System.out.println("(+)tetris Fit function and  after Draw:");
        mytetris.Fit();
        mytetris.Draw();
        System.out.println("Animate function:");
        mytetris.Animate();
    }
}