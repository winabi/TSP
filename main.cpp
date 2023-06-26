#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

map<string, map<string, int>> trainsMapTask1; // Matrix 6 by 6
map<string, map<string, double>> trainsMapTask2;
vector<string> trainsArray; // Storage of unique train numbers
vector<int> visited;
int costTask1 = 0;
float costTask2 = 0;

class MyClass
{
public:
    int routeNumber;
    string numTrain1;
    string numTrain2;
    double cost;
    string time1;
    string time2;
    int Time;

    MyClass();
    MyClass(int for_routeNumber, string for_numTrain1, string for_numTrain2, double for_cost, string for_time1, string for_time2, int for_Time)
    {
        routeNumber = for_routeNumber;
        numTrain1 = for_numTrain1;
        numTrain2 = for_numTrain2;
        cost = for_cost;
        time1 = for_time1;
        time2 = for_time2;
        Time = for_Time;
    }
};

// Definition of the output operator for the MyClass class
ostream &operator<<(ostream &os, const MyClass &obj)
{
    os << "numTrain1: " << obj.numTrain1 << ", numTrain2: " << obj.numTrain2 << ", cost: " << obj.cost << ", Time: " << obj.Time;
    return os;
}

// Function for converting hours to minutes
int processTime(string timeString1, string timeString2)
{
    int hourTrain1, minuteTrain1, secondTrain1, hourTrain2, minuteTrain2, secondTrain2;

    istringstream issTrain1(timeString1);
    string hour1, minute1, second1;
    getline(issTrain1, hour1, ':');
    getline(issTrain1, minute1, ':');
    getline(issTrain1, second1, ':');

    hourTrain1 = stoi(hour1);
    minuteTrain1 = stoi(minute1);
    secondTrain1 = stoi(second1);

    int totalMinutesTrain1 = hourTrain1 * 60 + minuteTrain1 + secondTrain1 / 60;

    istringstream issTrain2(timeString2);
    string hour2, minute2, second2;
    getline(issTrain2, hour2, ':');
    getline(issTrain2, minute2, ':');
    getline(issTrain2, second2, ':');

    hourTrain2 = stoi(hour2);
    minuteTrain2 = stoi(minute2);
    secondTrain2 = stoi(second2);

    int totalMinutesTrain2 = hourTrain2 * 60 + minuteTrain2 + secondTrain2 / 60;

    int timeDifference;
    if (totalMinutesTrain2 >= totalMinutesTrain1)
    {
        timeDifference = totalMinutesTrain2 - totalMinutesTrain1;
    }
    else
    {
        // Add 24 hours (1440 minutes) to account for midnight crossing
        timeDifference = (24 * 60 - totalMinutesTrain1) + totalMinutesTrain2;
    }

    return timeDifference;
}

void readFromFile(vector<MyClass> &objectsArray)
{
    ifstream file("test_task_data.csv");
    if (!file.is_open())
    {
        cout << "File opening error!" << endl;
    }

    string line;
    vector<vector<string>> parsedData;

    // Read the file line by line
    while (getline(file, line))
    {
        istringstream iss(line); // The current line read from the file
        string routeNumberStr, numTrain1, numTrain2, costStr, time1, time2;
        double cost_r;
        int routeNumber;

        if (getline(iss, routeNumberStr, ';') &&
            getline(iss, numTrain1, ';') &&
            getline(iss, numTrain2, ';') &&
            getline(iss, costStr, ';') &&
            getline(iss, time1, ';') &&
            getline(iss, time2, ';'))
        {
            cost_r = stod(costStr);                    // Convert string costStr to type double
            routeNumber = stoi(routeNumberStr);        // Convert routeNumberStr string to int type
            time2 = time2.substr(0, time2.size() - 1); // Method for creating a substring from the existing string

            int Time = processTime(time1, time2);

            objectsArray.push_back(MyClass(routeNumber, numTrain1, numTrain2, cost_r, time1, time2, Time));
        }
        else
        {
            cout << "Error when extracting values from a string: " << line << endl;
        }
    }

    file.close();
}

void printTrainsMapTask1(const vector<string> &trainsArray, map<string, map<string, int>> &trainsMap)
{
    cout << "\t";
    for (const auto &train : trainsArray)
    {
        cout << train << "\t";
    }
    cout << "\n";

    for (const auto &train1 : trainsArray)
    {
        cout << train1 << "\t";
        for (const auto &train2 : trainsArray)
        {
            cout << trainsMap[train1][train2] << "\t";
        }
        cout << endl;
    }
}

void printTrainsMapTask2(const vector<string> &trainsArray, map<string, map<string, double>> &trainsMap)
{
    cout << "\t";
    for (const auto &train : trainsArray)
    {
        cout << train << "\t";
    }
    cout << "\n";

    for (const auto &train1 : trainsArray)
    {
        cout << train1 << "\t";
        for (const auto &train2 : trainsArray)
        {
            cout << trainsMap[train1][train2] << "\t";
        }
        cout << endl;
    }
}

int leastTask1(int c)
{
    int i, nc = 999;
    int min = 1500, kmin;
    for (i = 0; i < trainsArray.size(); i++)
    {
        const string &trainRoute = trainsArray[i];
        if ((trainsMapTask1[trainsArray[c]][trainRoute] != 0) && (visited[i] == 0))
            if (trainsMapTask1[trainsArray[c]][trainRoute] < min)
            {
                min = trainsMapTask1[trainRoute][trainsArray[0]] + trainsMapTask1[trainsArray[c]][trainRoute];
                kmin = trainsMapTask1[trainsArray[c]][trainRoute];
                nc = i;
            }
    }
    if (nc != 999)
        costTask1 += kmin;
    return nc;
}

double leastTask2(int c)
{
    int i, nc = 999;
    int min = 2000, kmin;
    for (i = 0; i < trainsArray.size(); i++)
    {
        const string &trainRoute = trainsArray[i];
        if ((trainsMapTask2[trainsArray[c]][trainRoute] != 0) && (visited[i] == 0))
            if (trainsMapTask2[trainsArray[c]][trainRoute] < min)
            {
                min = trainsMapTask2[trainRoute][trainsArray[0]] + trainsMapTask2[trainsArray[c]][trainRoute];
                kmin = trainsMapTask2[trainsArray[c]][trainRoute];
                nc = i;
            }
    }
    if (nc != 999)
        costTask2 += kmin;
    return nc;
}

void mincostTask1(int trainRoute)
{
    int i, ntrainRoute;
    visited[trainRoute] = 1;
    cout << trainsArray[trainRoute] << " -> ";
    ntrainRoute = leastTask1(trainRoute);
    if (ntrainRoute == 999)
    {
        ntrainRoute = 0;
        cout << trainsArray[ntrainRoute];
        costTask1 += trainsMapTask1[trainsArray[trainRoute]][trainsArray[ntrainRoute]];
        return;
    }
    mincostTask1(ntrainRoute);
}

void mincostTask2(int trainRoute)
{
    int i, ntrainRoute;
    visited[trainRoute] = 1;
    cout << trainsArray[trainRoute] << " -> ";
    ntrainRoute = leastTask2(trainRoute);
    if (ntrainRoute == 999)
    {
        ntrainRoute = 0;
        cout << trainsArray[ntrainRoute];
        costTask2 += trainsMapTask2[trainsArray[trainRoute]][trainsArray[ntrainRoute]];
        return;
    }
    mincostTask2(ntrainRoute);
}

void taskWIthTime(vector<MyClass> &objectsArray)
{
    // Filling the array
    for (int i = 0; i < trainsArray.size(); i++)
    {
        for (int j = 0; j < trainsArray.size(); j++)
        {
            // Find all numTrain1 and numTrain2 matches
            vector<MyClass>::iterator it = objectsArray.begin();
            while (it != objectsArray.end())
            {
                it = find_if(it, objectsArray.end(), [&](const MyClass &obj)
                             { return obj.numTrain1 == trainsArray[i] && obj.numTrain2 == trainsArray[j]; });

                if (it != objectsArray.end())
                {
                    if (trainsMapTask1[trainsArray[i]][trainsArray[j]] == 0 || it->Time < trainsMapTask1[trainsArray[i]][trainsArray[j]])
                    {
                        trainsMapTask1[trainsArray[i]][trainsArray[j]] = (it->Time);
                    }
                    it++;
                }
            }

            // if (trainsMapTask1[trainsArray[i]][trainsArray[j]] == 0)
            // {
            //     // cout << "The object with numTrain1=" << trainsArray[i] << " and numTrain2=" << trainsArray[j] << " not found." << endl;
            // }
        }
    }

    cout << "Matrix for the Time Assignment" << endl;
    printTrainsMapTask1(trainsArray, trainsMapTask1);

    visited.resize(trainsArray.size(), 0);

    cout << "\n Best Time:";
    cout << "\n There's a route: ";
    mincostTask1(0);
    cout << "\n Minimum time: " << costTask1 / 60 << " hours " << costTask1 % 60 << " minutes ";

    visited.clear();
}

void taskWIthCost(vector<MyClass> &objectsArray)
{
    // Filling the array
    for (int i = 0; i < trainsArray.size(); i++)
    {
        for (int j = 0; j < trainsArray.size(); j++)
        {
            // Find all numTrain1 and numTrain2 matches
            vector<MyClass>::iterator it = objectsArray.begin();
            while (it != objectsArray.end())
            {
                it = find_if(it, objectsArray.end(), [&](const MyClass &obj)
                             { return obj.numTrain1 == trainsArray[i] && obj.numTrain2 == trainsArray[j]; });

                if (it != objectsArray.end())
                {
                    if (trainsMapTask2[trainsArray[i]][trainsArray[j]] == 0 || it->cost < trainsMapTask2[trainsArray[i]][trainsArray[j]])
                    {
                        trainsMapTask2[trainsArray[i]][trainsArray[j]] = (it->cost);
                    }
                    it++;
                }
            }

            // if (trainsMapTask2[trainsArray[i]][trainsArray[j]] == 0)
            // {
            //     // cout << "The object with numTrain1=" << trainsArray[i] << " and numTrain2=" << trainsArray[j] << " not found." << endl;
            // }
        }
    }

    cout << "Matrix for the Cost Assignment " << endl;
    printTrainsMapTask2(trainsArray, trainsMapTask2);

    visited.resize(trainsArray.size(), 0);

    cout << "\n Best Cost:";
    cout << "\n There's a route: ";
    mincostTask2(0);
    cout << "\n Minimum cost: " << costTask2;

    visited.clear();
}

int main()
{
    vector<MyClass> objectsArray;
    readFromFile(objectsArray);

    for (auto object : objectsArray)
    {
        if (find(trainsArray.begin(), trainsArray.end(), object.numTrain1) == trainsArray.end())
        {
            trainsArray.push_back(object.numTrain1);
        }
    }

    taskWIthTime(objectsArray);
    cout << "\n\n\n";

    taskWIthCost(objectsArray);
    cout << endl;

    return 0;
}
