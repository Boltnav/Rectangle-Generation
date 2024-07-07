#include <iostream>
#include <fstream>
#include <algorithm>
// #include <vector>
#include <cstdlib>
// #include <ctime>
#include <time.h>
#include <random>
using namespace std;

# define NUMB 199

struct Node 
{
    pair<int, int> x_interval;
    pair<int, int> y_interval;
    int max;
    Node* left;
    Node* right;

    Node(pair<int, int> x_interval, pair<int, int> y_interval) : x_interval(x_interval), y_interval(y_interval), max(x_interval.second), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root, pair<int, int> x_interval, pair<int, int> y_interval)
{
    if (!root) 
    {
        return new Node(x_interval, y_interval);
    }

    if (x_interval.first < root->x_interval.first) 
    {
        root->left = insert(root->left, x_interval, y_interval);
    } 
    else 
    {
        root->right = insert(root->right, x_interval, y_interval);
    }

    root->max = max(root->max, x_interval.second);
    return root;
}

pair<int, int> overlap(Node* root, pair<int, int> arb_interval) 
{
    if (!root) 
    {
        return make_pair(-1, -1);
    }

    // arbitrary interval is fully enclosed by root->x_interval
    if (root->x_interval.first <= arb_interval.second && root->x_interval.second >= arb_interval.first) 
    {
        return root->x_interval;
    }

    if (root->left && root->left->max >= arb_interval.first) 
    {
        return overlap(root->left, arb_interval);
    }

    return overlap(root->right, arb_interval);
}

void findAllOverlaps(Node* root, pair<int, int> arb_interval, vector<pair<int, int>>& overlaps) {
    if (!root) 
    {
        return;
    }

    // If there is an overlap with the current node's interval, add it to the result vector
    if (root->x_interval.first <= arb_interval.second && root->x_interval.second >= arb_interval.first) 
    {
        // overlaps.push_back(root->x_interval);
        overlaps.push_back(root->y_interval); // pushing the y_interval !!!
    }

    // If there's a left child that could contain overlapping intervals, recurse on the left child
    if (root->left && root->left->max >= arb_interval.first) 
    {
        findAllOverlaps(root->left, arb_interval, overlaps);
    }

    // Recurse on the right child as there could still be overlapping intervals
    findAllOverlaps(root->right, arb_interval, overlaps);
}

Node* minValueNode(Node* root) 
{
    Node* current = root;
    while (current && current->left != nullptr)      
    {
        current = current->left;
    }
    return current;
}

Node* deleteNode(Node* root, pair<int, int> x_interval) 
{
    if (!root) 
    {
        return nullptr;
    }

    if (x_interval.first < root->x_interval.first) 
    {
        root->left = deleteNode(root->left, x_interval);
    } 
    else if (x_interval.first > root->x_interval.first) 
    {
        root->right = deleteNode(root->right, x_interval);
    }
    else 
    {
        if (root->left == nullptr) 
        {
            Node* temp = root->right;
            delete root;
            return temp;
        } 
        else if (root->right == nullptr) 
        {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = minValueNode(root->right);
        root->x_interval = temp->x_interval;
        root->right = deleteNode(root->right, temp->x_interval);
    }

    return root;
}

vector <pair<int, int>> mergeIntervals( vector <pair<int, int>> & intervals)
{
    // if (intervals.empty())  // This will never be satisfied because this null possibility has already been handled 
    // {
    //     return;
    // }

    sort(intervals.begin(), intervals.end());   // Sorted on the basis of the first element of each interval; if first elements are equal, then compare using second
    vector <pair<int, int>> mergedIntervals;
    mergedIntervals.push_back(intervals[0]);
    for (auto & intervalCurrent : intervals)
    {
        if (intervalCurrent.first <= mergedIntervals.back().second)
        {
            mergedIntervals.back().second = max(mergedIntervals.back().second, intervalCurrent.second);
        }
        else
        {
            mergedIntervals.push_back(intervalCurrent);
        }
    }

    return mergedIntervals;
}

pair<int, int> generate_Y_interval( vector<pair<int, int>> & intervals) 
{
    int start, end;

    // If intervals are empty, pick any random pair as there are no possibilities of an overlap

    if (intervals.empty()) 
    {
        int one = rand() % NUMB+1;
        int two = rand() % NUMB+1;
        start = min(one, two);
        if (start == NUMB){start--;}
        end = max(one, two);
        if (end == start){end++;}
        // cout<< "No Restriction : Start = " << start << ", End = " << end << endl;
        return {start, end};
    }

    // If intervals are not empty, proceed with finding a gap
    
    vector <pair<int, int>> mergedIntervals = mergeIntervals(intervals);

    int length = mergedIntervals.size();
    int sector = rand() % length+1;

    // vector <int> choiceVector;
    // for (size_t i = 0; i <= sortedIntervals.size(); i++)
    // {
    //     if (i == 0)
    //     {
    //         for (int j = 0; j < sortedIntervals[0].first; j++)
    //         {
    //             choiceVector.push_back(j);
    //         }
    //     }
    //     else if (i == sortedIntervals.size())
    //     {
    //         for (int j = sortedIntervals[sortedIntervals.size()-1].second; j <= NUMB; j++)  
    //         {
    //             choiceVector.push_back(j);
    //         }
    //     }
    //     else
    //     {
    //         for (int j = sortedIntervals[i-1].second; j < sortedIntervals[i].first; j++)
    //         {
    //             choiceVector.push_back(j);
    //         }
    //     }
    // }

    if (sector == 0)
    {
        int one = rand() % mergedIntervals[0].first;
        int two = rand() % mergedIntervals[0].first;
        start = min(one, two);
        end = max(one, two);
        if (start == NUMB){start--;}
        if (end == start){end++;}
        // cout<< "Sector = " << sector << " : Start = " << start << ", End = " << end << endl;
        return {start, end};
    }
    else if (sector == length)
    {
        int one = rand() % (NUMB - mergedIntervals[sector-1].second); one = one + mergedIntervals[sector-1].second;
        int two = rand() % (NUMB - mergedIntervals[sector-1].second); two = two + mergedIntervals[sector-1].second;
        // int two = rand() % (NUMB - one); two = two + one;
        start = min(one, two);
        end = min(one, two);
        if (start == NUMB){start--;}
        if (end == start){end++;}
        // cout<< "Sector = " << sector << " : Start = " << start << ", End = " << end << endl;
        return {start, end};
    }
    else
    {
        int one = rand() % (mergedIntervals[sector].first - mergedIntervals[sector-1].second); one = one + mergedIntervals[sector-1].second;
        int two = rand() % (mergedIntervals[sector].first - mergedIntervals[sector-1].second); two = two + mergedIntervals[sector-1].second;
        start = min(one, two);
        end = max(one, two);
        if (start == NUMB){start--;}
        if (end == start){end++;}
        // cout<< "Sector = " << sector << " : Start = " << start << ", End = " << end << endl;
        return {start, end};
    }

}

// void printer(pair <int, int> x_interval, pair <int, int> y_interval, ofstream outFile)
// {
//     // cout<< "[(" << x_interval.first << ", " << x_interval.second << "), (" << y_interval.first << ", " << y_interval.second << ")]" << endl; 

//     outFile << "Rectangle(bottomLeft=(" << x_interval.first << ", " << y_interval.first << "), topRight=(" << x_interval.second << ", " << y_interval.second << "))";
// }

int main() 
{
    srand(time(NULL));
    // ofstream object for writing
    ofstream outFile;
    outFile.open("Generated.txt");
    if (!outFile) // Check if the file was opened successfully
    { 
        cerr << "Error opening file." << endl;
        return 1; 
    }

    Node* root = nullptr;

    // cout << "rects = [";
    outFile << "rects = [";

    int numberOfRectangles = 19;    // Change this to change the number of rectangles generated
    for (int i = 0; i < numberOfRectangles ; i++)
    {
        // int rand1 = (rand() % NUMB) + 1;
        int rand1 = rand() % NUMB+1;
        int rand2 = rand() % NUMB+1;
        int x_random1 = min(rand1, rand2);
        if (x_random1 == NUMB){x_random1--;}
        int x_random2 = max(rand1, rand2);
        if (x_random2 == x_random1){x_random2++;}
        // This is the X-axis interval
        // cout<< "Random x values: " << x_random1 << " and " << x_random2 << endl;
        pair <int, int> x_pair;
        vector<pair<int, int>> overlaps;
        x_pair = make_pair(x_random1, x_random2);

        // Finding all the nodes it overlaps
        findAllOverlaps(root, x_pair, overlaps);
        if (!overlaps.empty()) 
        {
            // cout<< overlaps[0].first << " and " << overlaps[0].second << endl;
        } 
        else 
        {
            // cout<< "No overlaps found." << endl;
        }

        // The corresponding Y-axis interval
        pair<int, int> y_pair = generate_Y_interval(overlaps);
        // cout<< "Random y values: " << y_pair.first << " and " << y_pair.second << endl;

        // printer(x_pair, y_pair, outFile);
        outFile << "Rectangle(bottomLeft=(" << x_pair.first << ", " << y_pair.first << "), topRight=(" << x_pair.second << ", " << y_pair.second << "))";

        root = insert(root, x_pair, y_pair);

        if (i != 19){outFile << ", ";}
    }
    outFile << "]"; 
    outFile.close();
}
