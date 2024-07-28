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
  uint64_t b=ret+t;
  uint64_t s=ret-t;
  if(max(b,checkpoint)-min(b,checkpoint)<max(ret,checkpoint)-min(ret,checkpoint)){
    ret=b;
  }
  if(max(s,checkpoint)-min(s,checkpoint)<max(ret,checkpoint)-min(ret,checkpoint)){
    ret=s;
  }
  return ret;
}
