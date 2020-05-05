#!/bin/bash
set -euo pipefail

echo "alpha bravo charlie delta echo" | ./render_as_dot RandomBalanceStringSet >  render_as_dot_random_balance.render_as_dot
dot render_as_dot_random_balance.dot -Tpng -o render_as_dot_random_balance.png
cat render_as_dot_random_balance.dot | -Tsvg >render_as_dot_random_balance.svg


