#include <cmath>
#include <algorithm>

#include "smoothEvolvent.hpp"

using namespace std;

static int _Pow_int(int x, int n)
{
    int val = 1;
    for(int i = 0; i < n; i++)
        val *= x;
    return val;
}

static double Hermit( double y0, double d0, double y1, double d1, double h, double x)
{
  return y0 + (x+h)* (d0 + (x+h)*(d0-(y0-y1)/(-2*h)+
        (x-h)*(d0-2*(y0-y1)/(-2*h)+d1)/(-2*h))/(-2*h));
}

static double HermitDer( double y0, double d0, double y1, double d1, double h, double x)
{
  return pow(h,-3)*(d0*h*(-0.25*h*h-0.5*h*x+0.75*x*x)
                    +d1*h*(-0.25*h*h+0.5*h*x+0.75*x*x)
                    -0.75*h*h*y0+0.75*h*h*y1
                    +0.75*x*x*y0
                    -0.75*x*x*y1);
}

static int node ( int is, int n, int& iq, int nexp, std::vector<int>& iu, std::vector<int>& iv );
static void SmoothEvolventDer( double x, int n, int m,std::vector<double>&y, std::vector<double>&y_, bool );

SmoothEvolvent::SmoothEvolvent(int dimension, int tightness, const double* lb, const double* ub, double smoothness)
      : Evolvent(dimension, tightness, lb, ub)
{
  n = mDimension;
  m = mTightness;
  h = smoothness;
  continuously = h != 1. ?  true : false;
  smoothPointCount = 0;
}

void SmoothEvolvent::GetImage(double x, double y[])
{
  if(mDimension != 1)
  {
    x *= 1 - pow(2., -m*n);
    std::vector<double> y_vec, y_;
    (*this)(x, y_vec, y_);
    std::copy(y_vec.begin(), y_vec.end(), y);
  }
  else
    y[0] = x - 0.5;

  TransformToSearchDomain(y, y);
}

int SmoothEvolvent::GetAllPreimages(const double* p, double xp[])
{
  return 0;
}

void SmoothEvolvent::operator ()( double x, std::vector<double>&y, std::vector<double>&y_ ) const
{
  y.assign( n, .0 );
  y_.assign( n, .0 );
  int l(0),iq(0);
  std::vector<int> iu;
  iu.assign( n, 0 );
  std::vector<int> iv;
  iv.assign( n, 0 );
  int nexp = _Pow_int( 2, n ); // nexp=2**n */
  int mnexp = _Pow_int( nexp, m ); // mnexp=2**(nm)
  double d = 1.0 / mnexp;
  double dh = d * h;
  double xc = 0;
  while (xc < x)
    xc += d;
  if ( ((h > 0) && (h <= .5) && (x > dh) && (x < 1 - d - dh) && ((xc - x < dh) || (xc - x > d - dh))) && continuously)
  {
    smoothPointCount++;

    std::vector<double> y0; y0.assign( n, 0 );
    std::vector<double> y1; y1.assign( n, 0 );
    std::vector<double> y0_; y0_.assign( n, 0 );
    std::vector<double> y1_; y1_.assign( n, 0 );
    double xh = 0;
    if ( xc - x < dh )
    {
      xh += x - xc;
      ::SmoothEvolventDer( xc - dh, n, m, y0, y0_, true );
      ::SmoothEvolventDer( xc + dh, n, m, y1, y1_, true );
    }
    else
    {
      xh += x - xc + d;
      ::SmoothEvolventDer( xc - d - dh, n, m, y0, y0_, true );
      ::SmoothEvolventDer( xc - d + dh, n, m, y1, y1_, true );

    }
    int i0(-1), i1(-1);
    for( int i = 0; i < n; i++ )
    {
      if ( y1[i]!= y0[i] )
      {
        if (i0 == -1 )
          i0 = i;
        else
          i1 = i;
      }
      else
      {
        y[i] = y0[i];
        y_[i] = 0;
      }
    }
    if ( i0 != -1 && i1 != -1 )
    {
      y[i0] = Hermit(y0[i0], y0_[i0], y1[i0], y1_[i0], dh, xh);
      y_[i0] = HermitDer(y0[i0], y0_[i0], y1[i0], y1_[i0], dh, xh);
      y[i1] = Hermit(y0[i1], y0_[i1], y1[i1], y1_[i1], dh, xh);
      y_[i1] = HermitDer(y0[i1], y0_[i1], y1[i1], y1_[i1], dh, xh);
      return;
    }
  }
  ::SmoothEvolventDer( x, n, m, y, y_, continuously );
}

void SmoothEvolvent::minmax( double &a, double & b ) const
{
  a = .0;
  b = 1- pow(2., -m*n);
}

static int node ( int is, int n, int& iq, int nexp, std::vector<int>& iu, std::vector<int>& iv)
{
 /* calculate iu=u[s], iv=v[s], l=l[s] by is=s */
  iq = 0;
  int k1,k2,iff;
  static int l = 0;
  if ( is == 0 )
  {
    l = n-1;
    for ( int i=0; i<n; i++ )
    {
      iu[i]=-1;
      iv[i]=-1;
    }
  }
  else
    if ( is == (nexp-1) )
    {
      l = n-1;
      iu[0] = 1;
      iv[0] = 1;
      for ( int i = 1; i < n; i++ )
      {
        iu[i] = -1;
        iv[i] = -1;
      }
      iv[n - 1]=1;
    }
    else
    {
      iff = nexp;
      k1 = -1;
      for ( int i = 0; i < n; i++ )
      {
        iff /= 2;
        if ( is >= iff )
        {
          if ( (is == iff)&&(is != 1) )  { l = i; iq = -1; }
          is = is - iff;
          k2 = 1;
        }
        else
        {
          k2 = -1;
          if ( (is == (iff-1))&&(is != 0) )  { l = i; iq = 1; }
        }
        iu[i] = iv[i] =-k1 * k2;
        k1 = k2;
      }
      iv[l] *= iq;
      iv[n-1] = -iv[n-1];
    }
    return l;
}

static void SmoothEvolventDer( double x, int n, int m, std::vector<double>&y, std::vector<double>&y_, bool c )
{
  if ( y.size() != n )
    y.assign( n, .0 );
  if ( y_.size() != n )
    y_.assign( n, .0 );
  int l(0),iq(0);
  std::vector<int> iu;
  iu.assign( n, 0 );
  std::vector<int> iv;
  iv.assign( n, 0 );
  int nexp = _Pow_int( 2, n ); // nexp=2**n */
  int mnexp = _Pow_int( nexp, m ); // mnexp=2**(nm)
  double d = 1.0 / mnexp;
  std::vector<int> iw; iw.assign(n,0);
  double xd = x;
  int it = 0;
  double dr = nexp;
  for ( int i = 0; i < n; i++ )
  {
    iw[i] = 1;
    y[i] = 0;
  }
  int k = 0;
  double r = 0.5;
  int ic;
  for ( int j = 0; j < m; j++ )
  {
    if ( x == 1.0 - d )
    {
      ic = nexp-1;
      xd = 0.0;
    }
    else
    {
      xd = xd * nexp;
      ic = (int)xd;
      xd = xd - ic;
    }
    iq = 0;
    l = node( ic, n, iq, nexp, iu, iv );
    int swp = iu[it];
    iu[it] = iu[0];
    iu[0] = swp;
    swp = iv[it];
    iv[it] = iv[0];
    iv[0] = swp;
    if (l == 0)
      l = it;
    else if (l == it)
      l = 0;
    if ((iq > 0)||((iq == 0)&&(ic == 0)))
      k = l;
    else if (iq<0)
    {
      if (it == n-1)
        k = 0;
      else
        k = n - 1;
    }
    r *= 0.5;
    it = l;
    for ( int i = 0; i < n; i++ )
    {
      iu[i] *= iw[i];
      iw[i] *= -iv[i];
      y[i] += r * iu[i];
    }
  }
  if ( c )
  {
    if (ic == (nexp-1))
    {
      y[k] += 2 * iu[k] *r * xd;
      y_[k] = ( (iu[k] > 0) ? 1 : (iu[k] < 0) ? -1 : 0  ) * pow( 2, m * (n - 1) );
    }
    else
    {
      y[k] -= 2 * iu[k] * r * xd;
      y_[k] = - ( (iu[k] > 0) ? 1 : (iu[k] < 0) ? -1 : 0 ) * pow( 2, m * (n - 1) );
    }
    if (x == 1.0 - d)
    {
      std::vector<double> y0; y0.assign(n,0);
      y_[k] = 0;
      ::SmoothEvolventDer( x - d / 2, n, m, y0, y_, true );
    }
  }
}
