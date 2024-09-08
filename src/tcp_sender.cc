#include "tcp_sender.hh"
#include "tcp_config.hh"

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
   ret.RST=false;
   ret.payload="";
   seq+=ret.sequence_length();
   in_flight+=ret.sequence_length();
   check_point+=ret.sequence_length();
   transmit(ret);
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
