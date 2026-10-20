#!/usr/bin/env bash
# Regenerates wodox.yaml + wodox.svg from wodox.json (combos come from combos.yaml).
set -euo pipefail
cd "$(dirname "$0")"
KD="uvx --from keymap-drawer keymap -c config.yaml"
$KD parse -q wodox.json -l Base Numpad Sym Nav Mouse Dev Tmux Alt > wodox.yaml
cat combos.yaml >> wodox.yaml
$KD draw -j ../keyboard/keyboard.json -l LAYOUT wodox.yaml > wodox.svg
