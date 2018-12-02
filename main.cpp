#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip> //for outputting floats
#include <algorithm> //find k in vector

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
        
    public: 
        Data_Set(vector<Instance> data)
        {
            instances = data; //add data to instances vector
        };
        
        int get_NumInstances() //return size of instances
        {
            return instances.size();
        }
        
        int get_NumFeatures()
        {
            return instances.at(0).get_features().size();
        }
        double leave_one_out_cross_validation(Data_Set, vector<int>, int); 
        
        //void forward_feature_search(Data_Set data);
        

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
        //cout << features.size() << "TEST" << endl;
        int class_type = -1;
        double featToAdd = 0; 
        string inputRow; //temp string  
        
        getline(my_input_file, inputRow);  
        
        //cout << inputRow << endl; //TEST
        
        istringstream ss(inputRow);
        
        //cout << ss.str() << " : ss.str() test" << endl; //TEST
        
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
  
    for (int i = 0; i < instanceVect.size(); i++) //TESTING PARSING
    {
        instanceVect.at(i).output();
    } 
    
    
    cout << "This dataset has " << instanceVect.at(0).get_features().size() << " features with " << instanceVect.size() << " instances." << endl;
    
    return instanceVect;
    
    
}

//helper for nearest neighbor, need to implement
double calc_euclidian(vector<double> a, vector<double> b, vector<double> indices)
{
    double euclidian = 0; 
    for (int i = 0; i < indices.size(); i++) //calculate for only features in indices 
    {
        euclidian += pow(a.at(indices.at(i)) - b.at(indices.at(i)), 2); 
    }
    return sqrt(euclidian);
}

double Data_Set::leave_one_out_cross_validation(Data_Set data, vector<int>current_set, int feature_to_add)
{
    /* iterate through entire set of instances leaving one out each time
    calculate ecludian of each and determine the instance j that is 
    i closest to i, if class_type of both are same then add one to correct
    count, at end of loop return correct count/total instances
    */
    return 0.0; //function stub
}

void forward_feature_search(Data_Set data)
{
    vector<int> current_set_of_features;
    for (int i = 1; i < data.get_NumFeatures(); i++)
    {
        cout << "On the " << i << "th level of the search tree" << endl;
        int feature_to_add_at_this_level = -1;
        int best_so_far_accuracy = 0;
        
        for (int k = 1; k < data.get_NumFeatures(); k++)
        {
            if (!(find(current_set_of_features.begin(), current_set_of_features.end(), k) != current_set_of_features.end()))
            {
                int accuracy = 0; 
                cout << "Considering adding the " << k << " feature" << endl;
                accuracy = data.leave_one_out_cross_validation(data, current_set_of_features, (k + 1));
                
                if (accuracy > best_so_far_accuracy)
                {
                    best_so_far_accuracy = accuracy;
                    feature_to_add_at_this_level = k;
                }
                
            }
        }
        
        current_set_of_features.at(i) = feature_to_add_at_this_level; 
        cout << "On level " << i << " i added feature" << feature_to_add_at_this_level << " to current set" << endl;
        
        return;
    }
}

void backward_feature_search(Data_Set data)
{
    vector<int> current_set_of_features;
    for (int i = 0; i < data.get_NumFeatures(); i++) //start with all features
    {
        current_set_of_features.push_back(i);
    }
    for (int i = 1; i < data.get_NumFeatures(); i++)
    {
        cout << "On the " << i << "th level of the search tree" << endl;
        int feature_to_add_at_this_level = -1;
        int best_so_far_accuracy = 0;
        
        for (int k = 1; k < data.get_NumFeatures(); k++)
        {
            if (!(find(current_set_of_features.begin(), current_set_of_features.end(), k) != current_set_of_features.end()))
            {
                int accuracy = 0; 
                cout << "Considering adding the " << k << " feature" << endl;
                accuracy = data.leave_one_out_cross_validation(data, current_set_of_features, (k + 1));
                
                if (accuracy > best_so_far_accuracy)
                {
                    best_so_far_accuracy = accuracy;
                    feature_to_add_at_this_level = k;
                }
                
            }
        }
        
        current_set_of_features.at(i) = feature_to_add_at_this_level; 
        cout << "On level " << i << " i added feature" << feature_to_add_at_this_level << " to current set" << endl;
        
        return;
    }
}

/*
function  feature_search_demo(data)
 
current_set_of_features = []; % Initialize an empty set
 
for i = 1 : size(data,2)-1 
    disp(['On the ',num2str(i),'th level of the search tree'])
    feature_to_add_at_this_level = [];
    best_so_far_accuracy    = 0;    
    
     for k = 1 : size(data,2)-1 
       if isempty(intersect(current_set_of_features,k)) % Only consider adding, if not already added.
        disp(['--Considering adding the ', num2str(k),' feature'])
        accuracy = leave_one_out_cross_validation(data,current_set_of_features,k+1);
        
        if accuracy > best_so_far_accuracy 
            best_so_far_accuracy = accuracy;
            feature_to_add_at_this_level = k;            
        end        
      end
     end
    
    current_set_of_features(i) =  feature_to_add_at_this_level;
    disp(['On level ', num2str(i),' i added feature ', num2str(feature_to_add_at_this_level), ' to current set'])
        
 end 
end
*/


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
    
    if(searchType == 1)
    {
        forward_feature_search(data);
    }
    

    
    
    
    
    return 0;
}
        
    
    
