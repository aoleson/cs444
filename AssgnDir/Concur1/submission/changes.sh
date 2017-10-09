#!/bin/bash

# This script was created using this resource: 
# https://mike42.me/blog/2014-04-including-git-commit-history-in-a-latex-document
# Credit goes to the original author of that page.

# Find remote URL for hashes
origin=`git config remote.origin.url`
base=`dirname "$origin"`/`basename "$origin" .git`

# Output LaTeX table in chronological order
echo "\\begin{table}[ht]"
echo "\\centering"
echo "\\resizebox{\textwidth}{!}{"
echo "\\begin{tabular}{l l l}\\textbf{Detail} & \\textbf{Author} & \\textbf{Description}\\\\\\hline"
git log --pretty=format:"\\href{$base/commit/%H}{%h} & %an & %s\\\\\\hline" --reverse
echo "\\end{tabular}}"
echo "\\end{table}"

