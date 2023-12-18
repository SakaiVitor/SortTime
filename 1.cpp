#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const double timeout_time = 300.0; // Timeout 300 seconds

vector<float> bubbleSort(vector<float> disArray) {
    clock_t start_time = clock();
    
    for (int i = 0; i < (int)disArray.size(); i++) {
        for (int j = 0; j < (int)disArray.size() - i - 1; j++) {
            if (disArray[j] > disArray[j + 1]) {
                swap(disArray[j], disArray[j + 1]);
            }
        }
        
        // Check elapsed time and exits if exceeds 300s
        if ((double)(clock() - start_time) / CLOCKS_PER_SEC > timeout_time) {
            return disArray; // Return partially sorted array
        }
    }
    
    return disArray;
}

vector<float> quickSort(vector<float> disArray, clock_t start_time) {
    if (disArray.size() <= 1) {
        return disArray;
    }
    
    vector<float> left, right;
    for (int i = 1; i < (int)disArray.size(); i++) {
        if (disArray[i] < disArray[0]) {
            left.push_back(disArray[i]);
        } else {
            right.push_back(disArray[i]);
        }
    }
    
    left = quickSort(left, start_time);
    
    // Timeout check
    if ((double)(clock() - start_time) / CLOCKS_PER_SEC > timeout_time) {
        return disArray; 
    }
    
    right = quickSort(right, start_time);
    left.push_back(disArray[0]);
    left.insert(left.end(), right.begin(), right.end());
    
    return left;
}

vector<float> mergeSort(vector<float> disArray, clock_t start_time) {
    if (disArray.size() == 1) {
        return disArray;
    }
    
    vector<float> left(disArray.begin(), disArray.begin() + disArray.size() / 2);
    vector<float> right(disArray.begin() + disArray.size() / 2, disArray.end());
    
    left = mergeSort(left, start_time);
    
    // Timeout check
    if ((double)(clock() - start_time) / CLOCKS_PER_SEC > timeout_time) {
        return disArray;
    }
    
    right = mergeSort(right, start_time);
    vector<float> result;
    int i = 0, j = 0;
    while (i < (int)left.size() && j < (int)right.size()) {
        if (left[i] < right[j]) {
            result.push_back(left[i]);
            i++;
        } else {
            result.push_back(right[j]);
            j++;
        }
    }
    while (i < (int)left.size()) {
        result.push_back(left[i]);
        i++;
    }
    while (j < (int)right.size()) {
        result.push_back(right[j]);
        j++;
    }
    
    return result;
}

vector<float> randomArray(int n) {
    vector<float> result;
    // Seed the random number generator with current time
    srand(static_cast<unsigned int>(time(nullptr)));

    for (int i = 0; i < n; i++) {
        float randomValue = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX); // Generate random float from [0, 1]
        float scaledValue = randomValue * 200000.0f - 100000.0f; // Scale to [-100000, 100000]
        result.push_back(scaledValue);
    }
    return result;
}

void saveSortingTimesToCSV(const string& fileName, const vector<int>& sizes, const vector<double>& bubbleSortTimes, const vector<double>& quickSortTimes, const vector<double>& mergeSortTimes) {
    ofstream outputFile(fileName);

    if (outputFile) {
        outputFile << "Size,Bubble Sort Time (s),Quick Sort Time (s),Merge Sort Time (s)" << endl;

        for (size_t i = 0; i < sizes.size(); i++) {
            outputFile << sizes[i] << "," << bubbleSortTimes[i] << "," << quickSortTimes[i] << "," << mergeSortTimes[i] << endl;
        }

        outputFile.close();
    } else {
        cerr << "Error: Unable to open the CSV file for writing." << endl;
    }
}

int main() {
    vector<int> sizes = {1000, 10000, 100000, 1000000, 10000000};
    vector<double> bubbleSortTimes, quickSortTimes, mergeSortTimes;

    for (int size : sizes) {
        vector<float> disArray = randomArray(size);
        vector<float> result;

        clock_t start, end;

        start = clock();
        result = bubbleSort(disArray);
        end = clock();
        double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
        bubbleSortTimes.push_back(elapsed_time);

        start = clock();
        result = quickSort(disArray, start);
        end = clock();
        elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
        quickSortTimes.push_back(elapsed_time);

        start = clock();
        result = mergeSort(disArray, start);
        end = clock();
        elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
        mergeSortTimes.push_back(elapsed_time);
    }

    // Save sorting times to CSV file
    saveSortingTimesToCSV("sorting_times.csv", sizes, bubbleSortTimes, quickSortTimes, mergeSortTimes);

    return 0;
}
