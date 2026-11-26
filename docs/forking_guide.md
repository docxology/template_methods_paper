# Adapt the methods-paper exemplar

1. Fork or clone the standalone repository. Register the checkout as described
   in the [quickstart](quickstart.md). If it has a different directory name,
   use that name for the working-project entry and stage arguments.
2. Set the paper metadata in [`manuscript/config.yaml`](manuscript/config.yaml).
   Use [the example config](manuscript/config.yaml.example) as a reference and
   update the project citation metadata in `CITATION.cff`, `.zenodo.json`,
   and `codemeta.json`.
3. Edit the worked examples in
   [`examples_methods.py`](../src/template_methods_paper/methods_dsl/examples_methods.py)
   and extend the controlled vocabulary or dimensions if the new procedure
   requires them.
4. Update the tests and align the evidence inputs
   [`domain_profile.yaml`](../domain_profile.yaml),
   [`experiment_plan.yaml`](../experiment_plan.yaml), and
   [`data/claim_ledger.yaml`](../data/claim_ledger.yaml).
5. Run the [tests and analysis](quickstart.md) and regenerate the
   [report](rendering_pipeline.md) to verify the new claims and figures.

See the [publication notes](standalone.md) for this repository's release
identity and the status report command.
