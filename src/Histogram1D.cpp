#include "Histogram1D.hpp"
#include <fstream>

Histogram1D::Histogram1D(const string& name,int bins,double min_v,double max_v):name(name), bins(bins), min_v(min_v), max_v(max_v), underflow(0), overflow(0){
    bin_data.resize(bins);
}

void Histogram1D::fill(double value,double weight){
    if(value<min_v){
        underflow++;
    }
    else if(value>max_v){
        overflow++;
    }
    else{
        int bin=static_cast<int>((value-min_v)/(max_v-min_v)*bins);
        bin_data[bin].total_weight+=weight;
        bin_data[bin].sum_values+=value*weight;
    }
}

void Histogram1D::print(){
    cout<<"Histogram: "<<name<<" \n";
    for(size_t i=0;i<bins;i++){
        double bin_start=min_v+i*(max_v-min_v)/bins;
        double bin_end=bin_start+(max_v-min_v)/bins;
        cout<<"Bin ["<<bin_start<<", "<<bin_end<<" ];"
            <<"count= "<<bin_data[i].total_weight
            <<", mean value= ";
        if(bin_data[i].total_weight>0){
            cout<<bin_data[i].sum_values/bin_data[i].total_weight;
        }
        else{
            cout<<"N/A";
        }
        cout<<"\n";
    }
    cout<<"Underflow: "<<underflow<<", Overflow: "<<overflow<<"\n";
}

void Histogram1D::export_to_csv(const string& filename){
    ofstream out(filename);
    double bin_width=(max_v-min_v)/bins;
    out<<"bin_start,bin_end,count,mean_value\n";
    for(size_t i=0;i<bins;i++){
        double bin_start=min_v+i*bin_width;
        double bin_end=bin_start+bin_width;
        out<<bin_start<<","<<bin_end<<","<<bin_data[i].total_weight<<",";
        if(bin_data[i].total_weight>0){
            out<<(bin_data[i].sum_values/bin_data[i].total_weight);
        }
        else{
            out<<"N/A";
        }
        out<<"\n";
    }
    out.close();
}

