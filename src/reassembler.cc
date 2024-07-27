#include "reassembler.hh"

using namespace std;

void Reassembler::insert( uint64_t first_index, string data, bool is_last_substring )
{
  int data_len=data.size();
  int l=0,r=data_len;
  int f=first_index;
  if(first_index<head){
    l=head-first_index;
    f=head;
  }
  if(first_index+data_len>=head+capacity_){
    r=head+capacity_-first_index;
  }
  for(int i=l;i<r;i++){
    buffer[(f+i-l)%capacity_]=data[i];
    buffer_ready[(f+i-l)%capacity_]=true;
  }
  if(is_last_substring&&r==data_len){
    output_.writer().close();
  }
  while(buffer_ready[head%capacity_]&&output_.writer().available_capacity()){
    output_.writer().push(string(1,buffer[head%capacity_]));
    buffer_ready[head%capacity_]=false;
    head++;
  }
}

uint64_t Reassembler::bytes_pending() const
{
  // Your code here.
  for(uint64_t i=0;i<capacity_;i++){
    if(buffer_ready[(head+i)%capacity_])return i;
  }
  return 0;
}
