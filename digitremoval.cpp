#include <iostream>
using namespace std;

int main() {
    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int n, d, count = 0, placeV = 0, result = 0, number = 0, number1 = 0;
        cin >> n >> d;
        number = number1 = n;
    recheck:
        count = placeV = 0;
        while (number != 0) {
            count++;
            if (number % 10 == d) {
                placeV = count;
            }
            number /= 10;
        }

        if (placeV != 0) {
            int difference = 0, tens = 1;

            for (int j = 0; j < placeV - 1; j++) {
                tens *= 10;
            }
            difference = number1 - (number1 / tens) * tens;

            int major = 1;
            if (d == 0) {
                for (int k = 0; k < placeV - 1; k++) {
                    major = 1 + major * 10;
                }
                result = result + major - difference;
            } else {
                result = result + tens - difference;

                if (d == 9) {
                    number = number1 = result + n;
                    goto recheck;
                }
            }
        }
        cout << result << endl;
    }
    return 0;
}
