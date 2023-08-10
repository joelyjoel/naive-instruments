#include "../core.h"
#include "Metronome.h"
#include "Resetter.h"

class MetronomicResetter : public Patch<double>
{
private:
    std::shared_ptr<Metronome> metronome = std::make_shared<Metronome>();
    std::shared_ptr<Resetter>  resetter  = std::make_shared<Resetter>();

public:
    FrameStreamConsumer<double>& input = exposeInput( resetter->input );
    FrameStreamConsumer<double>& bpm   = exposeInput( metronome->bpm );

    MetronomicResetter()
    {
        resetter->trigger << metronome;
        exposeOutput( resetter );
    }

    std::string label() override
    {
        return "MetronomicResetter";
    }
};
