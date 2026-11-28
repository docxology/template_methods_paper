# Reproducibility {#sec:reproducibility}

This section describes a fresh analysis and render from a disposable
working checkout. The analysis and manuscript-variable scripts provide the
values used by the reader build.

## Regenerate the standard outputs

The standalone checkout supplies the methods library and the two analysis
entry points. With that checkout registered as a working project in the
pinned template renderer, run the following from the working checkout.
`renderer_root` is the absolute path to the template checkout at commit
`87704feae0a4490ef7dad9c931d268e8c30273c2`. Move the tracked `output/`
directory outside this working checkout before running either generator.
Keep it as the earlier publication snapshot and use a fresh `output/` for
the new build.

```bash
uv sync --locked --extra dev --python 3.14
PYTHONPATH="$renderer_root" uv run --no-sync pytest tests --cov=src/template_methods_paper --cov-fail-under=90
PYTHONPATH="$renderer_root" uv run --no-sync python scripts/methods_analysis.py
PYTHONPATH="$renderer_root" uv run --no-sync python scripts/z_generate_manuscript_variables.py
```

From the pinned template checkout, with its own locked environment installed,
run the render and validation stages.

```bash
uv run --no-sync python scripts/pipeline/stage_03_render.py --project working/template_methods_paper
uv run --no-sync python scripts/pipeline/stage_04_validate.py --project working/template_methods_paper
```

## Generated artifact registry

The standard analysis, hydration, render, and validation commands produce
the following artifacts under `output/`.

| Artifact | Produced by |
|---|---|
| `data/pbspreparation_worklist.md`, `data/pbspreparation_plan.csv`, `data/pbspreparation_graph.mmd`, `data/pbspreparation_plan.json` | `compile_method()` + exporters, for `PBSPreparation` |
| `data/sensorcalibrationsweep_worklist.md`, `data/sensorcalibrationsweep_plan.csv`, `data/sensorcalibrationsweep_graph.mmd`, `data/sensorcalibrationsweep_plan.json` | `compile_method()` + exporters, for `SensorCalibrationSweep` |
| `data/compiled_plans.json` | Per-method plan summary, consumed by `src/template_methods_paper/manuscript_variables.py` |
| `reports/gate_report.json` | `run_all_gates()` tally across both methods |
| `reports/trust_chain_report.json` | `append_record()`/`verify_chain()` demonstration chain |
| `figures/step_counts.png` and `figures/figure_registry.json` | Analysis bar chart and figure metadata |
| `data/manuscript_variables.json` and `manuscript/` | Variable map and hydrated sections from `z_generate_manuscript_variables.py` |
| `pdf/template_methods_paper_combined.pdf`, `web/index.html`, and `slides/` | Enabled Stage 03 editions |
| `reports/validation_report.json` and `reports/rendered_provenance.json` | Stage 04 validation and source binding |

The API glossary, `output/docs/api_glossary.md`, has a separate optional
producer, `scripts/generate_api_docs.py`. Keep any retained publication
artifacts in the saved snapshot alongside their original evidence.

## Determinism

- `compile_method()` is deterministic by construction: the plan hash is
  computed from compact UTF-8 JSON with sorted keys over `method_name`,
  `method_version`, `target`, and each scheduled step's identifying fields.
  See [@sec:methodology] for the exact serialization used to verify an
  exported plan.
- `topological_order()` breaks scheduling ties by ascending `step_id`, so
  the same `Method` object always yields the same step order across
  processes and platforms.
- {{DETERMINISM_CHECK}} — `src/template_methods_paper/manuscript_variables.py::generate_variables`
  recompiles every example method twice at manuscript-build time and
  compares hashes live, so this guarantee is checked on every build, not
  merely asserted once in a test.

## Verification (no hand-transcribed numbers)

Every quantitative claim in [@sec:results] is either a generated variable
sourced from a live analysis output or registered in `data/claim_ledger.yaml` for
evidence-registry validation. The manuscript intentionally does not
hand-transcribe volatile values, so prose and artifacts cannot disagree.
Configuration provenance is injected. The value `{{CONFIG_HASH}}` is the
SHA-256 prefix of `docs/manuscript/config.yaml` at build time, and
`{{GENERATION_TIMESTAMP}}` records when the variables were generated
(honoring `SOURCE_DATE_EPOCH` for byte-reproducible builds).
