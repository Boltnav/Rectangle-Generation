#include <iostream>
#include <fstream>
#include <algorithm>
// #include <vector>
#include <cstdlib>
// #include <ctime>
#include <time.h>
#include <random>
using namespace std;

#define NUMB 100

int main() 
{
    srand(time(NULL));
    // ofstream object for writing
    ofstream outFile;
    outFile.open("ok.txt");
    if (!outFile) // Check if the file was opened successfully
    { 
        cerr << "Error opening file." << endl;
        return 1; 
    }

    // cout << "rects = [";
    outFile << "rects = [";

    int numberOfRectangles = 10;    // Change this to change the number of rectangles generated
    for (int i = 0; i < numberOfRectangles ; i++)
    {
        int x1 = rand() % NUMB+1;
        int x2 = rand() % NUMB+1;
        int x_random1 = min(x1, x2);
        if (x_random1 == NUMB){x_random1--;}
        int x_random2 = max(x1, x2);
        if (x_random2 == x_random1){x_random2++;}
        pair <int, int> x_pair;
        x_pair = make_pair(x_random1, x_random2);

        int y1 = rand() % NUMB+1;
        int y2 = rand() % NUMB+1;
        int y_random1 = min(y1, y2);
        if (y_random1 == NUMB){y_random1--;}
        int y_random2 = max(y1, y2);
        if (y_random2 == y_random1){y_random2++;}
        pair <int, int> y_pair;
        y_pair = make_pair(y_random1, y_random2);

        outFile << "Rectangle(bottomLeft=(" << x_pair.first << ", " << y_pair.first << "), topRight=(" << x_pair.second << ", " << y_pair.second << "))";

        if (i != numberOfRectangles-1){outFile << ", ";}
    }
    outFile << "]"; 
    outFile.close();
}