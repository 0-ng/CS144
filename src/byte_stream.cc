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
  return head==tail;
}

uint64_t Reader::bytes_popped() const
{
  return tail%BUFFER_SIZE;
}

string_view Reader::peek() const
{
  // return buffer[tail%BUFFER_SIZE]
  return buffer.substr(tail%BUFFER_SIZE,1);
}

void Reader::pop( uint64_t len )
{
  tail+=len;
}

uint64_t Reader::bytes_buffered() const
{
  return head-tail;
}
