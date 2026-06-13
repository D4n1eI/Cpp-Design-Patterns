template <typename T>
struct Property{
    T value;
    Property(T value){
        *this = value;
    }


    operator T(){
        return value;
    }

    T operator =(T new_value){

        std::cout <<"Assignment";
        return value = new_value;
    }
};


struct Creature{
    Property<int> strength{10};
    Property<int> agility{15};

};

int main(){
    Creature c;
    c.strength=15;
    auto x = c.agility;
    return 0;
}