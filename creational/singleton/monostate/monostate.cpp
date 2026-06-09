class Printer
{
    static int id;

public:
    int get_id() const { return id; };
    void set_id(int id)
    {
        this->id = id;
    }
};





int main(){

    Printer p;
    int p = p.get_id();

    Printer p2;

    return 0;
}