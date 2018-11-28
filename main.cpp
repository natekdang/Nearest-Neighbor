#include <iostream>
#include <vector>

using namespace std;

/*double leave_one_out_cross_validation(data, current_set, feature_to_add)
{
    return rand; //test stub
} */

//helper for nearest neighbor, need to implement
double calc_euclidian(vector<double> a, vector<double> b, vector<double> c);

struct Instance //holds data instances
{
    private:
        int class; //two possible classes for this project
        vector<double> features; //features of each instance
        
    public: 
        Instance()
        {
            class = 0; //must be set to 1 or 2 eventually
        }
        //setters
        void add_feature(double feature_to_add)
        {
            features.push_back(feature_to_add);
            return; 
        }
        void set_class(int class)
        {
            this->class = class; 
            return; 
        }
        //getters
        void get_features()
        {
            return features; 
        }
        void get_class()
        {
            return class; 
        }
        
        void output(); //implement later for trace
        
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

int main()
{
    
}
