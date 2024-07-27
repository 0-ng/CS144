#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ),buffer(string(capacity,' ')) {
  
}

bool Writer::is_closed() const
{
  return closed;
}

void Writer::push( string data )
{
  int len=data.size();
  for(int i=0;i<len;i++){
    if(tail>=head+capacity_){
      break;
    }
    buffer[tail%capacity_]=data[i];
    tail+=1;
  }
}

void Writer::close()
{
  closed=true;
}

uint64_t Writer::available_capacity() const
{
  return capacity_-(tail-head);
}

uint64_t Writer::bytes_pushed() const
{
  return tail;
}

bool Reader::is_finished() const
{
  return closed;
  // return head==tail;
}

uint64_t Reader::bytes_popped() const
{
  return head;
}

string_view Reader::peek() const
{
  if(head>=tail)return "";
  return buffer.substr(head%capacity_,1);
}

void Reader::pop( uint64_t len )
{
  if(head+len<=tail){
    head+=len;
  }else{
    head=tail;
  }
}

uint64_t Reader::bytes_buffered() const
{
  return tail-head;
}
