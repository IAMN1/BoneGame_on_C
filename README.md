<p align="center">
  <img src="docs/media/hero.svg" alt="Bone Machine — a slot machine that rolls dice with its own face" width="820">
</p>

<p align="center">
  <a href="LICENSE"><img src="https://img.shields.io/badge/license-MIT-blue?style=flat-square" alt="MIT licence"></a>
  <img src="https://img.shields.io/badge/language-ANSI%20C-00599C?style=flat-square" alt="ANSI C">
  <img src="https://img.shields.io/badge/built%20with-Turbo%20C%2B%2B%203.0-orange?style=flat-square" alt="Turbo C++ 3.0">
  <img src="https://img.shields.io/badge/graphics-BGI%20640%C3%97480%20%C2%B7%2016%20colours-AA00AA?style=flat-square" alt="BGI, 640x480, 16 colours">
  <img src="https://img.shields.io/badge/written-2017-2ea44f?style=flat-square" alt="Written in 2017">
</p>

<p align="center">
  <b>English</b> · <a href="README.ru.md">Русский</a>
</p>

> A gambling machine with a face, written in C on Turbo C++ in 2017 — by a tenth-grader who
> had not yet heard of functions taking arguments. You bet, you name a number, a brick of C4
> counts down, and the machine rolls three dice **in its own two eyes and its nose**.
> It has been preserved exactly as it was, typos included.

<p align="center">
  <img src="docs/media/demo.gif" alt="One round: loading, title, menu, countdown, and a win" width="640">
</p>

## Quick start

The game needs a DOS machine, so it comes with one.

```
1.  Install DOSBox                    https://www.dosbox.com
2.  Unpack Turbo C++ 3.0 to           C:\TURBOC3        (inside DOSBox)
3.  Drop BoneMachine.c next to it, open it in the IDE, and press Ctrl+F9
```

`initgraph()` looks for the BGI drivers in `c:\turboc3\bgi`, so `EGAVGA.BGI` has to be there —
that is the one thing that goes wrong for everyone. Full walkthrough, including the mouse and
the usual errors: **[docs/RUN.md](docs/RUN.md)**.

## How the game works

You type a starting balance, pick a number from 1 to 6, and watch three dice come up. The dice
are not drawn as dice — they appear inside the machine's face, one per pupil and one on the
nose. Guess right and the mouth turns green and grins; guess wrong and it turns red.

| Mode | You name | You win if | Chance | Balance |
|---|---|---|---|---|
| **Guess 1 of 3** | one number | any of the three rolls matches it | 42.1% | `+150` / `−30` |
| **Guess 2 of 3** | two numbers | any roll matches either of them | 70.4% | `+150` / `−30` |

Which brings us to the best bug in the repository.

### The house loses

The payout is fixed at `+150` for a win and `−30` for a loss, and nobody checked that against
the odds. Mode 1 wins 1 − (5/6)³ = 42.1% of the time, so the expected result of a round is
**+45.8 chips for the player**. Mode 2, with two distinct guesses, wins 1 − (4/6)³ = 70.4% of
the time: **+96.7 per round**.

The machine is not rigged against you. It is rigged *for* you, and it cannot be beaten by
playing badly — only by getting bored. Sixteen-year-old me built a casino that pays rent.

## The screens

Every screen below is reconstructed straight from the BGI coordinates in the source — the same
`bar3d`, `line` and `outtextxy` calls the code makes. No emulator screenshots, no touch-ups.
The one liberty taken is the typeface: BGI's 8×8 bitmap font is stood in for by an ordinary
monospace, on the same eight-pixel grid.

<table>
<tr>
<td width="50%"><img src="docs/media/screen-loading.svg" alt="Loading screen"></td>
<td width="50%"><img src="docs/media/screen-title.svg" alt="Title screen"></td>
</tr>
<tr>
<td><b>Loading.</b> Eight lines swing across a circle and snap back, three times, for no
reason other than that loading screens are what real programs have.</td>
<td><b>Title.</b> Eleven coloured blocks are thrown across the screen, then redrawn in
formation. The 2017 splash still spells out <code>The Bone Game</code>, and it stays that way.</td>
</tr>
<tr>
<td><img src="docs/media/screen-menu.svg" alt="Main menu"></td>
<td><img src="docs/media/screen-countdown.svg" alt="C4 countdown"></td>
</tr>
<tr>
<td><b>Menu.</b> Hand-built buttons with drop shadows and hover states, driven by both the
arrow keys and the mouse. The typo in <code>Gues</code> has been there since 2017.</td>
<td><b>Countdown.</b> Every single round begins by detonating a brick of C4: three, two, one,
a yellow <code>BOOM</code>, a red <code>BOOM</code>.</td>
</tr>
<tr>
<td><img src="docs/media/screen-win.svg" alt="A winning round"></td>
<td><img src="docs/media/screen-lose.svg" alt="A losing round"></td>
</tr>
<tr>
<td><b>A win.</b> The mouth fills green and eight teeth are cut out of it with white
rectangles.</td>
<td><b>A loss.</b> The same mouth in red. This is the entire animation system: draw a
rectangle over the old one.</td>
</tr>
<tr>
<td><img src="docs/media/screen-exit.svg" alt="Exit confirmation dialog"></td>
<td><img src="docs/media/screen-stats.svg" alt="End-of-game statistics"></td>
</tr>
<tr>
<td><b>Leaving.</b> A wider panel over the same backdrop, with the buttons growing and
shrinking as the highlight moves between <code>Yes</code> and <code>No</code>.</td>
<td><b>Statistics.</b> Rounds played, final balance, wins, losses. The only screen where
<code>printf</code> text and BGI drawing share the display.</td>
</tr>
</table>

## Inside the code

| | |
|---|---|
| One file | `BoneMachine.c`, 1344 lines, no headers of its own |
| Functions | 15 — `main` plus 14, and eleven of them take no arguments at all |
| Comments | 196 lines carry one, and the vocabulary slips into transliterated Russian: `Graphics_Fon` is *fon*, background; `punkt` is a menu item |
| Graphics | BGI primitives only: `bar3d`, `line`, `floodfill`, `outtextxy` |
| Mouse | `int86(0x33, …)` — raw DOS interrupts, polled every 30 ms |
| Navigation | `goto`. Seven labels. It is a state machine, if you squint |
| Version | 6.0, dated `18/05/2017 · 21:39` in the header comment |

The 367-line `main()` is a menu drawn three times over, once per highlighted row,
because that was easier than tracking a selection index. Every screen transition is a `goto`
into the middle of another loop. It should not be readable, and yet it is.

A guided walk through the whole thing — the interrupt handling, the redraw model, the
`goto` graph, and the parts that are genuinely clever — is in
**[docs/CODE-TOUR.md](docs/CODE-TOUR.md)**.

## What I would do differently

Not a list of regrets. A list of things the code teaches by doing them the hard way.

- **`goto` instead of state.** Three menu layouts are copy-pasted, one per highlight, and
  jumped between by label. One `int selected` and a redraw loop would have replaced all of it.
- **Two modes, one algorithm.** `Game_Mode_1` and `Game_Mode_2` are ~240 lines each and differ
  by one `scanf` and one `||`. That is roughly a third of the program, duplicated.
- **Six cases to print one digit.** `switch(Random1 = random(6)+1)` has a `case` per face,
  each calling `outtextxy` with a different string literal.
- **Everything is global.** `balance`, the three rolls, the guesses and the menu index all
  live at file scope, so no function needs a parameter and no function can be tested.
- **`Mouse_Regs()` is declared `int` and returns nothing.** Turbo C++ let that through. So did I.
- **Nobody did the arithmetic.** See above: the house loses about 46 chips a round.

## Porting it

`graphics.h` and `dos.h` are Borland's, so this will not build with GCC or Clang — the drawing
calls and the `int86` mouse both need replacing. That makes it a pleasant afternoon project:
the whole game is 15 functions and one screen resolution.

If you port it to SDL2, raylib, WebAssembly or anything else, open an issue or a PR and it
gets linked right here. Ports are the one contribution this repository actively wants; the
2017 code itself stays exactly as it is.

## Licence

[MIT](LICENSE) — take it, learn from it, ship it.

<details>
<summary>The licence this README used to claim</summary>

<br>

**Nostalgia Public License v1.0**

- **May:** feel nostalgic, smile, remember 2016.
- **May:** use the code for teaching — both as an example and as a warning.
- **May:** show a friend and say "this was my first program".
- **May not:** seriously criticise a sixteen-year-old.

Superseded by the MIT licence above, which has the advantage of existing.

</details>

---

<p align="center">
  <sub>Version 6.0 · 18/05/2017 · 21:39 · by <a href="https://github.com/IAMN1">IAMN1</a><br>
  <i>"If this program works, IAMN1 wrote it. If it does not, I have no idea who wrote it."</i><br>
  — the header comment, 2017</sub>
</p>
