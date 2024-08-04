#include "tcp_receiver.hh"
#include<stdint.h>

using namespace std;

void TCPReceiver::receive( TCPSenderMessage message )
{
  if(is_rst){
    return;
  }
  if(message.RST){
    is_rst=true;
    return;
  }
  // size_t data_len=message.sequence_length;
  if(message.SYN){
    is_syn=true;
    zero_point=message.seqno;
    // data_len-=1;
  }
  uint64_t fisrt_index=message.seqno.unwrap(zero_point,reassembler_.fisrt_reassemble());
  if(!message.SYN){
    if(fisrt_index==0)return;
    fisrt_index-=1;
  }
  // if(message.FIN){
  //   data_len-=1;
  // }
  reassembler_.insert(fisrt_index,message.payload,message.FIN);
}

TCPReceiverMessage TCPReceiver::send() const
{
  TCPReceiverMessage ret;
  
  ret.RST=is_rst;
  
  size_t window_size=UINT16_MAX;
  if(reader().get_capacity()<window_size){
    window_size=reader().get_capacity();
  }
  window_size-=reader().bytes_buffered();
  ret.window_size=window_size;

  if(is_syn){
    ret.ackno=Wrap32::wrap(1+reassembler_.writer().is_closed()+reassembler_.fisrt_reassemble(),zero_point);
  }
  return ret;
}
