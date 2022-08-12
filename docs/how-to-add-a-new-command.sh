#! /usr/local/bin/bash

cat <<EOF
## How add a new command

To create a new command you need do two things:

  1. Create a new class (probably a subclass of \`AudioCommand\`) in
     \`src/commands/<your-command's-name>.h\`

  2. register the command in \`src/main.cpp\`

Here's an example of a very simple command:

\`\`\`cpp
// src/commands/NoiseCommand.h

$(cat src/commands/NoiseCommand.h)
\`\`\`

For more examples see the files in \`src/commands\`

EOF
