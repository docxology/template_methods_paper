# `src/template_methods_paper/methods_dsl/`

Tested controlled-method specification library for the methods-paper exemplar.

The analysis script (`scripts/methods_analysis.py`) and the manuscript
variable generator (`src/template_methods_paper/manuscript_variables.py`) call these functions
instead of burying logic in either place, so the methodology the paper
describes is reproducible and unit-tested.

## Files

| File | Role |
| --- | --- |
| `__init__.py` | Public DSL exports re-exported from `template_methods_paper`. |
| `vocabulary.py` | Controlled-vocabulary `StepKind` and `Target` enums; `target_accepts`. |
| `units.py` | Dimensional-safety unit system: `Dimension`, `DimensionError`, `Quantity`. |
| `model.py` | `Method`, `Step`, `Resource`, `Parameter` frozen dataclasses with shape validation. |
| `validation.py` | Four staged gates (`structural_gate`, `semantic_gate`, `plan_gate`, `target_gate`), `run_all_gates`, and the derived `GATE_COUNT`/`GATE_SEQUENCE`. |
| `compiler.py` | `topological_order` (Kahn's algorithm) and `compile_method` — deterministic `Method` → `Plan`. |
| `export.py` | Worklist Markdown, CSV, Mermaid graph, and formatted JSON for a `Plan`. Writers take explicit paths. |
| `trust.py` | `ProvenanceTier` and a hash-chained `StateRecord` history (`append_record`, `verify_chain`). |
| `examples_methods.py` | Two worked example methods (`pbs_preparation_method`, `sensor_calibration_method`) used by the script, tests, and manuscript. |
| `_logging.py` | The one sanctioned `infrastructure.*` import (logging adapter; falls back to stdlib `logging` when forked standalone). |

## See Also

- [`../README.md`](source.md) - project source overview
- [`../AGENTS.md`](../src/AGENTS.md) - source-layer editing rules
- [`AGENTS.md`](../src/template_methods_paper/methods_dsl/AGENTS.md) - subpackage-level rules
