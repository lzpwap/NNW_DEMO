#include <armadillo>
using namespace arma;
class Layer {
public:
	Layer* preLayer;
	Layer* nextLayer;
	mat weight;
    vec bais;
	size_t in;
	size_t out;
    int activationFlag;
    vec transform(const vec& x) const;
};

class NeuralNetwork {
public:
	Layer* innerLayer;
    const char* modelPath;
	int predict(const vec& x) const;
    NeuralNetwork(const char* modelPath);
    void initModel();
};