#include <iostream>
using namespace std;

int main()
{
    string mNames[5];
    double mPrices[5];
    int mQuants[5];
    bool isExpired[5];
    int mExpDate[5][2];
    
    string expMeds [5];
    int numExpMeds = 0;
    
    int losses = 0;
    cout<<"-- Please enter the mediciens names as one  word only and thier price, quantity, expiry month and expiry year --\n";
    for(int i = 0 ; i < 5 ; i++)
    {
        cout<<"Enter medicine "<<i+1<<" name: ";
        cin>>mNames[i];
        
        cout<<"Enter "<<mNames[i]<<"\'s price: ";
        cin>>mPrices[i];
        
        cout<<"Enter "<<mNames[i]<<"\'s quantity: ";
        cin>>mQuants[i];
        
        cout<<"Enter "<<mNames[i]<<"\'s expiry month: ";
        cin>>mExpDate[i][0];
        
        cout<<"Enter "<<mNames[i]<<"\'s expiry year: ";
        cin>>mExpDate[i][1];
        
        if(mExpDate[i][1] > 2019)
            isExpired[i] = false;
        else if(mExpDate[i][1] == 2019)
        {
            if(mExpDate[i][0] > 4)
                isExpired[i] = false;
            else
                isExpired[i] = true;
            
        }
        else
            isExpired[i] = true;
            
            
        if(isExpired[i]){
            losses += mQuants[i] * mPrices[i];
            numExpMeds++;
            expMeds[numExpMeds - 1] = mNames[i];
        }
            
        cout<<"\n\n\n";
    }
    
    cout<<"Total losses from expired mediciens = " << losses <<endl<<endl<<endl;
    
    
    cout<<"Expired mediciens \n ----------------\n";
    for(int i = 0 ; i < numExpMeds ; i++)
        cout<<expMeds[i]<<endl;
}
