#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int n;
    cin >> n;

    double maxDiagonal = 0.0;
    int maxArea = 0;

    for (int i = 0; i < n; i++) {
        int width, length;
        cin >> width >> length;

        // Calculate the diagonal length using the Pythagorean theorem
        double diagonal = sqrt(width * width + length * length);

        // Compare with the current maximum diagonal
        if (diagonal > maxDiagonal) {
            maxDiagonal = diagonal;
            maxArea = width * length;
        }
    }

    cout <<  maxArea << endl;

    return 0;
}
