#include "tcp_receiver.hh"

using namespace std;

void TCPReceiver::receive( TCPSenderMessage message )
{
  // if(message.RST){
  //   reassembler_.writer().set_error();
  //   return;
  // }
  // size_t data_len=message.sequence_length;
  if(message.SYN){
    is_receive=true;
    zero_point=message.seqno;
    // data_len-=1;
  }
  uint64_t fisrt_index=message.seqno.unwrap(zero_point,reassembler_.fisrt_reassemble());
  if(!message.SYN){
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
  ret.RST=false;
  ret.window_size=(uint16_t)(reader().get_capacity());
  if(is_receive){
    ret.ackno=Wrap32::wrap(1+reassembler_.fisrt_reassemble(),zero_point);
  }
  return ret;
}
