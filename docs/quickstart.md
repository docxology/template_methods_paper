# Quickstart

Use Git, uv, and Python 3.14 for the checked workflow. The package declares
Python 3.12 or newer. The analysis scripts and their integration tests use
shared infrastructure from a separate, pinned template checkout.

From the root of the methods-paper checkout, clone the renderer and register
a separate copy of the current project commit. Hydration runs inside the
renderer’s project boundary and requires a physical working-project checkout.

```bash
project_root="$(pwd -P)"
git clone https://github.com/docxology/template.git ../template-renderer
renderer_root="$(cd ../template-renderer && pwd -P)"
git -C "$renderer_root" checkout --detach 87704feae0a4490ef7dad9c931d268e8c30273c2
(cd "$renderer_root" && uv sync --locked --no-dev)
mkdir -p "$renderer_root/projects/working"
git clone "$project_root" "$renderer_root/projects/working/template_methods_paper"
cd "$renderer_root/projects/working/template_methods_paper"
git checkout --detach
```

Install the project's locked development dependencies and run the project tests.

```bash
uv sync --locked --extra dev --python 3.14
export PYTHONPATH="$renderer_root"
uv run --no-sync pytest tests --cov=src/template_methods_paper --cov-fail-under=90
```

Coverage is measured for the installed package under `src/template_methods_paper/`.
The exported checkout also contains a legacy copy of those modules directly
under `src/`. The tests import the installed package.

For a clean regeneration, move the tracked `output/` out of the way in
this working checkout before running the generators. Then generate the
analysis outputs and hydrate the manuscript.

```bash
uv run --no-sync python scripts/methods_analysis.py
uv run --no-sync python scripts/z_generate_manuscript_variables.py
```

Continue with the [render and validation commands](rendering_pipeline.md).
