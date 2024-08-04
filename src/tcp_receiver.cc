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
    zero_point=message.seqno;
    // data_len-=1;
  }
  // if(message.FIN){
  //   data_len-=1;
  // }
  // uint64_t fisrt_index=message.seqno.unwrap(zero_point,reassembler_.output_.writer.bytes_pushed());
  uint64_t fisrt_index=message.seqno.unwrap(zero_point,0);
  reassembler_.insert(fisrt_index,message.payload,message.FIN);
}

TCPReceiverMessage TCPReceiver::send() const
{
  // Your code here.
  return {
    // Wrap32::wrap( zero_point,reassembler_.output_.writer.bytes_pushed(), zero_point),
    Wrap32::wrap(0,zero_point),
    reader().get_capacity(),
    false
  };
}
