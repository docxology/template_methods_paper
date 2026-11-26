# Output inventory

Paths are relative to the methods-paper checkout.

| Output | Producer |
| --- | --- |
| `output/data/*_worklist.md`, `*_plan.csv`, `*_graph.mmd`, and `*_plan.json` | Analysis exports for the two compiled methods |
| `output/data/compiled_plans.json` | Analysis summary with each method's target, step count, and plan hash |
| `output/reports/gate_report.json` and `trust_chain_report.json` | Analysis gate tally and example provenance-chain verification |
| `output/docs/api_glossary.md` | Optional `scripts/generate_api_docs.py` glossary |
| `output/figures/step_counts.png` and `figure_registry.json` | Analysis bar chart and figure metadata |
| `output/data/manuscript_variables.json` and `output/manuscript/` | Variable generation and resolved manuscript copies |
| `output/pdf/template_methods_paper_combined.pdf`, `output/web/index.html`, and `output/slides/` | Shared Stage 03 publication editions |
| `output/reports/validation_report.json` and `rendered_provenance.json` | Shared Stage 04 validation and provenance |

See [output conventions](output_conventions.md) for the role of committed
snapshots and [rendering](rendering_pipeline.md) to regenerate the editions.
