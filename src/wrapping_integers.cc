#include "wrapping_integers.hh"

using namespace std;

Wrap32 Wrap32::wrap( uint64_t n, Wrap32 zero_point )
{
  return zero_point+n;
}

uint64_t Wrap32::unwrap( Wrap32 zero_point, uint64_t checkpoint ) const
{
  uint64_t ret=raw_value_-zero_point.raw_value_+((checkpoint>>32)<<32);
  uint64_t t=( 1UL << 32 );
  if(ret<checkpoint){
    if(checkpoint-ret>ret+t-checkpoint){
      ret+=t;
    }
  }else{
    if(ret-checkpoint>checkpoint-(ret-t)){
      ret-=t;
    }
  }
  return ret;
}
