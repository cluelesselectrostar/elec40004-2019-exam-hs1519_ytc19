#!/bin/bash
set -euo pipefail

echo "alpha bravo charlie delta echo" | ./render_as_dot EqualBalanceStringSet >  render_as_dot_equal_balance.dot
dot render_as_dot_equal_balance.dot -Tpng -o render_as_dot_equal_balance.png
cat render_as_dot_equal_balance.dot | dot -Tsvg >render_as_dot_equal_balance.svg
