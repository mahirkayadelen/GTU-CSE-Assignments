import java.util.Scanner;
import java.util.Random;

public class driver2 {
    public static void main(String args[]){
        

        int x,y;
        int endctr = 0;
        Scanner input = new Scanner(System.in);
        do{
            System.out.print("Please enter the dimensions of the board (first input column, second input row)");
            x = input.nextInt();
            y = input.nextInt();
        }while(x<0 || y<0 );

        System.out.println("Game starting..");
        try { // for sleep 2 sec
            Thread.sleep(2000);
        } 
        catch (InterruptedException e) {
            e.printStackTrace();
        }

        Tetris mytetris = new Tetris(x,y);
        mytetris.Draw();

        while(endctr <= (x-2)){
            char tetroinp;
            System.out.println("Tetromino type (I, O, T, J, L, S, Z).You may enter R for random Tetromino, Q for quit. : ");
            tetroinp =  input.next().charAt(0);
            if(tetroinp == 'Q')
                return;

            else if(tetroinp != 'I' && tetroinp != 'O' && tetroinp != 'T' && tetroinp != 'J' && tetroinp != 'L' && tetroinp != 'S' && tetroinp != 'Z' && tetroinp != 'R'){
                System.out.println("Wrong input please try again.");
                continue;
            }
            if(tetroinp == 'R'){
                Random rand = new Random();
                char[] letters = {'I', 'O', 'T', 'J', 'S', 'L', 'Z'};
                int randomIndex = rand.nextInt(letters.length);
                char randomChar = letters[randomIndex];
                tetroinp = randomChar;
            }
            mytetris.Add(tetroinp);
            if(mytetris.gettetrosvector().get(mytetris.gettotal()-1).getcol() + mytetris.getbottomc() > x-1)
                break;
            mytetris.Animate();
        }
        System.out.println("Game over..");
    }
}
