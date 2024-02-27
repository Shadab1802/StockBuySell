#include<iostream>
#include<tuple>
#include<vector>
using namespace std;

tuple<int,int,int> FindMaxCrossingSubarray(vector<int> &arr,int low,int mid,int high){
    int left_sum=INT_MIN;
    int left_low=0;
    int sum=0;
    for(int i=mid;i>=low;i--){
        sum+=arr[i];
        if(sum>left_sum){
            left_sum=sum;
            left_low=i;
        }
    }

    int right_sum=INT_MIN;
    int right_high=0;
    sum=0;
    for(int i=mid+1;i<=high;i++){
        sum+=arr[i];
        if(sum>right_sum){
            right_sum=sum;
            right_high=i;
        }
    }
    return {left_low,right_high,right_sum+left_sum};
}

tuple<int,int,int> FindMaximunSubarray(vector<int> &arr ,int low,int high){
    if(high==low){return {low,high,arr[low]};}
    else{
        int mid=(high+low)/2;
        int left_low,left_high,left_sum;
        tie(left_low,left_high,left_sum)=FindMaximunSubarray(arr,low,mid);//0 0 13
        int right_low,right_high,right_sum;
        tie(right_low,right_high,right_sum)=FindMaximunSubarray(arr,mid+1,high);// 2 2 -25
        int cross_low,cross_high,cross_sum;
        tie(cross_low,cross_high,cross_sum)=FindMaxCrossingSubarray(arr,low,mid,high);

        if(left_sum>=right_sum && left_sum>=cross_sum){return {left_low,left_high,left_sum};}
        else if(right_sum>=left_sum && right_sum>=cross_sum){return {right_low,right_high,right_sum};}
        else{return {cross_low,cross_high,cross_sum};}
    }
}
  
int main()
{
    vector<int> prices;
    vector<int> subarray;
    cout<<"Enter negative number to stop taking price as input"<<endl;
    int inp=1;
    cout<<"Enter prices: ";
    
    while(inp>=0){
        cin>>inp;
        prices.push_back(inp);
    }

    for(int i=1;i<prices.size();i++){subarray.push_back(prices[i]-prices[i-1]);}
    
    int i,j,sum;
    tie(i,j,sum)=FindMaximunSubarray(subarray,0,subarray.size()-1);

    cout<<"Maximum Profit: "<<prices[j+1]-prices[i];
    return 0;
}