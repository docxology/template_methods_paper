# Reproducibility {#sec:reproducibility}

This section explains how to regenerate every artifact in the study from a
clean checkout. The exemplar's reproducibility guarantee is structural: each
result is produced by a tested function and a thin script, then injected
into the manuscript by generated-variable substitution — never transcribed
by hand.

## How to regenerate everything

The standalone checkout supplies the methods library and the two analysis
entry points. With that checkout registered as a working project in the
pinned template renderer, run the following from the working checkout.
`renderer_root` is the absolute path to the template checkout at commit
`87704feae0a4490ef7dad9c931d268e8c30273c2`.

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

The analysis script writes the following artifacts under
`output/`:

| Artifact | Produced by |
|---|---|
| `data/pbspreparation_worklist.md`, `data/pbspreparation_plan.csv`, `data/pbspreparation_graph.mmd`, `data/pbspreparation_plan.json` | `compile_method()` + exporters, for `PBSPreparation` |
| `data/sensorcalibrationsweep_worklist.md`, `data/sensorcalibrationsweep_plan.csv`, `data/sensorcalibrationsweep_graph.mmd`, `data/sensorcalibrationsweep_plan.json` | `compile_method()` + exporters, for `SensorCalibrationSweep` |
| `data/compiled_plans.json` | Per-method plan summary, consumed by `src/template_methods_paper/manuscript_variables.py` |
| `reports/gate_report.json` | `run_all_gates()` tally across both methods |
| `reports/trust_chain_report.json` | `append_record()`/`verify_chain()` demonstration chain |
| `figures/step_counts.png` | Step-count bar chart |
| `data/manuscript_variables.json` | Every generated-variable value, written by `z_generate_manuscript_variables.py` |

The `output/` tree is disposable and regenerated on every run; it is not the
source of truth.

## Determinism

- `compile_method()` is deterministic by construction: the plan hash is
  computed from a canonical, sort-keys JSON payload over `method_name`,
  `method_version`, `target`, and each scheduled step's identifying fields —
  never from a wall-clock timestamp or a UUID.
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
