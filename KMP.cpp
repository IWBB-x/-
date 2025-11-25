#include<iostream>
using namespace std;
//next数组的构建
void built_next(int* next,string P){
  //1.初始化
  next[0]=0;
  int j=0;

  //j是前缀的末尾，同时也是前缀长度（存放在next的数值）
  //i是后缀的末尾
  for(int i=1;i<P.size();i++){
 //2. 处理前后缀不同的情况
    while(j>0&&P[i]!=P[j]){
      j=next[j-1];
    }
  //3.处理前后缀相同的情况
    if(P[i]==P[j]){
      j++;  
    }

  //4. 最后更新next数组
    next[i]=j;
  }
}

int KMP(string S,string P){
  int *next=new int[P.size()];
  built_next(next,P);

  int j=0;//P的指针
  for(int i=0;i<S.size();i++){
      while(j>0&&P[j]!=S[i]){
        j=next[j-1];
      }
      if(P[j]==S[i]){
        j++;
      }

      if(j==P.size()){
        return i-j+1;
      }
    }
    return -1;
  }

  int main(){
    string s,p;
    cin>>s;
    cin>>p;

    cout<<KMP(s,p);
    return 0;
  }
