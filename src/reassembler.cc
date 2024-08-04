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
  for(int i=l,now=l%capacity_;i<r;i++,now++){
    if(now>=capacity_)now-=capacity_;
    buffer[now]=data[i-first_index];
    buffer_ready[now]=true;
  }

  uint64_t now=head%capacity_;
  while(buffer_ready[now]&&output_.writer().available_capacity()){
    output_.writer().push(string(1,buffer[now]));
    buffer_ready[now]=false;
    head++;
    now++;
    if(now>=capacity_)now-=capacity_;
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
  uint64_t begin=head%capacity_;
  for(uint64_t i=0;i<capacity_;i++){
    if(begin>=capacity_)begin-=capacity_;
    if(buffer_ready[begin])ret++;
    begin+=1;
  }
  return ret;
}
