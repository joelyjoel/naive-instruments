#pragma once

#include <exception>
#include <iostream>
#include <math.h>

class MonoBuffer
{
    // TODO: Generalise to any number of channels and sample types
    // TODO: rename Sample
    // TODO: Make proper use of c++ const keyword for non-editable views
    // TODO: Create proper move semantics
public:
    /**
     * How many samples are there?
     */
    const int numberOfSamples;

    /**
     * How long is the sampled signal in smp.
     */
    int numberOfFrames()
    {
        return numberOfSamples;
    }

    /**
     * Pointer to the data
     */
    double* data;

    /**
     * Create an empty sampled signal
     */
    MonoBuffer( int numberOfSamples )
    : numberOfSamples( numberOfSamples )
    {
        data    = new double[numberOfSamples];
        isAView = false;
    }

    /**
     * Construct as a view
     */
    MonoBuffer( double* dataPtr, int length )
    : numberOfSamples( length )
    {
        isAView = true;
        data    = dataPtr;
    }

private:
    /**
     * A view is a MonoBuffer instance that points at a sub section of another
     * monobuffer's data. Views must be careful not to release their buffer's from
     * the heap!
     */
    bool isAView;

public:
    ~MonoBuffer()
    {
        if ( !isAView )
            delete data;
    }

    double& atIndex( int index )
    {
        return data[index % numberOfSamples];
    }
    double& operator[]( int index )
    {
        return atIndex( index );
    }
    double operator[]( double index )
    {
        return interpolate( index );
    }

    double interpolate( double index )
    {
        int   i0       = int( index );
        int   i1       = ( i0 + 1 );
        float progress = index - float( i0 );
        return atIndex( i0 ) * ( 1 - progress ) + progress * atIndex( i1 );
    }

    const float sampleRate = 44100;
    double      duration()
    {
        return float( numberOfSamples ) / float( sampleRate );
    }
    double atTime( double time )
    {
        return atIndex( time * sampleRate );
    }
    double operator()( double time )
    {
        return atTime( time );
    };

    double peak()
    {
        double max = 0;
        for ( int i = 0; i < numberOfSamples; ++i )
            if ( abs( data[i] ) > max )
                max = abs( data[i] );
        return max;
    }

    void scale( double scaleFactor )
    {
        for ( int i = 0; i < numberOfSamples; ++i )
            data[i] *= scaleFactor;
    }

    void operator*=( double scaleFactor )
    {
        scale( scaleFactor );
    }
    void operator/=( double scaleFactor )
    {
        scale( 1.0 / scaleFactor );
    }

    MonoBuffer view( int from = 0, int until = 0 )
    {
        if ( until <= 0 )
            until = numberOfSamples - until;
        return MonoBuffer( data + from, until - from );
    }

    MonoBuffer* slice( int from = 0, int until = 0 )
    {
        return view( from, until ).copy();
    }
    MonoBuffer* slice( float from = 0, float to = 0 )
    {
        int fromInt = from * sampleRate;
        int toInt   = to * sampleRate;
        return slice( fromInt, toInt );
    }

    MonoBuffer* copy()
    {
        MonoBuffer* newbuffer = new MonoBuffer( numberOfSamples );
        for ( int i = 0; i < numberOfSamples; ++i )
            newbuffer->data[i] = data[i];
        return newbuffer;
    }

    void normalise()
    {
        scale( 1.0 / peak() );
    }

    void fadeIn( double fadeInDuration )
    {
        int    n     = fadeInDuration * sampleRate;
        double scale = 0;
        double rate  = 1 / float( n );
        for ( int i = 0; i < n; ++i )
        {
            data[i] *= scale;
            scale += rate;
        }
    }
    void fadeOut( double fadeInDuration )
    {
        int    n     = fadeInDuration * sampleRate;
        double scale = 0;
        double rate  = 1 / float( n );
        for ( int i = 0; i < n; ++i )
        {
            data[numberOfSamples - i] *= scale;
            scale += rate;
        }
    }
    void fadeBoth( double fadeInDuration = 0.1, double fadeOutDuration = 0.1 )
    {
        fadeIn( fadeInDuration );
        fadeOut( fadeOutDuration );
    }

    MonoBuffer* repeat( float numberOfRepetitions )
    {
        // TODO: Return using move semantics

        MonoBuffer* newbuffer = new MonoBuffer( numberOfSamples * numberOfRepetitions );

        for ( int i = 0; i < newbuffer->numberOfSamples; ++i )
            newbuffer->data[i] = data[i % numberOfSamples];

        return newbuffer;
    }
};
