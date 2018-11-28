#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

/*double leave_one_out_cross_validation(data, current_set, feature_to_add)
{
    return rand; //test stub
} */

//helper for nearest neighbor, need to implement
double calc_euclidian(vector<double> a, vector<double> b, vector<double> indices)
{
    double euclidian = 0; 
    for (int i = 0; i < indices.size(); i++) //calculate for only features in indices 
    {
        euclidian += pow(a.at(indices.at(i)) - b.at(indices.at(i)), 2); 
    }
    return euclidian;
}

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
            cout << "Class: " << class_type << " Features: ";
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
        
    public: 
        Data_Set(vector<Instance> data)
        {
            instances = data; //add data to instances vector
        };
        
        int get_size() //return size of instances
        {
            return instances.size();
        }
        double nearest_neighbor(vector<int>); //pass instances return accuracy

};

double Data_Set::nearest_neighbor(vector<int> data)
{
    return 0.0; //function stub
}

int main()
{
    string fileName; 
    int numFeatures;
    int numInstances;
    
    cout << "Welcome to Nate Dang's Feature Selection Algorithm." << endl;
    cout << "Type in the name of the file to test: "; 
    cin >> fileName; 
    cout << endl << endl;
    cout << "Type the number of the algorithm you want to run." << endl << endl;
    cout << "1)   Forward Selection" << endl;
    cout << "2)   Backward Elimination" << endl;
    cout << "3)   Nate's Special Algorithm" << endl;
    
    //testing ifstream
    ifstream my_input_file;
    my_input_file.open(fileName.c_str());
    vector<Instance> instanceVect;
    
    while (my_input_file.good())
    {
        Instance newInst; 
        vector<double> features; 
        int type; 
        double featToAdd;
        
        string inputRow;
        getline(my_input_file, inputRow);  
        
        //cout << inputRow << endl;
        
        istringstream parse(inputRow);
        
        parse >> type;
        
        newInst.set_class(type);
        
        while(parse >> featToAdd)
        {
            newInst.add_feature(featToAdd);         
        }
        
        instanceVect.push_back(newInst);                                 
    }
    my_input_file.close();
  
    for (int i = 0; i < instanceVect.size(); i++)
    {
        instanceVect.at(i).output();
    } 
    
    
     cout << "This dataset has " << numFeatures << " features with " << numInstances << " instances." << endl;
    
    return 0;
}
        
    
    
