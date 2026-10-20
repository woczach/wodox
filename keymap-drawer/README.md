# keymap-drawer

`wodox.json` is the QMK keymap (`qmk c2json` output, layer names resolved to indices) for [keymap-drawer](https://github.com/caksoylar/keymap-drawer).

    pip install keymap-drawer
    keymap -c keymap-drawer/config.yaml parse -q keymap-drawer/wodox.json -l Base Numpad Sym Nav Mouse Dev L6 Alt > keymap-drawer/wodox.yaml
    keymap -c keymap-drawer/config.yaml draw -j keyboard/keyboard.json -l LAYOUT keymap-drawer/wodox.yaml > keymap-drawer/wodox.svg

Regenerate the JSON after editing `keymap.c`:

    qmk c2json -kb wodox -km default keyboard/keymaps/default/keymap.c
