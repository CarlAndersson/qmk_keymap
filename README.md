# qmk_keymap
This is my keymap: Colemak, repeat key, caps word, one-shot mods. Five layers in 34 keys!

## Rationale
The main thing which is a bit strange is the left thumb, which homes on a repeat key, and toggles both the nav layers and the number layer.
This is driven by the wish to have one-handed access to both modifiers and numbers, while the right hand is on the mouse.
With a dislike for mod-taps, there's not many other options than one-shots, to the left hand needs access to two layers.
The repeat key is quite new in this layout, but it needs to be prominent to have any use at all.
Hence, a thumb combo for the number layer.

## Layers
Base layer: Colemak with some extra features for shifted punctuation.
Combos are global over all layers.
```
        | Esc |                                       | Tab |
.-----------------------------.         .-----------------------------.
|  q  |  w  |  f  |  p  |  g  |         |  j  |  l  |  u  |  y  |  ⌫  |
|-----+-----+-----+-----+-----|         |-----+-----+-----+-----+-----|
|  a  |  r  |  s  |  t  |  d  |-CapsWrd-|  h  |  n  |  e  |  i  |  o  |
|-----+-----+-----+-----+-----|         |-----+-----+-----+-----+-----|
|  z  |  x  |  c  |  v  |  b  |         |  k  |  m  | , ; | . : | ' " |
.-----------------+-----+-----|         |-----+-----+-----------------.
                  | Nav | Rep | -Enter- |Space| Sym |
                  .-----+-----.         .-----+-----.
                    | Nums |
```
Number layer: numpad on the left and "mathy" symbols on the right.
```
.-----------------------------.        .-----------------------------.
|     |  7  |  8  |  9  |     |        |     |  /  |  \  |  *  |  ⌫  |
|-----+-----+-----+-----+-----|        |-----+-----+-----+-----+-----|
|  0  |  4  |  5  |  6  |  <  |        |  >  |  -  |  =  |  +  |  ^  |
|-----+-----+-----+-----+-----|        |-----+-----+-----+-----+-----|
|     |  1  |  2  |  3  |     |        |     |  ~  |  ,  |  .  |     |
.-----------------+-----+-----|        |-----+-----+-----------------.
                  | --------- |        |     |     |
                  .-----+-----.        .-----+-----.
```
Symbol layer: Has the remaining symbols and spots for Swedish letters.
```
.-----------------------------.        .-----------------------------.
|     |  ?  |  !  |  %  |     |        |     |  |  |  {  |  }  |  å  |
|-----+-----+-----+-----+-----|        |-----+-----+-----+-----+-----|
|  @  |  (  |  )  |  #  |  <  |        |  >  |  _  |  $  |  ä  |  ö  |
|-----+-----+-----+-----+-----|        |-----+-----+-----+-----+-----|
|  &  |  [  |  ]  |     |     |        |     |     |     |     |  `  |
.-----------------+-----+-----|        |-----+-----+-----------------.
                  |     |     |        |     | --- |
                  .-----+-----.        .-----+-----.
```
Navigation layer: Modifiers, navigation, and macros.
Very useful for code mangling.
```
.-----------------------------.        .-----------------------------.
|     |     |     |     |     |        |     |     |     |     |  ⌫  |
|-----+-----+-----+-----+-----|        |-----+-----+-----+-----+-----|
|Shift| Ctrl| Alt | Cmd |     |        |     |  ←  |  ↑  |  →  |     |
|-----+-----+-----+-----+-----|        |-----+-----+-----+-----+-----|
|Undo | Cut |Copy |Paste|Cmnt |        |     |Dednt|  ↓  |Indnt|     |
.-----------------+-----+-----|        |-----+-----+-----------------.
                  | --- |     |        |Space|     |
                  .-----+-----.        .-----+-----.
```
Function layer: Not much more than F-keys at the moment.
```
.-----------------------------.        .-----------------------------.
|     |     |     |     |     |        | F1  | F2  |  F3 | F4  | F5  |
|-----+-----+-----+-----+-----|        |-----+-----+-----+-----+-----|
|     |     |     |     |     |        | F6  | F7  | F8  | F9  | F10 |
|-----+-----+-----+-----+-----|        |-----+-----+-----+-----+-----|
|     |     |     |     |     |        | F11 | F12 | F13 | F14 | F15 |
.-----------------+-----+-----|        |-----+-----+-----------------.
                  | --- |     |        |     | --- |
                  .-----+-----.        .-----+-----.
```

## Setup commands
This repo is not a fork of qmk, like most people do. Instead, qmk is included as a submodule. This means that the files in this repo has to be symlinked into the qmk codebase when compiling. This is handled with a small python script.
```
./qmk_link.py symlink
./qmk_link.py config
./qmk_link.py <boardname>
```

## Commonly used qmk commands
```
qmk compile
qmk flash
```

## List of symbols
I keep forgetting which symbols go into a keymap, so here's a list:
- Numbers (10): 0123456789
- Brackets (8): ()[]{}<>
- "Mathy" symbols (6): =+-*/\
- Punctuation (6): .,:;?!
- Special symbols (7): _#@$%&|
- Accents (5): '"`^~
- Neccessary "functions": space, backspace, enter, tab, escape, modifiers
