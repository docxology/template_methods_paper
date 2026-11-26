# Troubleshooting

## Analysis cannot import infrastructure

Check that `PYTHONPATH` points to the pinned template checkout as shown in the
[quickstart](quickstart.md). Run the analysis commands from the methods-paper
checkout using its installed project environment.

## A token or figure is missing

Run `scripts/methods_analysis.py` and then
`scripts/z_generate_manuscript_variables.py`. The former writes the compiled
plans, reports, PNG and figure registry. The latter resolves tokens in the
source into `output/manuscript/`. Ensure the generated copies come from the
same checkout as the analysis data and config. For a fresh build, start with
an empty output tree in a disposable checkout.

## Citations or slide rendering fail

Check `pandoc --version`, `pandoc-crossref --version`, and
`xelatex --version`. If the combined PDF fails with a JuliaMono font error,
check `kpsewhich JuliaMono-Regular.ttf` in the render shell. Use Pandoc and pandoc-crossref built for the same
Pandoc version. Review the Stage 03 log and consult the
[render instructions](rendering_pipeline.md).

## Project tests report approximately half coverage

Use the [documented coverage scope](quickstart.md). The standalone export
ships duplicate legacy modules under `src/`, while the integration tests
exercise the installed `template_methods_paper` package.
