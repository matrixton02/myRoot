#include "Histogram2D.hpp"
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <iostream>

using namespace std;

Histogram2D::Histogram2D(const string& name,int xbins,double xmin,double xmax,int ybins,double ymin,double ymax):name(name),xbins(xbins),xmin(xmin),xmax(xmax),ybins(ybins),ymin(ymin),ymax(ymax),underflow(0),overflow(0){
    bin_data.resize(xbins,vector<Bin>(ybins));
}

void Histogram2D::fill(double x,double y,double weight){
    if(x<xmin || x>=xmax || y<ymin || y>=ymax){
        if(x<xmin || y<ymin){
            underflow++;
        }
        else{
            overflow++;
        }
    }

    int xbin=static_cast<int>((x-xmin)/(xmax-xmin)*xbins);
    int ybin=static_cast<int>((y-ymin)/(ymax-ymin)*ybins);

    Bin& bin=bin_data[xbin][ybin];
    bin.total_weight+=weight;
    bin.sum_weights_squared+=weight*weight;
}

double Histogram2D::get_bin_width_x(){
    return (xmax-xmin)/xbins;
}

double Histogram2D::get_bin_width_y(){
    return (ymax-ymin)/ybins;
}

double Histogram2D::get_bin_center_x(int xbin){
    return xmin+(xbin+0.5)*get_bin_width_x();
}

double Histogram2D::get_bin_center_y(int ybin){
    return ymin+(ybin+0.5)*get_bin_width_y();
}

void Histogram2D::print(){
    cout<<"Histogram2D: "<<name<<"\n";
    for(int i=0;i<xbins;i++){
        for(int j=0;j<ybins;j++){
            double xcenter=get_bin_center_x(i);
            double ycenter=get_bin_center_y(j);
            const Bin& bin=bin_data[i][j];
            cout<<"Bin ("<<i<<", "<<j<<") "<<"center=("<<xcenter<<", "<<ycenter<<") "<<"count= "<<bin.total_weight<<", error="<<sqrt(bin.sum_weights_squared)<<"\n";
        }
    }
    cout<<"Undeflow: "<<underflow<<", Overflow: "<<overflow<<"\n";

}
void Histogram2D::export_to_csv(const string& filename){
    ofstream out(filename);
    out<<"xbin_center,ybin_center,count,error\n";
    for(int i=0;i<xbins;i++){
        double xcenter=get_bin_center_x(i);
        for(int j=0;j<ybins;j++){
            double ycenter=get_bin_center_y(j);
            const Bin& bin=bin_data[i][j];
            out<<xcenter<<","<<ycenter<<","<<bin.total_weight<<","<<sqrt(bin.sum_weights_squared)<<"\n";
        }
    }
    out.close();
}

void Histogram2D::plot(const string& filename,const string& script){
    export_to_csv(filename);
    string command="python "+script+" "+filename;
    system(command.c_str());
}