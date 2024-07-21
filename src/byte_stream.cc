#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) : capacity_( capacity ) {}

bool Writer::is_closed() const
{
  return closed;
}

void Writer::push( string data )
{
  int len=data.size();
  for(int i=0;i<len;i++){
    if(head>=tail+BUFFER_SIZE){
      break;
    }
    buffer[head%BUFFER_SIZE]=data[i];
    head+=1;
  }
}

void Writer::close()
{
  closed=true;
}

uint64_t Writer::available_capacity() const
{
  return BUFFER_SIZE-(head-tail);
}

uint64_t Writer::bytes_pushed() const
{
  return head%BUFFER_SIZE;
}

bool Reader::is_finished() const
{
  return closed;
  // return head==tail;
}

uint64_t Reader::bytes_popped() const
{
  return tail%BUFFER_SIZE;
}

string_view Reader::peek() const
{
  if(tail>=head)return "";
  // return buffer[tail%BUFFER_SIZE]
  char c=buffer[tail%BUFFER_SIZE];
  tail+=1;
  return c;
}

void Reader::pop( uint64_t len )
{
  if(tail+len<=head){
    tail+=len;
  }else{
    tail=head;
  }
}

uint64_t Reader::bytes_buffered() const
{
  return head-tail;
}
