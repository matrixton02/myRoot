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
        bin_data[bin].sum_square+=value*value*weight;
        bin_data[bin].sum_weights_squared+=weight*weight;
    }
}

double Histogram1D::get_bin_width(){
    return (max_v-min_v)/bins;
}
double Histogram1D::get_bin_center(int bin_index){
    double bin_width=get_bin_width();
    return min_v+(bin_index+0.5)*bin_width;
}
void Histogram1D::print(){
    cout<<"Histogram: "<<name<<" \n";
    for(int i=0;i<bins;i++){
        int bin_width=get_bin_width();
        double bin_start=min_v+i*bin_width;
        double bin_end=bin_start+bin_width;
        cout<<"Bin ["<<bin_start<<", "<<bin_end<<" ];"
            <<"count= "<<bin_data[i].total_weight
            <<", mean value= ";
        if(bin_data[i].total_weight>0){
            double mean=bin_data[i].sum_values/bin_data[i].total_weight;
            double variance=(bin_data[i].sum_square/bin_data[i].total_weight)-(mean*mean);
            double rms=sqrt(variance);
            double error=sqrt(bin_data[i].sum_weights_squared);
            cout<<mean<<", RMS="<<rms<<", Error= "<<error;
        }
        else{
            cout<<"N/A, RMS= N/A, Error=N/A";
        }
        cout<<"\n";
    }
    cout<<"Underflow: "<<underflow<<", Overflow: "<<overflow<<"\n";
}

void Histogram1D::export_to_csv(const string& filename){
    ofstream out(filename);
    double bin_width=(max_v-min_v)/bins;
    out<<"bin_start,bin_end,count,mean_value,rms,error\n";
    for(int i=0;i<bins;i++){
        double bin_start=min_v+i*bin_width;
        double bin_end=bin_start+bin_width;
        out<<bin_start<<","<<bin_end<<","<<bin_data[i].total_weight<<",";
        if(bin_data[i].total_weight>0){
            double mean=bin_data[i].sum_values/bin_data[i].total_weight;
            double variance=(bin_data[i].sum_square/bin_data[i].total_weight)-(mean*mean);
            double rms=sqrt(variance);
            double error=sqrt(bin_data[i].sum_weights_squared);
            out<<mean<<","<<rms<<","<<error;
        }
        else{
            out<<"N/A,N/A,N/A";
        }
        out<<"\n";
    }
    out.close();
}

void Histogram1D::plot(const string& filename,const string& script){
    export_to_csv(filename);
    string command="python "+script+" "+filename;
    system(command.c_str());
}

