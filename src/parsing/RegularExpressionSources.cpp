#include "RegularExpressionSources.h"

const string RegularExpressionSources::naturalNumber = "\\d+";
const string RegularExpressionSources::integer = "(-|+)? ?" + naturalNumber;
const string RegularExpressionSources::word = "\\w+";
const string RegularExpressionSources::unit = "%|(?:\\w+)?";
const string RegularExpressionSources::ignoreWhitespace = "\\s*";

const string RegularExpressionSources::positiveDecimal =
    naturalNumber + "\\." + naturalNumber;
const string RegularExpressionSources::positivePointNumber =
    "\\." + naturalNumber;

const string RegularExpressionSources::number =
    "-?" + Bracket(Or(naturalNumber, positiveDecimal, positivePointNumber));

const string RegularExpressionSources::numberWithUnit =
    Capture(number) + ignoreWhitespace + Capture(unit);

// Control Signals
const string RegularExpressionSources::controlSequenceTempoInstruction =
    numberWithUnit + ":";
const string RegularExpressionSources::controlSequenceValueInstruction =
    numberWithUnit;
const string RegularExpressionSources::controlSequenceGlideInstruction = "~";
const string RegularExpressionSources::controlSequenceRestInstruction = "_";
const string RegularExpressionSources::controlSequenceInstruction =
    Or(controlSequenceTempoInstruction, controlSequenceValueInstruction,
       controlSequenceGlideInstruction, controlSequenceRestInstruction);

const string RegularExpressionSources::controlSequence =
    Kleene(Capture(controlSequenceInstruction) + ignoreWhitespace);
