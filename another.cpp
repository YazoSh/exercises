#include <iostream>
using namespace std;

int main()
{
    string names[7];
    double salary[7];

    int sum = 0;

    int max = 0,min = 0;
    for(int i = 0 ; i < 7 ; i++)
    {
        cout<<"Enter employee " << i + 1 << " name: ";
        cin>>names[i];

        cout<<"Enter " << names[i] << "\'s salary: ";
        cin>>salary[i];

        sum += salary[i];
        cout<<"\n";
        if(salary[max] < salary[i])
            max = i;
        if(salary[min] > salary[i])
            min = i;
    }
    cout<<"Employee            Salary\n"<<
          "---------           -------\n";
    for(int i = 0 ; i < 7 ; i++)
    {
        cout<<names[i]<<"           "<<salary[i]<<endl;
    }
    cout<<"-----------------------------\n"<<
    "Total salaries: " << sum <<endl<<
    "Average salaries: " << sum/7.0<<endl<<
    "Employee name with the highest salary : " <<names[max]<<endl<<
    "Employee name with the lowest salary : " <<names[min]<<endl;


}
