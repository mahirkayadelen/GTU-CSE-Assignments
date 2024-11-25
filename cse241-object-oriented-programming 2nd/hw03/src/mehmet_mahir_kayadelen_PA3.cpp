#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

class ppmImage; // for use object as a argument in read_ppm

int read_ppm(const string source_ppm_filename,ppmImage& destination_object); // for use read_ppm function in my constructor
int write_ppm(const string destination_ppm_file_name, const ppmImage& source_object); // for use in member function ppm_write()

class ppmImage{
    public:
        ppmImage(const string source_ppm_file_name){ // creates image according to ppm file given as argument
            read_ppm(source_ppm_file_name,*this);
        }


        ppmImage(int in_height, int in_width){ // creates image according to the given dimensions
            img_pixels = vector<vector<int>>(in_height,vector<int>(in_width*3));
            for(int i = 0;i<in_height;i++){ // fill white pixels
                for(int j = 0;j<in_width;j++){
                    img_pixels[i][j] = 255;
                }
            }
            img_height = in_height;
            img_width = in_width;
            img_maxvalue = 255;
            img_type = "P3";

        }
        
        ppmImage(){ // default constructor
            img_height = 0;
            img_width = 0;
            img_maxvalue = 255; // default value
            img_type = "P3";
        }
        int change_pixel(int row,int column,int channel,int value);
        int ppm_read(const string source_ppm_file_name);
        int ppm_write(const string destination_ppm_file_name);

        int setHeight(int height);
        int setWidth(int width);
        int setMaxvalue(int maxvalue);
        int setType(string type);
        int setVector(vector<vector<int>> pixels);
        vector<vector<int>>& changeVector(){ return img_pixels;}

        void getpixel(int height,int width) const;
        void getdimensions ()const;
        int getHeight() const{ return img_height;}
        int getWidth() const{ return img_width;}
        int getMaxvalue() const{ return img_maxvalue;}
        vector<vector<int>> getVector() const{ return img_pixels;}
        string getType()const{ return img_type;}

        friend ostream& operator<<(ostream& out,ppmImage& image);
        ppmImage operator+(const ppmImage& img1);
        ppmImage operator-(const ppmImage& img1);
        int& operator()(int row,int column,int channel);
    private:
        string img_type;
        int img_height; //height of the opened image
        int img_width; // width of the opened image
        int img_maxvalue; // max RGB value of the opened image
        vector<vector<int>> img_pixels; // vector filled with color numbers

};

int ppmImage::change_pixel(int row,int column,int channel,int value){
    if(value >=0 && value <= getMaxvalue()){
        (*this)(1,1,1) = value;
        return 1;
    }
    else
       return 0;
}


int ppmImage::ppm_write(const string destination_ppm_file_name){
    if(write_ppm(destination_ppm_file_name,*this) == 0){
        cout << "Failed to write!" << endl;
        return 0;
    }
    return 1;
}


int ppmImage::ppm_read(const string source_ppm_file_name){
    if(read_ppm(source_ppm_file_name,*this) == 0){
        cout << "Failed to read, check filename!" << endl;
        return 0;
    }
    return 1;
}

void ppmImage::getpixel(int height,int width) const{
    ppmImage temp(height,width);
    temp.img_pixels = this->getVector();
    if(height<0 ||  height > getHeight() || width < 0 || width > getWidth() ){
        cout << "Fault pixel location!" << endl;
    }
    else{
        cout << "RGB values of pixel(" << height << "," << width <<")" <<  endl;
        cout << "red:" << temp(height,width,1) << " green:" << temp(height,width,2) << " blue:" << temp(height,width,3) << endl; 
    }
}


int& ppmImage::operator()(int row,int column,int channel){
    if(row >= 1 && row <= getHeight() && column >= 1 && column <=(getWidth()) && (channel == 1 || channel == 2 || channel == 3)){
        if(channel == 1) // red
            return img_pixels[row-1][(column*3-3)];
        else if(channel == 2) // green
            return img_pixels[row-1][(column*3)-2];
        else // blue
            return img_pixels[row-1][(column*3)-1];
    }
    else
        cout << "Usage fault. returned first index.";
    return img_pixels[0][0];
}

ppmImage ppmImage::operator+(const ppmImage& img1){
    ppmImage temp;
    if(!(img1.getHeight() == getHeight() && img1.getWidth() == getWidth())) // image dimensions are not same return default.
        return temp;
    
    temp.setHeight(getHeight());
    temp.setWidth(getWidth());
    vector<vector<int>> pixels(getHeight(),vector<int>(getWidth()*3)); // open new vector height by width size
    for(int i = 0;i<getHeight();i++){ // fill vector with rgb values of image
        for(int j = 0;j<(getWidth()*3);j++){
            int value = getVector()[i][j] + img1.getVector()[i][j];
            if(value >getMaxvalue())
                value = 255;
            pixels[i][j] = value;
        }
    }
    temp.img_pixels = pixels;
    return temp;
}

ppmImage ppmImage::operator-(const ppmImage& img1){
    ppmImage temp;
    if(!(img1.getHeight() == getHeight() && img1.getWidth() == getWidth())) // image dimensions are not same return default.
        return temp;
    temp.setHeight(getHeight());
    temp.setWidth(getWidth());
    vector<vector<int>> pixels(getHeight(),vector<int>(getWidth()*3)); // open new vector height by width size
    for(int i = 0;i<getHeight();i++){ // fill vector with rgb values of image
        for(int j = 0;j<(getWidth()*3);j++){
            int value = abs(getVector()[i][j] - img1.getVector()[i][j]);
            if(value >getMaxvalue())
                value = 255;
            pixels[i][j] = value;
        }
    }
    temp.img_pixels = pixels;
    return temp;
}


ostream& operator<<(ostream& out,ppmImage& image){
    out << image.img_type << endl << image.img_height << " " << image.img_width << endl;
    
    for(int i = 0;i<image.getHeight();i++){
        for(int j = 0;j<(image.getWidth())*3;j++){
            out << image.getVector()[i][j] << " ";
            if((j+1) % 3 == 0 && j != 0)
                out << "  ";
        }
        out << endl;
    }
    return out;
}

int ppmImage::setHeight(int height){
    if(!(height >= 0 && height <=img_maxvalue)){
        return -1;
    }
    else 
        img_height = height;
    return 0; // all is good
}

int ppmImage::setWidth(int width){
    if(!(width >= 0 && width <=img_maxvalue)){
        return -1;
    }
    else 
        img_width = width;
    return 0; // all is good
}

int ppmImage::setMaxvalue(int maxvalue){
    if(!(maxvalue >= 0 && maxvalue <=255)){
        return -1;
    }
    else 
        img_maxvalue = maxvalue;
    return 0; // all is good
}

int ppmImage::setType(string type){
    if(!(type == "P3")){
        return -1;
    }
    else 
        img_type = type;
    return 0; // all is good
}
int ppmImage::setVector(vector<vector<int>> pixels){
    img_pixels = pixels;
    return 1;
}

 


void ppmImage::getdimensions() const{
    cout << "Width:" << img_height << ", Height:" << img_width << endl;
}

int read_ppm(const string source_ppm_filename,ppmImage& destination_object){
    ifstream infile(source_ppm_filename,ios::in);
    if(!infile){ // If filename wrong or sth.
        cout << "Error opening file."<<endl;
            return 0;
    }

    string type,str_height,str_width,str_maxvalue; 
    infile >> type;
    infile >> str_height;
    infile >> str_width;
    infile >> str_maxvalue;

    if(destination_object.setType(type) != 0){// converting written maxvalue to integer
        cout << "type is not legal! it should be P3 " << endl;
        return 0;
    } 

    if(destination_object.setMaxvalue(stoi(str_maxvalue)) != 0){// converting written maxvalue to integer
        cout << "maxvalue is not legal! it should be 0<mv<255" << endl;
        return 0;
    } 
    if(destination_object.setHeight(stoi(str_height)) != 0){// converting written height to integer
        cout << "height is not legal!" << endl;
        return 0;
    }
    if(destination_object.setWidth(stoi(str_width))){ // converting written width to integer
        cout << "width is not legal!" << endl;
        return 0;
    }

    vector<vector<int>> pixels(destination_object.getHeight(),vector<int>(destination_object.getWidth()*3)); // open new vector height by width size
    for(int i = 0;i<destination_object.getHeight();i++){ // fill vector with rgb values of image
        for(int j = 0;j<(destination_object.getWidth()*3);j++){
            string str_value;
            infile >> str_value;
            int value = stoi(str_value); // int value of rgb value
            pixels[i][j] = value;
        }
    }
    destination_object.setVector(pixels);
    infile.close();

    return 1;
}

int write_ppm(const string destination_ppm_file_name, const ppmImage& source_object){
    ofstream newfile(destination_ppm_file_name); // open file as given from user
    string str_height,str_width_str_maxvalue;
    newfile << "P3\n";
    newfile << source_object.getHeight() << " " << source_object.getWidth()  <<endl << source_object.getMaxvalue()  <<endl;
    for(int i = 0;i<source_object.getHeight();i++){
        for(int j = 0;j<(source_object.getWidth())*3;j++){
            newfile << source_object.getVector()[i][j] << " ";
            if((j+1) % 3 == 0 && j != 0)
                newfile << "  ";
        }
        newfile << endl;
    }
    newfile.close();
    return 1;
}


int test_print(const string filename_image1){
    ppmImage img;
    if(read_ppm(filename_image1,img) != 1){
        cout << "cannot read file!" << endl;
        return 0;
    };

    cout << img.getType() << endl << img.getHeight() << " " << img.getWidth() << endl;

    for(int i = 0;i<img.getHeight();i++){
        for(int j = 0;j<(img.getWidth())*3;j++){
            cout << img.getVector()[i][j] << " ";
            if((j+1) % 3 == 0 && j != 0)
                cout << "  ";
        }
        cout << endl;
    }
    return 1;
}

int swap_channels(ppmImage& image_object_to_be_modified, int swap_choice){
    int tempvalue;
    if(swap_choice == 1){ // swaps red and green
        for(int i = 1;i<=image_object_to_be_modified.getHeight();i++){ // fill vector with rgb values of image
            for(int j = 1;j<=image_object_to_be_modified.getWidth();j++){
                tempvalue = image_object_to_be_modified(i,j,1);
                image_object_to_be_modified(i,j,1) = image_object_to_be_modified(i,j,2);
                image_object_to_be_modified(i,j,2) = tempvalue;
            }
        }
        return 1;
    }
    else if(swap_choice == 2){ // swaps red and blue
        for(int i = 1;i<=image_object_to_be_modified.getHeight();i++){ // fill vector with rgb values of image
            for(int j = 1;j<=image_object_to_be_modified.getWidth();j++){
                tempvalue = image_object_to_be_modified(i,j,1);
                image_object_to_be_modified(i,j,1) = image_object_to_be_modified(i,j,3);
                image_object_to_be_modified(i,j,3) = tempvalue;
            }
        }
        return 1;
    }
    else if(swap_choice == 3){ // swaps green and blue
        for(int i = 1;i<=image_object_to_be_modified.getHeight();i++){ // fill vector with rgb values of image
            for(int j = 1;j<=image_object_to_be_modified.getWidth();j++){
                tempvalue = image_object_to_be_modified(i,j,2);
                image_object_to_be_modified(i,j,2) = image_object_to_be_modified(i,j,3);
                image_object_to_be_modified(i,j,3) = tempvalue;
            }
        }
        return 1;
    }
    else // no swap
        return 1;
}

ppmImage single_color(const ppmImage& source, int color_choice){
    ppmImage newimage(source.getHeight(),source.getWidth());
    
    if(color_choice == 1){ // red channel is preserved
        for(int i = 1;i<=source.getHeight();i++){ // fill vector with rgb values of image
            for(int j = 1;j<=source.getWidth();j++){
                newimage(i,j,1) = source.getVector()[i-1][(j-1)*3];
                // cout << source.getVector()[i-1][(j-1)*3];
                newimage(i,j,2) = 0;
                newimage(i,j,3) = 0;
            }
        }
    }
    else if(color_choice == 2){ // green channel is preserved
        for(int i = 1;i<=source.getHeight();i++){ // fill vector with rgb values of image
            for(int j = 1;j<=source.getWidth();j++){
                newimage(i,j,2) = source.getVector()[i-1][((j-1)*3) + 1];
                // cout << source.getVector()[i-1][(j-1)*3];
                newimage(i,j,1) = 0;
                newimage(i,j,3) = 0;
            }
        }
    }
    else if(color_choice == 3){
        for(int i = 1;i<=source.getHeight();i++){ // fill vector with rgb values of image
            for(int j = 1;j<=source.getWidth();j++){
                newimage(i,j,3) = source.getVector()[i-1][((j-1)*3) + 2];
                // cout << source.getVector()[i-1][(j-1)*3];
                newimage(i,j,1) = 0;
                newimage(i,j,2) = 0;
            }
        }
    }
    return newimage;
}

int test_addition(const string filename_image1, const string filename_image2, const string filename_image3){
    ppmImage img1,img2,img3;
    if(read_ppm(filename_image1,img1) == 0 || read_ppm(filename_image2,img2) == 0 ){
        cout << "error while reading " <<  filename_image1 << "or " << filename_image2  << endl;
        return 0;
    }
    img3 = img1 + img2;

    if(write_ppm(filename_image3,img3) == 0){
        cout << "error while writing to" << filename_image3 << endl;
        return 0 ;
    }
    return 1;
}

int test_substraction(const string filename_image1, const string filename_image2, const string filename_image3){
    ppmImage img1,img2,img3;
    if(read_ppm(filename_image1,img1) == 0 || read_ppm(filename_image2,img2) == 0 ){
        cout << "error while reading " <<  filename_image1 << "or " << filename_image2  << endl;
        return 0;
    }
    img3 = img1 - img2;
    if(write_ppm(filename_image3,img3) == 0){
        cout << "error while writing to" << filename_image3 << endl;
        return 0 ;
    }
    return 1;
}

int main(int argc,char** argv){
    if(argc <= 1){
        cout << "missing arguments!" << endl;
        return 0 ;
    }

    if(argv[1][0] == '1'){
        if(argc == 5){
            test_addition(argv[2],argv[3],argv[4]);
            return 1;
        }
        else
            return 0;
    }
    else if(argv[1][0] == '2'){
        if(argc == 5){
            test_substraction(argv[2],argv[3],argv[4]);
            return 1;
        }
        else
            return 0;
    }
    else if(argv[1][0] == '3'){
        if(argc == 4){
            ppmImage img;
            read_ppm(argv[2],img);
            swap_channels(img,2); // swap red and blue channels
            write_ppm(argv[3],img);
            return 1;
        }
        else
            return 0;
    }
    else if(argv[1][0] == '4'){
        if(argc == 4){
            ppmImage img;
            read_ppm(argv[2],img);
            swap_channels(img,3); // swap green and blue channels
            write_ppm(argv[3],img);
            return 1;
        }
        else
            return 0;
    }
    else if(argv[1][0] == '5'){
        if(argc == 4){
            ppmImage img;
            read_ppm(argv[2],img);
            img = single_color(img,1);
            write_ppm(argv[3],img);
        }
        else
            return 0;
    }
    else if(argv[1][0] == '6'){
        if(argc == 4){
            ppmImage img;
            read_ppm(argv[2],img);
            img = single_color(img,2);
            write_ppm(argv[3],img);
        }
        else
            return 0;
    }
    else if(argv[1][0] == '7'){
        if(argc == 4){
            ppmImage img;
            read_ppm(argv[2],img);
            img = single_color(img,3);
            write_ppm(argv[3],img);
        }
        else
            return 0;
    }
    else{
        cout << "Invalid arguments!" << endl;
        return 0;
    }
}