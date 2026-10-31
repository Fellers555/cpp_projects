#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <limits>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;

const int MAXSIZE = 1000;

void swapValues(int &a, int &b);

int readNumbersFromFile(int nums[]);

int getIndexesForRange(const int nums[], int length, int low, int high, int indexes[]);

void sortIndexes(int indexes[], int numIndexes, const int nums[]);

void printNumbersByIndex(const int indexes[], int numIndexes, const int nums[]);

void getStats(const int nums[], int length, int &smallest, int &biggest, double &average, double &sd);

void printAll(const int nums[], int length);

void checkValidInteger(int& input, string outputMSG){
    while (!(cin >> input)) {
        cout << outputMSG;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return;
}

int main()
{
    int numbers[MAXSIZE], indexes[MAXSIZE],
        lowerBound, upperBound, 
        size = readNumbersFromFile(numbers);
    printAll(numbers, size);
   
    char response;
    do {
        cout << "Enter bounds for a range: ";
        checkValidInteger(lowerBound, "lower bound not an integer, try again: ");
        checkValidInteger(upperBound, "upper bound not an integer, try again: ");

        int numIndexes = getIndexesForRange(numbers, size, lowerBound, upperBound, indexes);
        if (numIndexes == 0) 
            cout << "No values were found in that range. " << endl;
        else {
            cout << numIndexes << " value(s) found." << endl;
            cout << "In order by index... " << endl;
            printNumbersByIndex(indexes, numIndexes, numbers);
            sortIndexes(indexes, numIndexes, numbers);
            cout << "In order by value... " << endl;
            printNumbersByIndex(indexes, numIndexes, numbers);
        }
        cout << "Go again? (y/n) ";
        cin >> response;
    } while (response == 'y' || response == 'Y');
    cout << "Bye!" << endl;
    return 0;
}

void swapValues(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

//USER INPUTS FILE HERE
int readNumbersFromFile(int nums[]) {
    
    string fileName;
    cout << "Please input a .txt file: ";
    
    do {
        cin >> fileName;
        ifstream file(fileName);
        
        if (!file.good()) {
            cout << "No file found. Try again: ";
        }
        else {
            //readout vars here
            int count = 0;
            int n;
            while (file) {
                file >> n;
                if (file) {
                    nums[count] = n;
                    count += 1;
                    //Cap the amount of data
                    if (count == MAXSIZE) {
                        break;
                    }
                }
            }
            
            return count;
        }
    }
    while(true);
}

int getIndexesForRange(const int nums[], int length, int low, int high, int indexes[]) {
    //SEARCH array
    int indexCount = 0;
    for (int i = 0; i < length; i ++) {
        if (nums[i] <= high and nums[i] >= low) {
            indexes[indexCount] = i;
            indexCount += 1;
        }
    }
    return indexCount;
}

void sortIndexes(int indexes[], int numIndexes, const int nums[]) {
    //Sort the indexes array to look better
    for (int i = 0; i < numIndexes; i++) {
        for (int j = 0; j < numIndexes-1; j++){
            if (nums[indexes[j]] > nums[indexes[j+1]]) {
                swapValues(indexes[j],indexes[j+1]);
            }
        }
    }
}


void printNumbersByIndex(const int indexes[], int numIndexes, const int nums[]) {
    int baseOffset = 8;
    
    cout << "Index";
    //LOOP FOR SPACING SINCE WE CAN'T USE SETW
    for (int o = 0; o < baseOffset; o ++) {
        cout << " ";
    }
    cout << "Value" << endl;
    
    for (int i = 0; i < numIndexes; i ++) {
        cout << indexes[i] << ":"; 
        
        //JUSTIFY COLUMNS CORRECTLY
        int additionalOffset = 1;
        if (indexes[i] < 100) {
            additionalOffset ++;
        }
        if (indexes[i] < 10) {
            additionalOffset ++;
        }
        
        for (int o = 0; o < baseOffset + additionalOffset; o ++) {
            cout << " ";
        }
        
        cout << nums[indexes[i]] << endl;
    }
    cout << endl;
}


void getStats(const int nums[], int length, int &smallest, int &biggest, double &average, double &sd) {
    
    double avgSum = 0;
    double sdSum = 0;
    smallest = 0;
    biggest = 0;
    
    if (length > 0) {
        smallest = nums[0];
        biggest = nums[0];
        
        for (int i = 0; i < length; i ++) {
            
            if (nums[i] > biggest) {
                biggest = nums[i];
            }
            
            if (nums[i] < smallest) {
                smallest = nums[i];
            }
            
    	    avgSum += nums[i];
    	    sdSum += (nums[i]) * (nums[i]);
    	}
    	
    	average = avgSum/length;
    	sdSum /= length;
    	sd = sqrt(sdSum - (average*average));
    }
}


void printAll(const int nums[], int length) {
    //DISPLAY RESULT AND STORE VALS
    cout << length << " values were read in:" << endl;
    
    if (length == 0) {
        return;
    }
    
    for (int i = 0; i < length; i++){
        //PRINT 20 ON A LINE
        if (i % 20 == 0) {
            cout << endl;
        }
        cout << nums[i] << " ";
    }
    cout << endl;
    cout << endl;
    
    int min = nums[0];
    int max = nums[0];
    
    double avg = 0;
    double stdev = 0;
    
    getStats(nums, length, min, max, avg, stdev);
    
    //DISPLAY STATS
    cout << "Min value: " << min << endl;
    cout << "Max value: " << max << endl;
    cout << "Average: " << avg << endl;
    cout << "Standard deviation: " << stdev << endl;
    cout << endl;
}