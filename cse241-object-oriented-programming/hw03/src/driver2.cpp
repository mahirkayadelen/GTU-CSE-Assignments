#include"tetris.h"
int main(){
    int isgameFinish = 0;
    srand(time(0));
    int x,y;
    int endctr=0;

    do {
        int a;
        cout << "Please enter the dimensions of the board (first input column, second input row)"<<endl;
        cin >> a;
        while(cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "\nBad entry.  Enter column again: ";
            cin >> a;
        }
        x = a;

        cin >> a;
        while(cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << "\nBad entry.  Enter row again: ";
            cin >> a;
        }
        y = a;
    }
    while (x<=0  ||y <=0);

    cout << "Game starting.."<<endl;
    sleep(1);

    Tetris mytetris(x,y);
    mytetris.Draw();
    //
    char inp;
    do{
        tetrominos temp;
        int isValidinp;
        do{
            cout <<"Please enter tetromino type (I, O, T, J, L, S, Z). You may enter R for random Tetromino, Q for quit: ";
            cin >> inp;
            if(inp != 'I' && inp != 'O' && inp != 'T' && inp != 'J' && inp != 'L' && inp != 'S' && inp != 'Z' && inp != 'R'  && inp != 'Q'){
                cout <<endl<< "Wrong input! please try again."<<endl;
                cin.ignore();
                isValidinp = 1;
            }
            else
                isValidinp = 0;
        }while(isValidinp);

        switch(inp){
            case 'I':
                temp = tetrominos::I;
                break;
            case 'O':
                temp = tetrominos::O;
                break;
            case 'T':
                temp = tetrominos::T;
                break;
            case 'J':
                temp = tetrominos::J;
                break;
            case 'L':
                temp = tetrominos::L;
                break;
            case 'S':
                temp = tetrominos::S;
                break;
            case 'Z':
                temp = tetrominos::Z;
                break;
            case 'R':
                inp = rand() % 7 + '0';
                if(inp == '0')
                    temp = tetrominos::I;
                else if(inp == '1')
                    temp = tetrominos::O;
                else if(inp == '2')
                    temp = tetrominos::T;
                else if(inp == '3')
                    temp = tetrominos::J;
                else if(inp == '4')
                    temp = tetrominos::L;
                else if(inp == '5')
                    temp = tetrominos::S;
                else if(inp == '6')
                    temp = tetrominos::Z;
                break;
            case 'Q':
                cout << "Exiting..";
                cout <<endl;
                sleep(1);
                return 1;
            default:
                cout << "Wrong input try again."<<endl;
                break;
        }
        Tetromino temptetro(temp);
        mytetris += temptetro;
        isgameFinish = mytetris.Animate(temptetro);

    }while(inp != 'Q' && isgameFinish);
}