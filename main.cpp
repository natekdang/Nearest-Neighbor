#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip> //for outputting floats
#include <algorithm> //find k in vector
#include <limits.h>

using namespace std;

struct Instance //holds data instances
{
    private:
        int class_type; //two possible classes for this project
        vector<double> features; //features of each instance
        
    public: 
        Instance()
        {
            class_type = 0; //must be set to 1 or 2 eventually
        }
        //setters
        void add_feature(double feature_to_add)
        {
            features.push_back(feature_to_add);
            return; 
        }
        void set_class(int class_type)
        {
            this->class_type = class_type; 
            return; 
        }
        //getters
        vector<double> get_features()
        {
            return features; 
        }
        int get_class()
        {
            return class_type; 
        }
        
        void output()
        {
            cout << "Class:" << class_type << " Features: ";
            for (int i = 0; i < features.size(); i++)
            {
                cout << features.at(i) << " ";
            }
            cout << endl;
        }
        
};
class Data_Set
{
    private:
        vector<Instance> instances; //hold each instance with it's features
        int numInstances;
        int numFeatures; 
        
    public: 
        Data_Set(vector<Instance> data)
        {
            instances = data; //add data to instances vector
            numInstances = data.size();
            numFeatures = data.at(0).get_features().size();
        };
        
        vector<Instance> get_Instances()
        {
            return instances;
        }
        
        int get_NumInstances() //return size of instances
        {
            return numInstances;
            //return instances.size();
        }
        
        int get_NumFeatures()
        {
            return numFeatures;
            //return instances.at(0).get_features().size();
        }
        //double leave_one_out_cross_validation_add(Data_Set, vector<int>, int);
        //double leave_one_out_cross_validation_remove(Data_Set, vector<int>, int);

};

vector<Instance> parseFile(string fileName)
{
    ifstream my_input_file;
    my_input_file.open(fileName.c_str());
    vector<Instance> instanceVect;
    
    while (my_input_file.good())//( getline(my_input_file, inputRow)) //my_input_file.good())
    {
        Instance newInst; 
        vector<double> features; 
        int class_type = -1;
        double featToAdd = 0; 
        string inputRow; //temp string  
        
        getline(my_input_file, inputRow);  
        
        istringstream ss(inputRow);
        
        ss >> class_type;
        
        if (class_type == -1) //no more lines to parse
        {
            break;
        }
        
        else //set class_type
        {
            newInst.set_class(class_type);
        }
        
        while(ss >> featToAdd) //while still features to add
        {
            if(featToAdd != 0) //fix 0 problem
            {
                newInst.add_feature(featToAdd);
            }
        }
        instanceVect.push_back(newInst);  
    }
    
    my_input_file.close();
  
    /*for (int i = 0; i < instanceVect.size(); i++) //TESTING PARSING
    {
        instanceVect.at(i).output();
    } */
    
    cout << "This dataset has " << instanceVect.at(0).get_features().size() << " features with " << instanceVect.size() << " instances." << endl;
    
    return instanceVect;
}

//helper for nearest neighbor, need to implement
double calc_euclidian(vector<double> a, vector<double> b, vector<int> setToCheck)
{
    double euclidian = 0; 
    for (int i = 0; i < setToCheck.size(); i++) //calculate for only features in indices 
    {
        euclidian += pow(abs(a.at(setToCheck.at(i)) - b.at(setToCheck.at(i))), 2); //set to check has num of feature but need to -1 because index starts at 0
    }
    
    //cout << "Distance: " << sqrt(euclidian) << endl;
    return sqrt(euclidian); 
}

/* iterate through entire set of instances leaving one out each time
    calculate ecludian of each and determine the instance j that is 
    i closest to i, if class_type of both are same then add one to correct
    count, at end of loop return correct count/total instances
    */
double leave_one_out_cross_validation_add(Data_Set* data, vector<int>current_set, int feature_to_add)
{
    vector<int> setToCheck = current_set;
    setToCheck.push_back(feature_to_add);
    
    vector<Instance> instances = data->get_Instances();
    
    //TEST OUTPUT
    cout << "Checking features: ";
    for (int i = 0; i < setToCheck.size(); i++)
    {
        cout << setToCheck.at(i) + 1 << " ";
    }
    //TEST OUTPUT
    
    double correctlyClassified = 0; 
    
    for (int i = 0; i < data->get_NumInstances(); i++)
    {
        double shortestDistance = INT_MAX; 
        Instance nearestNeighbor; 
        
        //TEST 
        //int nearest = 0;
        
        for (int j = 0; j < data->get_NumInstances(); j++)
        {
            double tempDistance = 0;
            if (i == j) //leave one out
            {
                continue; 
            }
            else
            {
                //cout << "Calling euclidian for " << j << "th instance" << endl; //TEST
                tempDistance = calc_euclidian(instances.at(i).get_features(), instances.at(j).get_features(), setToCheck);
                //cout << "tempDistance: " << tempDistance << ". shortestDistance: " << shortestDistance <<  endl; //TEST 
                if (tempDistance < shortestDistance)
                {
                    //cout << "tempDistance < shortestDistnace" << endl;
                    shortestDistance = tempDistance; //update newest shortest
                    nearestNeighbor = data->get_Instances().at(j); 
                    
                    //TEST 
                    //nearest = j;
                }
            }
        } //inner for
        
        //TEST
        //cout << "nearest neighbor index: " << nearest << endl;
        
        if (nearestNeighbor.get_class() == data->get_Instances().at(i).get_class())
        {
            correctlyClassified += 1; //increment # correct
        }
        
    }
    cout << "Accuracy: " << (correctlyClassified/(data->get_NumInstances() - 1)) << endl << endl;
    return (correctlyClassified/(data->get_NumInstances() - 1)); //-1 because leave one out 
    //return rand(); //function stub
}

double leave_one_out_cross_validation_remove(Data_Set* data, vector<int>current_set, int feature_to_remove)
{
    vector<int> setToCheck = current_set;
    setToCheck.erase(remove(setToCheck.begin(), setToCheck.end(), feature_to_remove), setToCheck.end());
    
    vector<Instance> instances = data->get_Instances();
    
    //TEST OUTPUT
    cout << "Checking features: ";
    for (int i = 0; i < setToCheck.size(); i++)
    {
        cout << setToCheck.at(i) + 1 << " ";
    }
    //TEST OUTPUT
    
    double correctlyClassified = 0; 
    
    for (int i = 0; i < data->get_NumInstances(); i++)
    {
        double shortestDistance = INT_MAX; 
        Instance nearestNeighbor; 
        
        for (int j = 0; j < data->get_NumInstances(); j++)
        {
            double tempDistance = 0;
            if (i == j) //leave one out
            {
                continue; 
            }
            else
            {
                tempDistance = calc_euclidian(instances.at(i).get_features(), instances.at(j).get_features(), setToCheck);
                if (tempDistance < shortestDistance)
                {
                    shortestDistance = tempDistance; //update newest shortest
                    nearestNeighbor = data->get_Instances().at(j); 
                }
            }
        } //inner for
        
        if (nearestNeighbor.get_class() == data->get_Instances().at(i).get_class())
        {
            correctlyClassified += 1; //increment # correct
        }
        
    }
    cout << "Accuracy: " << (correctlyClassified/(data->get_NumInstances() - 1)) << endl << endl;
    return (correctlyClassified/(data->get_NumInstances() - 1)); //-1 because leave one out 
}

double leave_one_out_cross_validation_nate(Data_Set* data, vector<int>current_set, int* numFeatWrong, int feature_to_add)
{
    vector<int> setToCheck = current_set;
    setToCheck.push_back(feature_to_add);
    int featuresCurrentlyWrong = 0; 
    
    vector<Instance> instances = data->get_Instances();
    
    //TEST OUTPUT
    cout << "Checking features: ";
    for (int i = 0; i < setToCheck.size(); i++)
    {
        cout << setToCheck.at(i) + 1 << " ";
    }
    //TEST OUTPUT
    
    double correctlyClassified = 0; 
    
    for (int i = 0; i < data->get_NumInstances(); i++)
    {
        double shortestDistance = INT_MAX; 
        Instance nearestNeighbor; 
        
        //TEST 
        //int nearest = 0;
        
        for (int j = 0; j < data->get_NumInstances(); j++)
        {
            double tempDistance = 0;
            if (i == j) //leave one out
            {
                continue; 
            }
            else
            {
                //cout << "Calling euclidian for " << j << "th instance" << endl; //TEST
                tempDistance = calc_euclidian(instances.at(i).get_features(), instances.at(j).get_features(), setToCheck);
                //cout << "tempDistance: " << tempDistance << ". shortestDistance: " << shortestDistance <<  endl; //TEST 
                if (tempDistance < shortestDistance)
                {
                    //cout << "tempDistance < shortestDistnace" << endl;
                    shortestDistance = tempDistance; //update newest shortest
                    nearestNeighbor = data->get_Instances().at(j); 
                    
                    //TEST 
                    //nearest = j;
                }
            }
        } //inner for
        
        //TEST
        //cout << "nearest neighbor index: " << nearest << endl;
        
        if (nearestNeighbor.get_class() == data->get_Instances().at(i).get_class())
        {
            correctlyClassified += 1; //increment # correct
        }
        
        else 
        {
            featuresCurrentlyWrong += 1; 
            
            if (featuresCurrentlyWrong >= *numFeatWrong)
            {
                return 0; //alpha beta pruning
            }
        }
        
    }
    cout << "Accuracy: " << (correctlyClassified/(data->get_NumInstances() - 1)) << endl << endl;
    *numFeatWrong = featuresCurrentlyWrong; 
    return (correctlyClassified/(data->get_NumInstances() - 1)); //-1 because leave one out 
    //return rand(); //function stub
}

void forward_feature_search(Data_Set* data)
{
    vector<int> current_set_of_features;
    vector<int> best_set_so_far;
    double overall_best_accuracy;
    for (int i = 0; i < data->get_NumFeatures(); i++)
    {
        cout << "On the " << i + 1 << "th level of the search tree" << endl;
        int feature_to_add_at_this_level = 0;
        double best_so_far_accuracy = 0;
        
        for (int k = 0; k < data->get_NumFeatures(); k++)
        {
            if (!(find(current_set_of_features.begin(), current_set_of_features.end(), k) != current_set_of_features.end()))
            {
                double accuracy = 0; 
                cout << "Considering adding the " << k + 1 << " feature" << endl;
                accuracy = leave_one_out_cross_validation_add(data, current_set_of_features, (k)); //(k + 1)
                //cout << "TEST accuracy is: " << accuracy << endl; //TEST
                //cout << "Finished leave one out test" << endl;
                if (accuracy > best_so_far_accuracy)
                {
                    best_so_far_accuracy = accuracy;
                    feature_to_add_at_this_level = k;
                }
                
            }
        }
        
        current_set_of_features.push_back(feature_to_add_at_this_level);
        
        //tracking best accuracy entire search
        if(best_so_far_accuracy > overall_best_accuracy)
        {
            best_set_so_far = current_set_of_features;
            overall_best_accuracy = best_so_far_accuracy;
        }
        cout << "On level " << i + 1 << " i added feature " << feature_to_add_at_this_level + 1 << " to current set" << endl; //+1 because index starts at 0
    }
    
    //output best subset
    cout << "Best set of features are ";
    for (int i = 0; i < best_set_so_far.size(); i++)
    {
        cout << best_set_so_far.at(i) + 1 <<  " ";
    }
    cout << "with accuracy " << overall_best_accuracy << endl;
    
    return;
}

void backward_feature_search(Data_Set* data)
{
    vector<int> current_set_of_features;
    for (int i = 0; i < data->get_NumFeatures(); i++) //start with all features
    {
        current_set_of_features.push_back(i);
    }
    vector<int> best_set_so_far;
    double overall_best_accuracy;
    for (int i = 0; i < data->get_NumFeatures(); i++)
    {
        cout << "On the " << i + 1 << "th level of the search tree" << endl;
        int feature_to_remove_at_this_level = 0;
        double best_so_far_accuracy = 0;
        
        for (int k = 0; k < data->get_NumFeatures(); k++)
        {
            if ((find(current_set_of_features.begin(), current_set_of_features.end(), k) != current_set_of_features.end()))
            {
                double accuracy = 0; 
                cout << "Considering removing the " << k + 1 << " feature" << endl;
                accuracy = leave_one_out_cross_validation_remove(data, current_set_of_features, (k)); //(k + 1)
                //cout << "TEST accuracy is: " << accuracy << endl; //TEST
                //cout << "Finished leave one out test" << endl;
                if (accuracy > best_so_far_accuracy)
                {
                    best_so_far_accuracy = accuracy;
                    feature_to_remove_at_this_level = k;
                }
                
            }
        }
        
        current_set_of_features.erase(remove(current_set_of_features.begin(), current_set_of_features.end(), feature_to_remove_at_this_level), current_set_of_features.end());
        
        //tracking best accuracy entire search
        if(best_so_far_accuracy > overall_best_accuracy)
        {
            best_set_so_far = current_set_of_features;
            overall_best_accuracy = best_so_far_accuracy;
        }
        cout << "On level " << i + 1 << " i removed feature " << feature_to_remove_at_this_level + 1 << " from current set" << endl << endl; //+1 because index starts at 0
    }
    
    //output best subset
    cout << "Best set of features are ";
    for (int i = 0; i < best_set_so_far.size(); i++)
    {
        cout << best_set_so_far.at(i) + 1 <<  " ";
    }
    cout << "with accuracy " << overall_best_accuracy << endl;
    
    return;
}

void nates_search(Data_Set* data)
{
    vector<int> current_set_of_features;
    vector<int> best_set_so_far;
    double overall_best_accuracy;
    int numFeatWrong = data->get_NumFeatures(); //set to max at first
    for (int i = 0; i < data->get_NumFeatures(); i++)
    {
        cout << "On the " << i + 1 << "th level of the search tree" << endl;
        int feature_to_add_at_this_level = 0;
        double best_so_far_accuracy = 0;
        
        for (int k = 0; k < data->get_NumFeatures(); k++)
        {
            if (!(find(current_set_of_features.begin(), current_set_of_features.end(), k) != current_set_of_features.end()))
            {
                double accuracy = 0; 
                cout << "Considering adding the " << k + 1 << " feature" << endl;
                accuracy = leave_one_out_cross_validation_nate(data, current_set_of_features, &numFeatWrong, (k)); //(k + 1)
                //cout << "TEST accuracy is: " << accuracy << endl; //TEST
                //cout << "Finished leave one out test" << endl;
                if (accuracy > best_so_far_accuracy)
                {
                    best_so_far_accuracy = accuracy;
                    feature_to_add_at_this_level = k;
                }
                
            }
        }
        
        current_set_of_features.push_back(feature_to_add_at_this_level);
        
        //tracking best accuracy entire search
        if(best_so_far_accuracy > overall_best_accuracy)
        {
            best_set_so_far = current_set_of_features;
            overall_best_accuracy = best_so_far_accuracy;
        }
        cout << "On level " << i + 1 << " i added feature " << feature_to_add_at_this_level + 1 << " to current set" << endl; //+1 because index starts at 0
    }
    
    //output best subset
    cout << "Best set of features are ";
    for (int i = 0; i < best_set_so_far.size(); i++)
    {
        cout << best_set_so_far.at(i) + 1 <<  " ";
    }
    cout << "with accuracy " << overall_best_accuracy << endl;
    
    return;
    return; //function stub
}



int main()
{
    cout << setprecision(16); //testing, cout has default precision of 6
    
    string fileName; 
    int searchType; 
    int numFeatures;
    int numInstances;
    vector<Instance> instances;
    
    cout << "Welcome to Nate Dang's Feature Selection Algorithm." << endl;
    cout << "Type in the name of the file to test: "; 
    cin >> fileName; 
    instances = parseFile(fileName); //training data
    Data_Set data(instances);
    cout << endl << endl;
    cout << "Type the number of the algorithm you want to run." << endl << endl;
    cout << "1)   Forward Selection" << endl;
    cout << "2)   Backward Elimination" << endl;
    cout << "3)   Nate's Special Algorithm" << endl;
    cin >> searchType;
    cout << endl << endl;
    
    if (searchType == 1)
    {
        forward_feature_search(&data);
    }
    
    if (searchType == 2)
    {
        backward_feature_search(&data);
    }
    
    if (searchType == 3)
    {
        nates_search(&data);
    }
    
    return 0;
}
        
    
    
