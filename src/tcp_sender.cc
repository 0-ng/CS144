#include "tcp_sender.hh"
#include "tcp_config.hh"
#include<string>
using namespace std;

uint64_t TCPSender::sequence_numbers_in_flight() const
{
  return in_flight;
}

uint64_t TCPSender::consecutive_retransmissions() const
{
  // Your code here.
  return {};
}

void TCPSender::push( const TransmitFunction& transmit )
{
   TCPSenderMessage ret=make_empty_message();
   ret.SYN=(seq==isn_);
   ret.FIN=false;
   string v=reader().peek();
  //  reader().pop(v.size());
   ret.payload=v;
   size_t seq_len=ret.sequence_length();
   if(seq_len==0){
    return;
   }
   transmit(ret);
   
   seq=seq+(uint32_t)(seq_len);
   in_flight+=seq_len;
   check_point+=seq_len;
}

TCPSenderMessage TCPSender::make_empty_message() const
{
  TCPSenderMessage ret;
  ret.seqno=seq;
  ret.RST=rst;
  return ret;
}

void TCPSender::receive( const TCPReceiverMessage& msg )
{
  if(msg.ackno.has_value()){
    if(!msg.ackno.value().bigger(ack,isn_,check_point)){
      return;
    }
    in_flight-=msg.ackno.value().sub(ack,isn_,check_point);
    ack=msg.ackno.value();
  }
}

void TCPSender::tick( uint64_t ms_since_last_tick, const TransmitFunction& transmit )
{
  // Your code here.
  (void)ms_since_last_tick;
  (void)transmit;
  (void)initial_RTO_ms_;
}
