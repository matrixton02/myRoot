#pragma once
#include <vector>
#include <string>

using namespace std;

class Histogram2D{
private:
        struct Bin{
            double total_weight=0.0;
            double sum_weights_squared=0.0;
        };
    string name;
    int xbins,ybins;
    double xmin,xmax,ymin,ymax;
    vector<vector<Bin>> bin_data;
    int underflow,overflow;
public:
    Histogram2D(const string& name,int xbins,double xmin,double xmax,int ybins,double ymin,double ymax);
    void fill(double x,double y,double weight=1.0);
    void print();
    double get_bin_center_x(int xbin);
    double get_bin_center_y(int ybin);
    double get_bin_width_x();
    double get_bin_width_y();
    void export_to_csv(const string& filename="hist2d.csv");
    void plot(const string& filename="hist2d.csv",const string& script="src/Histogram2D_plot.py");
};