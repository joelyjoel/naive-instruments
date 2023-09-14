#include "../core.h"
#include "../parsing/RhythmString.h"
#include <vector>

using std::cerr;
using std::vector, std::string;

// TODO: Refactor as two classes. A rhythm class, and a RhythmPlayer :
// Signal<bool> class

class Rhythm : public FrameStream<bool>
{

public:
    FrameStreamConsumer<double> bpm{ this, "bpm/bpm" };

    Rhythm( vector<float> durations )
    : durations( durations )
    {
    }

private:
    vector<float> durations;
    double        elapsed = 0;
    int           index   = 0;

    const double k = 1.0 / ( 60.0 * sampleRate );

protected:
    void action() override
    {
        elapsed += bpm.readFrame() * k;
        if ( elapsed > durations[index] )
        {
            output[0] = true;
            do
            {
                elapsed -= durations[index];
                index = ( index + 1 ) % durations.size();
            } while ( elapsed > durations[index] );
        }
        else
            output[0] = false;
    }

public:
    static std::shared_ptr<Rhythm> parse( const string& str )
    {
        return std::make_shared<Rhythm>( RhythmString::parse( str ) );
    }


public:
    std::ostream& describe( std::ostream& out )
    {
        for ( float duration : durations )
            out << duration << "b ";
        return out;
    }
};

std::ostream& operator<<( std::ostream& out, Rhythm& rhythm );
