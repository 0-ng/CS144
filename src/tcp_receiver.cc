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
  uint64_t fisrt_index=message.seqno.unwrap(zero_point,reassembler_.output_.writer.bytes_pushed());
  reassembler().insert(fisrt_index,message.payload,message.FIN);
}

TCPReceiverMessage TCPReceiver::send() const
{
  // Your code here.
  return {
    Wrap32::wrap( zero_point,reassembler_.output_.writer.bytes_pushed(), zero_point),
    10086,
    false
  };
}
