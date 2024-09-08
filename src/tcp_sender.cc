#include "tcp_sender.hh"
#include "tcp_config.hh"
#include <cstdint>
#include <string>
#include <string_view>
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
   string_view v=writer().reader().peek();
   uint64_t len=v.size()
   if(ret.sequence_length()+len>window_size){
    len=window_size-ret.sequence_length();
   }
   writer().reader().pop(len);
   ret.payload=v.substr(0,len);
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
  window_size=msg.window_size;
  if(window_size<1){
    window_size=1;
  }
}

void TCPSender::tick( uint64_t ms_since_last_tick, const TransmitFunction& transmit )
{
  // Your code here.
  (void)ms_since_last_tick;
  (void)transmit;
  (void)initial_RTO_ms_;
}
