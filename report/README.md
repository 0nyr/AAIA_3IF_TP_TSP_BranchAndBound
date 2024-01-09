# Latex

Notes about local LaTeX editing and  compiling.

# Commands & tools

## compiling LaTeX

`latexmk main.tex`

### compiling glossary / acronyms

`pdflatex main.tex`

`makeglossaries main`

`pdflatex main.tex`

### LTex Spell Checker

> @ext:valentjn.vscode-ltex

[LTex extension settings | doc](https://valentjn.github.io/ltex/settings.html)

Look inside `.vscode/settings.json` for extension language setting. 

> WARN: Only one language can be used for a given file at a time.

## Pandoc (Markdown to PDF)

`pandoc report/correction.md -o report/correction.pdf --pdf-engine=xelatex`: compile a Markdown file into a PDF file.