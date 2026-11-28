# AI Agent Instructions — template_methods_paper Exemplar

## Why This File Exists

`template_methods_paper` is the **methods-paper exemplar**: the canonical
example of a manuscript whose subject is a methodology rather than results
produced by running one. Deviating from the rules below — introducing a
mock, putting validation or compilation logic in a script, breaking the
`src/`/`infrastructure` boundary, hand-transcribing a number instead of
generating it — breaks the exemplar's purpose.

Read this file before touching any other file in this project.

---

## Rule 1: Read the Hub First

| Document | Governs | Skip consequence |
|---|---|---|
| **This file** | All modifications | Risk all violations below |
| [`architecture.md`](architecture.md) | Any file-boundary change | Risk violating the src/scripts boundary |
| [`testing_philosophy.md`](testing_philosophy.md) | Any test modification | Risk introducing mocks or reducing coverage |
| [`rendering_pipeline.md`](rendering_pipeline.md) | Any manuscript or output change | Risk broken token/figure references in the PDF |
| [`style_guide.md`](style_guide.md) | Any source code modification | Risk impure library code, wrong import layer |
| [`syntax_guide.md`](syntax_guide.md) | Any manuscript `.md` modification | Risk an unresolved `{{TOKEN}}` at render time |

---

## Rule 2: Coverage Gate — ≥90% on `src/`

The suite spans `test_vocabulary.py`, `test_units.py`, `test_model.py`,
`test_validation.py`, `test_compiler.py`, `test_export.py`, `test_trust.py`,
`test_examples_methods.py`, `test_project_paths.py`,
`test_manuscript_variables.py`, and `test_methods_analysis_script.py`. Both
the project `pyproject.toml` and the root pipeline gate coverage at **90%**.
Live test count and coverage live in
[`docs/_generated/COUNTS.md`](https://github.com/docxology/template/blob/87704feae0a4490ef7dad9c931d268e8c30273c2/docs/_generated/COUNTS.md) — do
not hardcode either number in prose.

After modifying any `src/template_methods_paper/methods_dsl/` module, run:

```bash
uv run --no-sync pytest tests \
    --cov=src/template_methods_paper \
    --cov-fail-under=90 --cov-report=term-missing -v
```

If coverage drops, fix the gap — do not delete tests to make the number work.

---

## Rule 3: The Thin Orchestrator Boundary

The DSL model, validation, and compiler work on supplied data. Export
writers in `src/template_methods_paper/methods_dsl/export.py` accept explicit
paths. `_logging.py` is the one declared `infrastructure.*` import exception.

**`scripts/methods_analysis.py`** and **`scripts/z_generate_manuscript_variables.py`**
coordinate the library calls, choose output paths, and handle plotting and
manuscript hydration.

**The boundary test**: if a script implements a validation gate, computes a
plan hash, or constructs DAG scheduling logic inline, it violates the
boundary. Move that computation into `src/template_methods_paper/methods_dsl/` and write a test.

```python
# In a script — BAD
ready = [s for s in method.steps if not s.depends_on]  # scheduling logic

# GOOD
plan = compile_method(method)  # tested src function
```

---

## Rule 4: "Show, Not Tell" Documentation

Use explicit, verifiable references in `docs/manuscript/` files.

**GOOD**: `src/template_methods_paper/methods_dsl/compiler.py::topological_order()` schedules steps
with Kahn's algorithm, breaking ties by ascending `step_id`.

**BAD**: "The compiler figures out a sensible order."

---

## Rule 5: Determinism Policy

`compile_method()` must always produce the same `plan_hash` for the same
`Method` object. Prefer fixed, hand-constructed `Method` fixtures in tests so
the expected gate outcome and plan hash are exact. Assert determinism by
compiling the same object twice and comparing hashes live — never against a
hardcoded hash string literal.

---

## Rule 6: Style and Syntax Guides Govern Their Domains

- **[`style_guide.md`](style_guide.md)** governs `src/template_methods_paper/methods_dsl/*.py`,
  `tests/`, and `scripts/`.
- **[`syntax_guide.md`](syntax_guide.md)** governs `docs/manuscript/*.md`.

Do not apply code-style rules to manuscript prose or vice versa.

---

## Rule 7: Preserve Publication Snapshots and Regenerate Outputs

Keep the tracked `output/` snapshot as publication evidence. Move it aside
in a disposable working checkout before a fresh build. To change a
generated file, change its producer and rerun it.

- To change `output/data/compiled_plans.json`,
  `output/reports/gate_report.json`, `output/reports/trust_chain_report.json`,
  or `output/figures/step_counts.png` → modify `src/template_methods_paper/methods_dsl/` and/or
  `scripts/methods_analysis.py`, then re-run the script.
- To change the rendered PDF → modify the `docs/manuscript/*.md` source, then
  re-render via `scripts/z_generate_manuscript_variables.py` and
  `scripts/pipeline/stage_03_render.py`.

See [`output_conventions.md`](output_conventions.md).

---

## Verification Checklist

```bash
# 1. Tests pass and coverage gate is met
uv run --no-sync pytest tests \
    --cov=src/template_methods_paper --cov-fail-under=90 -q

# 2. No mocks anywhere in tests/
grep -r "unittest.mock\|MagicMock\|@patch\|create_autospec" \
    tests/ || echo "Clean — no mocks found"

# 3. The DSL library has no unsanctioned infrastructure imports
grep -rnE "^(from|import) infrastructure" \
    src/template_methods_paper/methods_dsl/ \
    | grep -v "_logging.py" \
    && echo "VIOLATION — src/template_methods_paper/methods_dsl/ imports infrastructure outside _logging.py" \
    || echo "Clean — only the declared _logging.py exception imports infrastructure"
```
