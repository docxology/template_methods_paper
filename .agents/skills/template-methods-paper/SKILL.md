---
name: template-methods-paper
description: Methods-paper exemplar — controlled-method specification DSL with staged validation, deterministic compilation, informed by BPL.
version: 0.1.0
author: docxology
license: MIT
tags: [exemplar, methods, dsl, bpl]
---

# template-methods-paper

Project-scoped skill for the standalone methods-paper exemplar.

## When to Use

- Working inside the `template_methods_paper` exemplar — running scripts, editing source,
  or regenerating outputs.
- Forking this exemplar as the starting scaffold for a new research project.
- Validating that the exemplar's contracts (thin-orchestrator, layer boundaries,
  no-mocks testing) still hold after changes.

## Quick Reference

Follow the [quickstart](../../../docs/quickstart.md) for native tests and analysis.
The [render guide](../../../docs/rendering_pipeline.md) has the pinned template
commands for rendering and validation.

## Pitfalls

- **Keep scripts thin.** Business logic belongs in `src/` or shared
  `infrastructure/`, not in `scripts/`.
- **No mocks.** All tests must use real data, real files, and real
  computation.
- **Outputs are disposable.** Never hand-edit `output/` — regenerate from
  source and config.
- **Figure provenance is part of analysis.** `methods_analysis.py` validates
  `step_counts.png` against `src/template_methods_paper/figure_specs.py` before writing
  `output/figures/figure_registry.json`.
- **Check the working directory.** Run native tests and analysis from the
  project checkout. Run the stage scripts from the pinned renderer checkout.

## Cross-refs

- Project contract: [`AGENTS.md`](../../../AGENTS.md)
- README: [`README.md`](../../../README.md)
- TODO: [Maintenance backlog](../../../docs/backlog.md)
- Exemplar roster: [`projects/AGENTS.md`](https://github.com/docxology/template/blob/87704feae0a4490ef7dad9c931d268e8c30273c2/projects/AGENTS.md)
