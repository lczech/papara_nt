

#include <iostream>
#include <iterator>
#include <math.h>
#include <ivymike/time.h>
#include "dtw.h"

template<typename v_t>
inline v_t my_min3( v_t a, v_t b, v_t c ) {
    return std::min( a, std::min(b, c));
}

int main() {
 //     float ax[] = {1,2,3,4,5};
//     float bx[] = {1,2,4};
//     
//     size_t ax_s = sizeof( ax ) / sizeof(float);
//     size_t bx_s = sizeof( bx ) / sizeof(float);
//     
// //     std::cout << "xxx: " << sizeof(ax) / sizeof(float) << " " << sizeof(bx) << " " << XSIZE(ax) << "\n";
//     
//     std::vector<float> a( ax, ax + ax_s );
//     std::vector<float> b( bx, bx + bx_s );

    short v = -1234;
    std::cout << (~v & 0x7fff) << "\n";
    
    typedef short value_t;
//     typedef int value_t;
    const size_t VW = 16 / sizeof(value_t);
    
    std::vector<value_t> a0(256);
    std::vector<value_t> b0(256);
    std::vector<value_t> a(256);
    std::vector<value_t> b(256);
    a[0] = 0;
    b[0] = 0;
    float d = 0;
    std::ofstream os( "in.txt" );
    
    for( int i = 0; i < a.size(); i++ ) {
        //a[i] = (value_t)(sin( (i / float(a.size())) * (16 + 16 * (i/float(a.size()))) * 3.14159) * 128) + i * 0.1;
        if( i % 32 < 16 ) {
            a[i] = 128;
        } else {
            a[i] = 0;
        }
        b[i] = (value_t)(sin( (i / float(a.size())) * 32 * 3.14159) * 128);
        
        //         if( i > 0 ) {
            //             a[i] = a0[i-1] - a0[i];
        //             b[i] = b0[i-1] - b0[i];
        //         }
        //      
        d += fabs(a[i] - b[i]);
        os << a[i] << " " << b[i] << "\n";
    }
    
    if( true )
    {
        //     a = a0;
        //     b = b0;
        size_t ncup = 0;
        ivy_mike::timer t1;
        for( int i = 0; i < 1; i++ ) {
            
            const value_t large_float = 0x7fff;
            float res = dtw_align( a.begin(), a.end(), b.begin(), b.end(), large_float, fabsf, my_min3<float> );
            ncup += a.size() * b.size();
            std::cout << "res: " << res << "\n";
        }
        
        std::cout << ncup << " in " << t1.elapsed() << ": " << (ncup / (t1.elapsed() * 1e9)) << "\n";
    }
    ivy_mike::timer t1;
    size_t ncup = 0;
    
    std::vector<value_t> out(VW);
    dtw_align_ps<value_t> ps;
    aligned_buffer<value_t> aprofile;
    for( int i = 0; i < 1000; i++ ) 
    {
     
        
        
        
        
        
        size_t asize = a.size();
        
        if( aprofile.size() < asize * VW ) {
            aprofile.resize( asize * VW );
        }
        
        for( int i = 0; i < asize; i++ ) {
            std::fill( aprofile(i * VW), aprofile(i*VW + VW), a[i] );
        }
        
        dtw_align_vec<value_t,VW>(ps, aprofile, asize, b.begin(), b.end(), out );
        
        ncup += asize * b.size() * VW;
        
        
    }
    std::copy( out.begin(), out.end(), std::ostream_iterator<value_t>( std::cout, "\n" ));
    std::cout << ncup << " in " << t1.elapsed() << ": " << (ncup / (t1.elapsed() * 1e9)) << "\n";
    return 0;
    
}