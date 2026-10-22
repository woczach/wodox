#!/usr/bin/env bash
# Regenerates wodox.yaml + wodox.svg from wodox.json (combos come from combos.yaml).
set -euo pipefail
cd "$(dirname "$0")"
KD="uvx --from keymap-drawer keymap -c config.yaml"
$KD parse -q wodox.json -l Base Dev Tmux Alt Nav Numpad Sym Mouse > wodox.yaml
cat combos.yaml >> wodox.yaml
$KD draw -j ../keyboard/keyboard.json -l LAYOUT wodox.yaml > wodox.svg
