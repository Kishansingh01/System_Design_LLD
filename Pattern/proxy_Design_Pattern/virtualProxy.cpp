#include<iostream>
using namespace std;

class IImage{
    public:
        virtual void display()= 0;
        virtual ~IImage()= default;
};
class RealImage: public IImage{
    string filename;
    public:
        RealImage(string file){
            this->filename=file;
            // Heavy operation
            cout<<"[RealImage] Loading image from disk : "<<filename<< "/n";
        }
        void display() override {
            cout<<"[RealImage] displaying"<< filename << "\n";
        }
};
class ImageProxy : public IImage{
    RealImage* realImage;
    string filenmae;
    public:
        ImageProxy(string file){
            this->filenmae= file;
            realImage=nullptr;
        }
        void display() override{
            // Lazy initialization of real image
            if(!realImage){
                realImage= new RealImage(filename);
            }
            realImage->display()
        }
};
int main(){
    IImage* image1= new ImageProxy("sample.jpg");
}