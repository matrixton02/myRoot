#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

class Histogram1D{
    private:
        struct Bin{
            double total_weight=0.0;
            double sum_values=0.0;
            double sum_square=0.0;
            double sum_weights_squared=0.0;
        };
        string name;
        int bins;
        double min_v,max_v;
        vector<Bin> bin_data;
        int underflow;
        int overflow;
    public:
        Histogram1D(const string& name,int bins,double min_v,double max_v);
        void fill(double value,double weight=1.0);
        void print();
        void export_to_csv(const string& filename);
        double get_bin_center(int bin_index);
        double get_bin_width();
        void plot(string& filename,const string& script="Histogram1D_plot.py");
};
