#include <iostream>

struct Renderer
{
    virtual void render_circle(float x, float y, float radius) = 0;
};

struct RasterRenderer : public Renderer
{
    virtual void render_circle(float x, float y, float radius) override
    {
        std::cout << "Rasterizing a circle of radius " << radius << std::endl;
    }
};

struct VectorRenderer : public Renderer
{
    virtual void render_circle(float x, float y, float radius) override
    {
        std::cout << "Rasterizing a vector circle of radius " << radius << std::endl;
    }
};

struct Shape
{
protected:
    Renderer &renderer;

    Shape(Renderer &renderer) : renderer{renderer}
    {
    }

public:
    virtual void draw() = 0;
    virtual void resize(float factor) = 0;
};

struct Circle : Shape
{
    float x, y, radius;

    Circle(Renderer &renderer, float x, float y, float radius)
        : Shape(renderer), x{x}, y{y}, radius{radius}
    {
    }

    virtual void draw() override
    {
        renderer.render_circle(x, y, radius);
    }

    virtual void resize(float factor) override
    {
        radius *= factor;
    }
};

int main()
{
    RasterRenderer rr;
    Circle raster_circle{rr, 5, 5, 5};
    raster_circle.draw();
    raster_circle.resize(4);
    raster_circle.draw();
    return 0;
}