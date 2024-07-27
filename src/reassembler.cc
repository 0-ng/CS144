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
    vis[(f+i-l)%capacity_]=true;
  }
  if(is_last_substring&&r==data_len){
    output_.writer().close();
  }
  for(vis[head%capacity_]){
    output_.writer().push(buffer[head%capacity_]);
    vis[head%capacity_]=false;
    head++;
  }
}

uint64_t Reassembler::bytes_pending() const
{
  // Your code here.
  for(int i=0;i<capacity_;i++){
    if(vis[(head+i)%capacity_])return i;
  }
  return capacity_;
}
