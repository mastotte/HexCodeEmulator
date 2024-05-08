assignment.pdf: Markdown_Report.md
	pandoc --from=markdown \
	 --to=latex \
	 --toc \
	 -o $@ \
	 $< \
	 --shift-heading-level-by -1 \
	 --number-sections