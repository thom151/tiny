#include <iostream>
int main() {
float nums;
float a;
float b;
float c;
std::cout<<"How many fibonacci numbers do you want?";
std::cin >> nums;
std::cout<<"";
a=0;
b=1;
while(nums>0){
std::cout<<a;
c=a+b;
a=b;
b=c;
nums=nums-1;
}
return 0;
}
