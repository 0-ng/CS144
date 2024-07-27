#include "reassembler.hh"
#include<iostream>
using namespace std;

void Reassembler::insert( uint64_t first_index, string data, bool is_last_substring )
{
  int data_len=data.size();
  int l=max(first_index,writer().bytes_pushed());
  int r=min(first_index+data_len,writer().bytes_pushed()+writer().available_capacity());  
  if(l>=r){
    if(is_last_substring){
      tail=first_index+data_len;
    }
    if(head==tail){
      output_.writer().close();
    }
    return;
  }
  for(int i=l;i<r;i++){
    buffer[i%capacity_]=data[i-first_index];
    buffer_ready[i%capacity_]=true;
  }
  while(buffer_ready[head%capacity_]&&output_.writer().available_capacity()){
    output_.writer().push(string(1,buffer[head%capacity_]));
    buffer_ready[head%capacity_]=false;
    head++;
  }
  if(is_last_substring){
    tail=first_index+data_len;
  }
  if(head==tail){
    output_.writer().close();
  }
}

uint64_t Reassembler::bytes_pending() const
{
  uint64_t ret=0;
  for(uint64_t i=0;i<capacity_;i++){
    if(buffer_ready[(head+i)%capacity_])ret++;
  }
  return ret;
}
