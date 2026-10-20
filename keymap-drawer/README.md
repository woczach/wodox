# keymap-drawer

`wodox.json` is the QMK keymap (`qmk c2json` output, layer names resolved to indices) for [keymap-drawer](https://github.com/caksoylar/keymap-drawer).

    ./keymap-drawer/build.sh   # needs uv; combos are read from combos.yaml

Regenerate the JSON after editing `keymap.c`:

    qmk c2json -kb wodox -km default keyboard/keymaps/default/keymap.c
