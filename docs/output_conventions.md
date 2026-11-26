# Output conventions

The maintained manuscript is under [`docs/manuscript/`](manuscript/README.md).
`output/manuscript/` holds hydrated copies for rendering. Edit the source and
regenerate those copies when the prose or analysis changes.

The checked-in `output/` tree records an earlier publication build, including
`output/docs/` and `output/manuscript/`. Keep its release evidence separate
from a fresh render. Build in a disposable checkout with a fresh `output/`
when checking reproducibility. Keep `data/claim_ledger.yaml` as a source-owned
validation input.

The exported code under `_template_resources/` and the export and publication
tree manifests record the standalone export. The current render uses the
pinned template checkout described in the [quickstart](quickstart.md).

See the [output inventory](output_inventory.md) for producers and artifact paths.
