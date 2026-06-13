
#include <string>
#include <iostream>
struct Image
{
    virtual void draw() = 0;
};

struct Bitmap : Image
{
    Bitmap(const std::string &filename)
    {
        std::cout << "Loading bitmap from " << filename;
    }

    void draw() override
    {
        std::cout << "Drawing Bitmap";
    }
};

struct LazyBitmap : Image
{

public:
    LazyBitmap(const std::string &filename) : filename{filename}
    {
    }

    void draw() override{
        if (!bmp){
            bmp = new Bitmap(filename);

        }
        bmp->draw();
    }

private:
    std::string filename;
    Bitmap * bmp{nullptr};
};
int main()
{
    LazyBitmap bmp{"pokemon.png"};
    bmp.draw(); 
}