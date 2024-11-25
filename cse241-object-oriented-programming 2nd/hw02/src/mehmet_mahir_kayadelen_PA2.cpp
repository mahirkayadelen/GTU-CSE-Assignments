#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

class Image_Editor{
    public:
        Image_Editor(){ // default constructor
            img_height = 0;
            img_width = 0;
            imgctr = 0;
            img_maxvalue = 255; // default value
            menu();
        }; 
        char open_image(); // opens image reads and fills RGB values to the vector fills image sizes 
        char save_image(); // saves the final image
        char convert_grayscale(); // script for convert grayscale with user inputs coefficients
        void menu(); // editor main menu

    private:
        string img_name; // opened image name
        int img_height; //height of the opened image
        int img_width; // width of the opened image
        int img_maxvalue; // max RGB value of the opened image
        int imgctr; // opened image counter for this assignment it will always 1 
        vector<vector<int>> img_pixels; // vector filled with color numbers


};

char Image_Editor::convert_grayscale(){
    char select;
    float c_r,c_g,c_b; // channel coefficients
    int newvalue; // new calculated RGB value with grayscale formula
    do{
        cout << "CONVERT TO GRAYSCALE MENU\n";
        cout << "0 - UP\n1 - Enter Coefficients For RED GREEN And BLUE Channels.\n";
        cin >> select;
        if(select == '0'){
            return 4; // if user wants to upper menu func returns 4
        }
        else if(select == '1'){
            cin >> c_r >> c_g >> c_b;
            if(cin.fail()){ // if user enters  invalid inp
                cin.clear();
                cin.ignore(100,'\n');
            }
            if(!((c_r >=0 && c_r <1) && (c_g >=0 && c_g <1) && (c_b >=0 && c_b <1)) || cin.fail()){ // control float numbers are in the range [0,1)
                do{
                    cin.clear();
                    cin.ignore(100,'\n');
                    cout << "Coefficients must be  in range [0,1) Please Try Again."<<endl;
                    cin >> c_r >> c_g >> c_b;
                }while(!((c_r >=0 && c_r <1) && (c_g >=0 && c_g <1) && (c_b >=0 && c_b <1)));
            }

            for(int i = 0;i<img_height;i++){
                for(int j = 0;j<(img_width)*3;j+=3){
                    newvalue = (img_pixels[i][j] * c_r) + (img_pixels[i][j+1] * c_g) + (img_pixels[i][j+2] * c_b);
                    if(newvalue > img_maxvalue)
                        newvalue = img_maxvalue;
                    img_pixels[i][j+2] = img_pixels[i][j+1] = img_pixels[i][j] = newvalue;
                }
            }
            select = '4'; // for displaying menu again
        }
    }while(!(select == '0' || select == '1'));
    return 0;
}

char Image_Editor::save_image(){
    char select;
    do{
        cout << "SAVE IMAGE DATA MENU\n";
        cout << "0 - UP\n1 - Enter A File Name\n";
        cin >> select;
        if(select == '0'){
            return '4'; // if user wants to upper menu func returns 4
        }
        else if(select == '1'){
            cin >> img_name;
            ofstream newfile(img_name); // open file as given from user
            string str_height,str_width_str_maxvalue;
            newfile << "P3\n";
            newfile << img_height << " " << img_width <<endl << img_maxvalue <<endl;
            for(int i = 0;i<img_height;i++){
                for(int j = 0;j<(img_width)*3;j++){
                    newfile << img_pixels[i][j] << " ";
                    if((j+1) % 3 == 0 && j != 0)
                        newfile << "  ";
                }
                newfile << endl;
            }
            select = 4;
            newfile.close();
        }
    }while(!(select == '0' || select == '1'));

    return 0;
}

char Image_Editor::open_image(){
    char select;
    do{
        cout << "OPEN AN IMAGE MENU\n";
        cout << "0 - UP\n1 - Enter The Name Of The Image File\n";
        cin >> select;
        if(select == '0'){
            return '4'; // if user wants to upper menu func returns 4
        }
        else if(select == '1'){ // opens image
            cin >> img_name; // takes imagename for open from user
            imgctr++; 

            ifstream infile(img_name,ios::in);
            if(!infile){ // If filename wrong or sth.
                cout << "Error opening file."<<endl;
                return 1;
            }

            string type,str_height,str_width,str_maxvalue; 
            infile >> type;
            infile >> str_height;
            infile >> str_width;
            infile >> str_maxvalue;

            img_height = stoi(str_height); // converting written height to integer
            img_width = stoi(str_width); // converting written width to integer
            img_maxvalue = stoi(str_maxvalue); // converting written maxvalue to integer

            vector<vector<int>> pixels(img_height,vector<int>(img_width*3)); // open new vector height by width size
            for(int i = 0;i<img_height;i++){ // fill vector with rgb values of image
                for(int j = 0;j<(img_width*3);j++){
                    string str_value;
                    infile >> str_value;
                    int value = stoi(str_value); // int value of rgb value
                    pixels[i][j] = value;
                }
            }
            img_pixels = pixels; 
            infile.close(); // close img file
            select = '4'; // for displaying menu again
            continue; // for avoid error message "wrong choise"
        }
    }while(!(select == '0' || select == '1'));

    return 0;
}


void Image_Editor::menu(){
    char select;
    do{
        cout << "MAIN MENU\n";
        cout << "0 - Exit\n1 - Open An Image(D)\n2 - Save Image Data(D)\n3 - Scripts(D)\n";
        cin >> select;
        if( select == '0')
            return;
        else if(select == '1'){
            select = open_image(); 
        }
        else if( select == '2'){
            select = save_image();
        }
        else if(select == '3'){
            select = convert_grayscale();
        }
    }while(select <'0'  || select >'3');
    
}

int main(){
    Image_Editor editor;
    // editor.menu();
    
    return 0;
}