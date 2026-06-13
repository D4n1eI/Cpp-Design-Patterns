#include <iostream>
#include <vector>

struct Neuron;
struct NeuronLayer;


template <typename Self>
struct SomeNeurons
{
    template <typename T>
    void connect_to(T& other);
};

struct Neuron : SomeNeurons<Neuron>
{
    std::vector<Neuron*> in, out;
    unsigned int id;

    Neuron()
    {
        static unsigned int next_id{1};
        id = next_id++;
    }

    friend std::ostream& operator<<(std::ostream& os, const Neuron& neuron)
    {
        for (Neuron* n : neuron.in)
        {
            os << n->id << "\t-->\t[" << neuron.id << "]\n";
        }

        for (Neuron* n : neuron.out)
        {
            os << "[" << neuron.id << "]\t-->\t" << n->id << '\n';
        }

        return os;
    }

    Neuron* begin() { return this; }
    Neuron* end() { return this + 1; }

    const Neuron* begin() const { return this; }
    const Neuron* end() const { return this + 1; }
};

struct NeuronLayer : std::vector<Neuron>, SomeNeurons<NeuronLayer>
{
    explicit NeuronLayer(int count)
    {
        while (count-- > 0)
        {
            emplace_back();
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const NeuronLayer& layer)
    {
        for (const auto& n : layer)
        {
            os << n;
        }
        return os;
    }
};

template <typename Self>
template <typename T>
void SomeNeurons<Self>::connect_to(T& other)
{
    auto& self = *static_cast<Self*>(this);

    for (Neuron& from : self)
    {
        for (Neuron& to : other)
        {
            from.out.push_back(&to);
            to.in.push_back(&from);
        }
    }
}

int main()
{
    Neuron n1, n2;

    n1.connect_to(n2);

    std::cout << "n1 and n2:\n";
    std::cout << n1 << n2 << '\n';

    NeuronLayer l1{2};
    NeuronLayer l2{3};

    n1.connect_to(l1);
    l1.connect_to(l2);

    std::cout << "Layer 1:\n";
    std::cout << l1;

    std::cout << "Layer 2:\n";
    std::cout << l2;

    return 0;
}