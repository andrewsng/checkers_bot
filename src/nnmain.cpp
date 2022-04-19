#include <iostream>
#include <vector>
using std::vector;


int main(int argc, char *argv[]) {
    vector<float> input = { 1.0f, 1.0f, 1.0f };

    vector<float> weights1 = { 0.25f, 0.5f, 0.75f };
    vector<float> weights2 = { 0.5f, 0.75f, 1.0f };
    vector<float> weights3 = { 0.75f, 1.0f, 1.25f };

    float bias1 = 3.0f;
    float bias2 = 4.0f;
    float bias3 = 5.0f;

    float output1 = input[0] * weights1[0] + input[1] * weights1[1] + input[2] * weights1[2] + bias1;
    float output2 = input[0] * weights2[0] + input[1] * weights2[1] + input[2] * weights2[2] + bias2;
    float output3 = input[0] * weights3[0] + input[1] * weights3[1] + input[2] * weights3[2] + bias3;
    std::cout << output1 << " " << output2 << " " << output3 << "\n";
}
