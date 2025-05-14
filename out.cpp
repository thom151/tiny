#include <iostream>
int main() {
float nums;
std::string name;
float a;
float b;
float c;
std::string greet;
std::cout<<"How many fibonacci numbers do you want? ";
std::cin >> nums;
std::cout<<"what's your name? ";
std::cin >> name;
a=0;
b=1;
c=0;
while(nums>0){
std::cout<<a;
c=a+b;
a=b;
b=c;
nums=nums-1;
}
std::cout<<"\n";
greet="Hello ";
std::cout<<greet+name;
std::cout<<"\n";
return 0;
}
