# Render and validate the methods paper

Follow the [quickstart](quickstart.md) to install the two locked environments,
register the project, and run both analysis scripts. Install Pandoc 3.14,
the matching pandoc-crossref 0.3.26 release, and XeLaTeX with Beamer and
BibTeX. The pinned template provides
`scripts/shell/setup-system-deps.sh --check` to check its system prerequisites.

## Prepare the manuscript fonts

The PDF preamble uses JuliaMono. Install the v0.63.2 TTF family or make it
visible to XeLaTeX for this shell. The pinned template's
[acceptance font setup](https://github.com/docxology/template/blob/87704feae0a4490ef7dad9c931d268e8c30273c2/.github/actions/setup-acceptance-documents/action.yml)
records the release archive and checksum.

```bash
font_dir="$(mktemp -d)"
curl -fL https://github.com/cormullion/juliamono/releases/download/v0.63.2/JuliaMono-ttf.tar.gz \
  -o "$font_dir/JuliaMono-ttf.tar.gz"
printf '%s  %s\n' be6517295198ec5c92bdbaad42f4f6f8d83f921d80512b79f54fe036add95c0c \
  "$font_dir/JuliaMono-ttf.tar.gz" | shasum -a 256 -c
tar -xzf "$font_dir/JuliaMono-ttf.tar.gz" -C "$font_dir"
export TTFONTS="$font_dir//:"
kpsewhich JuliaMono-Regular.ttf
```

## Source and build inputs

- [`manuscript/config.yaml`](manuscript/config.yaml) holds the paper title,
  authors, publication metadata and enabled formats. The package declares
  the vocabulary, dimension rules, and gate order in Python.
- [`manuscript/README.md`](manuscript/README.md) lists the ordered source
  files, bibliography, and preamble. The figure reference is relative to
  the canonical source tree.
- `scripts/methods_analysis.py` compiles both examples, runs the gates and
  writes the plan exports, reports, figure and figure registry.
- `scripts/z_generate_manuscript_variables.py` reads the config and analysis
  results, writes `output/data/manuscript_variables.json`, and writes the
  resolved sections into `output/manuscript/`. Set `SOURCE_DATE_EPOCH` to
  control the build timestamp. Stage 03 reruns hydration before rendering.

## Run the pinned renderer

From the pinned template checkout:

```bash
uv run --no-sync python scripts/pipeline/stage_03_render.py --project working/template_methods_paper
uv run --no-sync python scripts/pipeline/stage_04_validate.py --project working/template_methods_paper
```

Find the combined PDF at `output/pdf/template_methods_paper_combined.pdf`,
HTML at `output/web/index.html`, and enabled Beamer decks in `output/slides/`
inside the methods-paper checkout. Check the combined editions for the
compiled-plan table, step-count figure, and resolved citations. Stage 04
writes `output/reports/validation_report.json` and
`output/reports/rendered_provenance.json`. The provenance report records the
source and the render inputs.

The pinned [project integration guide](https://github.com/docxology/template/blob/87704feae0a4490ef7dad9c931d268e8c30273c2/projects/README.md#L208-L223),
[manuscript resolver](https://github.com/docxology/template/blob/87704feae0a4490ef7dad9c931d268e8c30273c2/infrastructure/core/project_paths.py#L59-L75),
and [stage instructions](https://github.com/docxology/template/blob/87704feae0a4490ef7dad9c931d268e8c30273c2/docs/RUN_GUIDE.md#L563-L574)
describe the shared pipeline.
