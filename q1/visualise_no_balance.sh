#!/bin/bash
set -euo pipefail

echo "alpha bravo charlie delta echo" | ./render_as_dot UnbalancedStringSet >  render_as_dot_no_balance.render_as_dot
dot render_as_dot_no_balance.dot -Tpng -o render_as_dot_no_balance.png
cat render_as_dot_no_balance.dot | -Tsvg >render_as_dot_no_balance.svg


