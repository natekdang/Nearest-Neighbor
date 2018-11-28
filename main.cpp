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
        int class; //two classes for this project
        vector<double> features; //features of each instance
    public: 
        Instance();
        //setters
        void add_feature(double);
        void set_class(int);
        //getters
        void get_features(); 
        void get_class();
        
        void output();
        
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
