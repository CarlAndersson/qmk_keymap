# qmk_keymap
This is my keymap: Colemak, repeat key, caps word, one-shot mods. Five layers in 34 keys!

## Rationale
- Space and Capitalize should not be on the same hand, since space+capital is very frequent and would be a very annoying bigram.
- "Modifier" should be on the left to have easy access to the typical copy+paste stuff
- Main thumbs should be space and backspace
- Secondary thumbs should be capitalize and modifier

## Layers
Base layer: Colemak with some extra features for shifted punctuation.
Combos are global over all layers.
```
        | Esc |                                       | Tab |
.-----------------------------.         .-----------------------------.
|  q  |  w  |  f  |  p  |  g  |         |  j  |  l  |  u  |  y  | - _ |
|-----+-----+-----+-----+-----|         |-----+-----+-----+-----+-----|
|  a  |  r  |  s  |  t  |  d  |         |  h  |  n  |  e  |  i  |  o  |
|-----+-----+-----+-----+-----|         |-----+-----+-----+-----+-----|
|  z  |  x  |  c  |  v  |  b  |         |  k  |  m  | , ; | . : | ' " |
.-----------------+-----+-----|         |-----+-----+-----------------.
                  | Mod |Space|         |Bspce| Cap |
                  | Nav | Num | -Enter- | Sym |     |
                  .-----+-----.         .-----+-----.
```
Number layer: numpad on the left and "mathy" symbols on the right.
```
.-----------------------------.        .-----------------------------.
|     |  7  |  8  |  9  |     |        |  j  |  /  |  \  |  *  |  -  |
|-----+-----+-----+-----+-----|        |-----+-----+-----+-----+-----|
|  0  |  4  |  5  |  6  |  <  |        |  >  |  -  |  =  |  +  |  ^  |
|-----+-----+-----+-----+-----|        |-----+-----+-----+-----+-----|
|     |  1  |  2  |  3  |     |        |     |     |  ,  |  .  |  `  |
.-----------------+-----+-----|        |-----+-----+-----------------.
                  |     | --- |        |     |     |
                  .-----+-----.        .-----+-----.
```
Symbol layer: Has the remaining symbols and spots for Swedish letters.
```
.-----------------------------.        .-----------------------------.
|     |  {  |  }  |  %  |     |        |     |  |  |  &  |  å  |  ä  |
|-----+-----+-----+-----+-----|        |-----+-----+-----+-----+-----|
|  @  |  (  |  )  |  #  |  $  |        |     |  ~  |  ?  |  !  |  ö  |
|-----+-----+-----+-----+-----|        |-----+-----+-----+-----+-----|
|     |  [  |  ]  |     |     |        |     |     |     |     |     |
.-----------------+-----+-----|        |-----+-----+-----------------.
                  |     |     |        | --- |     |
                  .-----+-----.        .-----+-----.
```
Navigation layer: Modifiers, navigation, and macros.
Very useful for code mangling.
```
.-----------------------------.        .-----------------------------.
|Enter| Tab |Space|Bspce| Del |        |     |     |     |     |     |
|-----+-----+-----+-----+-----|        |-----+-----+-----+-----+-----|
|Shift| Ctrl| Alt | Cmd |     |        |     |  ←  |  ↑  |  →  |     |
|-----+-----+-----+-----+-----|        |-----+-----+-----+-----+-----|
|Undo | Cut |Copy |Paste|Cmnt |        |     |Dednt|  ↓  |Indnt|     |
.-----------------+-----+-----|        |-----+-----+-----------------.
                  | --- |     |        |Bspce|     |
                  .-----+-----.        .-----+-----.
```
Function layer: F-keys and media control.
```
.-----------------------------.        .-----------------------------.
|     |     |     |     |     |        | F1  | F2  |  F3 | F4  | F5  |
|-----+-----+-----+-----+-----|        |-----+-----+-----+-----+-----|
|     |Vol -|Mute |Vol +|     |        | F6  | F7  | F8  | F9  | F10 |
|-----+-----+-----+-----+-----|        |-----+-----+-----+-----+-----|
|     |Prev |Pause|Next |     |        | F11 | F12 | F13 | F14 | F15 |
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
