//From https://github.com/dcousens/Backprop/blob/master/backprop.cpp

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>

using std::vector;
double uniform() { return (0.5 - ((double)rand() / RAND_MAX)) * 2; }

class Backprop {
private:
    double activation(double x) const { return tanh(x); }
    double gradient(double x) const { return 1 - (x * x); }

    vector< vector<double> > errors, outputs;
    vector< vector< vector<double> > > deltas, weights;

public:
    Backprop(const vector<int>& config) {
        const auto nLayers = config.size();

        this->deltas.resize(nLayers);
        this->errors.resize(nLayers);
        this->outputs.resize(nLayers);
        this->weights.resize(nLayers);

        for (size_t i = 1; i < nLayers; ++i) {
            const auto nNeurons = config[i];

            this->deltas[i].resize(nNeurons);
            this->errors[i].resize(nNeurons);
            this->outputs[i].resize(nNeurons);
            this->weights[i].resize(nNeurons);

            const auto nInputs = config[i - 1] + 1; // +1 for bias

            for (auto j = 0; j < nNeurons; ++j) {
                this->deltas[i][j].resize(nInputs);
                this->weights[i][j].resize(nInputs);

                for (auto k = 0; k < nInputs; ++k) {
                    this->deltas[i][j][k] = 0;
                    this->weights[i][j][k] = uniform();
                }
            }
        }
    }

    const vector<double>& activate(const vector<double>& data) {
        const auto nLayers = this->outputs.size();

        for (size_t i = 1; i < nLayers; ++i) {
            const auto& inputs = i - 1 > 0 ? this->outputs[i - 1] : data;
            const auto& neurons = this->weights[i];
            auto& outputs = this->outputs[i];

            for (size_t j = 0; j < neurons.size(); ++j) {
                double sum = 0;

                for (size_t k = 0; k < inputs.size(); ++k) {
                    sum += inputs[k] * neurons[j][k];
                }

                sum += neurons[j].back(); // bias

                outputs[j] = this->activation(sum);
            }
        }

        return this->outputs.back();
    }

    void calculateError(const vector<double>& desired) {
        // error for output layer
        {
            const auto& outputs = this->outputs.back();
            auto& errors = this->errors.back();

            for (size_t j = 0; j < outputs.size(); ++j) {
                errors[j] = (desired[j] - outputs[j]) * this->gradient(outputs[j]);
            }
        }

        // calculate error for hidden layers
        const auto nHiddenLayers = this->outputs.size() - 2;

        for (auto i = nHiddenLayers; i >= 1; --i) {
            const auto upperLayer = i + 1;
            const auto& upperLayerErrors = this->errors[upperLayer];
            const auto& upperLayerWeights = this->weights[upperLayer];

            auto& errors = this->errors[i];
            const auto& outputs = this->outputs[i];

            for (size_t j = 0; j < outputs.size(); ++j) {
                double sum = 0;

                for (size_t k = 0; k < upperLayerWeights.size(); ++k) {
                    sum += upperLayerErrors[k] * upperLayerWeights[k][j];
                }

                errors[j] = sum * this->gradient(outputs[j]);
            }
        }
    }

    void train(const vector<double>& data, const vector<double>& desired, const double learnRate, const double momentum) {
        this->activate(data);
        this->calculateError(desired);

        // adjust weights for layers
        const auto nLayers = this->outputs.size();
        const auto adjustment = (1 - momentum) * learnRate;

        for (size_t i = 1; i < nLayers; ++i) {
            const auto lowerLayer = i - 1;

            const auto& inputs = lowerLayer > 0 ? this->outputs[lowerLayer] : data;
            const auto& errors = this->errors[i];

            for (size_t j = 0; j < errors.size(); ++j) {
                const auto adjustedError = adjustment * errors[j];

                for (size_t k = 0; k < inputs.size(); ++k) {
                    const auto delta = adjustedError * inputs[k] + (momentum * this->deltas[i][j][k]);

                    this->deltas[i][j][k] = delta;
                    this->weights[i][j][k] += delta;
                }

                const auto delta = adjustedError + (momentum * this->deltas[i][j].back());

                this->deltas[i][j].back() = delta;
                this->weights[i][j].back() += delta;
            }
        }
    }
};

int main() {
    const vector<int> config = {5, 10, 3};
    const vector< vector<double> > input = {
        {0.3, 0.6, 0.2, 0.3, 0.4},
        {0.3, 0.5, 0.7, 0.8, 0.9},
        {0.4, 0.1, 0.9, 0.2, 0.5},
        {0.0001, 0.999, 0.999, 0.999, 0.333}
    };
    const vector< vector<double> > desired = {
        {0.86, 0.5, 0.8},
        {0.5, 0.2, 0.1},
        {0.42, 0.42, 0.42},
        {0.99, 0.0, 0.5}
    };

    auto bp = Backprop(config);

    for (int i = 0; i < 200000; ++i) {
        bp.train(input[i % input.size()], desired[i % input.size()], 0.1, 0.1);
    }

    for (const auto data : input) {
        const auto res = bp.activate(data);

        for (const auto x : res) std::cout << x << ' ';
        std::cout << std::endl;
    }

    return 0;
}