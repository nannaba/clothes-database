//
//  Clothes.h
//  teamProject


#ifndef teamProject_Clothes_h
#define teamProject_Clothes_h
#include <iostream>
using namespace std;
class Clothes
{
private:
    string primary;
    string secondary;
    double price;
    string material;
    string type;
public:
    Clothes() {primary = " "; secondary = " "; price = 0; material = " ";type = " ";}
    string getPrimary() const{return primary;}
    string getSecondary()const {return secondary;}
    double getPrice() const{return price;};
    string getMaterial() const{return material;}
    string getType() const{return type;}
    void setPrimary (string pKey) {primary = pKey;}
    void setSecondary (string sKey) {secondary = sKey;}
    void setPrice (double value) {price = value;}
    void setMaterial(string mat) {material = mat;}
    void setType (string cType) {type = cType;}
    
};
#endif
