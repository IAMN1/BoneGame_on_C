<p align="center">
  <a href="../README.md">← Back to the README</a> ·
  <b>English</b> · <a href="CODE-TOUR.ru.md">Русский</a>
</p>

# A tour of the code

1344 lines of C in a single file, written in 2017 by someone who had just discovered that
`graphics.h` existed. This is a walk through how it actually works — the interrupt handling,
the redraw model, the `goto` graph — and an honest account of what is wrong with it.

Nothing here has been fixed. The point of the repository is the code as it was.

## The map

| Line | Function | What it does |
|---|---|---|
| [48](../BoneMachine.c#L48) | `main` | Boots the graphics mode, then *is* the menu — 367 lines of it |
| [417](../BoneMachine.c#L417) | `Begin_1` | Eleven title letters, scattered across the screen |
| [481](../BoneMachine.c#L481) | `Begin_2` | The same letters, in formation: `The Bone Game` |
| [545](../BoneMachine.c#L545) | `Button` | Fill, frame and label — the one real abstraction in the file |
| [551](../BoneMachine.c#L551) | `Shadow_Button` | A black rectangle behind a button. That is the whole 3D effect |
| [556](../BoneMachine.c#L556) | `Graphics_Fon` | The tiled backdrop: squares, triangles, and the menu panel |
| [649](../BoneMachine.c#L649) | `Graphics_Submenu` | A wider panel, for the "do you wish to exit?" dialog |
| [655](../BoneMachine.c#L655) | `Countdown_C4` | Three, two, one, `BOOM`. Runs before every single round |
| [734](../BoneMachine.c#L734) | `Head_Machine_On` | The face: two eyes, two pupils, two eyelids, a nose |
| [765](../BoneMachine.c#L765) | `Game_Mode_1` | Guess one number. 240 lines |
| [1007](../BoneMachine.c#L1007) | `Game_Mode_2` | Guess two numbers. The same 240 lines |
| [1256](../BoneMachine.c#L1256) | `Loading` | A spinning wireframe logo, three times round |
| [1316](../BoneMachine.c#L1316) | `Mouse_Regs` | Reads the DOS mouse through interrupt `0x33` |
| [1327](../BoneMachine.c#L1327) | `Button_Click` | Is the pointer inside this box *and* is the button down? |
| [1336](../BoneMachine.c#L1336) | `Button_Aiming` | Is the pointer inside this box? — the hover test |

Fifteen functions, and eleven of them take no arguments, because everything they need is a
global: `balance`, `Random1..3`, `mode1`, `mode2`, `punkt`.

## Booting into 640×480

```c
int gdriver = DETECT, gmode;
initgraph(&gdriver, &gmode, "c:\\turboc3\\bgi");
```

`DETECT` asks BGI to pick the best mode the card supports, which on anything VGA means
640×480 with 16 colours. The third argument is where the driver files live, and it is
hardcoded — this single line is why the game will not start on a machine that keeps Turbo C++
anywhere but `C:\TURBOC3`. ([How to fix it](RUN.md#the-bgi-error).)

Right under the includes there is a small piece of good sense:

```c
int colorR = 4, colorG = 2, colorB = 1, colorC = 3, colorM = 5;
int colorLG = 10, colorLB = 9, colorW = 15;
```

Those are the EGA palette indices, given names. The rest of the file mixes them freely with
BGI's own `WHITE`, `DARKGRAY` and `LIGHTBLUE` constants — which are the same numbers — so the
same colour is written two different ways depending on the mood of the afternoon.

## How anything gets drawn

There is no framebuffer, no sprite, no dirty-rectangle tracking. There is `cleardevice()` and
then a few dozen calls that put shapes on the screen. Every visual in the game is one of five
primitives:

| Call | Used for |
|---|---|
| `bar3d(x1,y1,x2,y2,depth,top)` | Every button, every eye, every block. `depth` gives the 3D edge |
| `bar(x1,y1,x2,y2)` | Flat fills: the mouth, the teeth, the C4 casing |
| `line` / `rectangle` / `circle` | The loading logo, the keypad grid, the wiring on the bomb |
| `floodfill(x,y,border)` | Colours in the 3D faces `bar3d` leaves as outlines |
| `outtextxy(x,y,s)` | All text, on an 8×8 grid scaled by `settextstyle` |

Animation is the same trick every time: draw the thing, `delay()`, draw over it. The mouth
changing from a grin to a grimace is literally a red `bar()` painted on top of a green one,
followed by eight white rectangles for the teeth and six black lines to separate them
([765–850](../BoneMachine.c#L765-L850)).

The loading screen is the most ambitious piece of motion in the file. Two x-coordinates walk
toward each other, eight lines are drawn from them into fixed points inside a circle, and when
either coordinate reaches the far side both snap back to their starting posts:

```c
xl1 += 10; xl2 -= 10;
/* ...eight line() calls using xl1 and xl2... */
if (xl1 >= 405 || xl2 <= 230) { xl1 = 230; xl2 = 405; }
```

The result is a star that opens, collapses through a single vertical line, and opens again.

## The mouse is an interrupt

There is no event loop and no callback. There is DOS interrupt `0x33`, called by hand:

```c
int Mouse_Regs(void) {
   regs.x.ax = 1; int86(0x33, &regs, &regs);   /* show the cursor       */
   regs.x.ax = 3; int86(0x33, &regs, &regs);   /* read position+buttons */
   delay(30);
   regs.x.ax = 2; int86(0x33, &regs, &regs);   /* hide the cursor       */
}
```

Function 3 leaves the pointer's x in `regs.x.cx`, its y in `regs.x.dx`, and the button state in
`regs.x.bx`. `Button_Click` and `Button_Aiming` then read those globals without touching the
interrupt again — which is why every interaction loop in the game starts by calling
`Mouse_Regs()` to refresh them.

That `delay(30)` sets the input rate at roughly 33 polls a second, and it is also why the
cursor visibly flickers: it is shown and hidden once per poll.

Two things to notice. `Mouse_Regs` is declared `int` and returns nothing at all — Turbo C++
compiled it without complaint. And hover is a separate function from click, differing only by
`&& regs.x.bx == 1`, which is a genuinely reasonable way to split the problem.

## The menu is a graph of gotos

`main()` runs from [line 48 to line 414](../BoneMachine.c#L48-L414) and is almost entirely
menu. There are three highlighted states, and each one is a full block of drawing calls,
copy-pasted with the coordinates nudged by five pixels. Movement between them is by label:

```
   round: ───────────► mode 1 highlighted ──► Game_Mode_1()
     ▲   ▲                    │ ▲
     │   └────────────────────┼─┘
     │                        ▼
  punkt2: ──────────► mode 2 highlighted ──► Game_Mode_2()
     ▲   ▲                    │ ▲
     │   └────────────────────┼─┘
     │                        ▼
  punkt3: ──────────► exit highlighted
                              │
                              ▼
  round2: ──► "Do you wish to exit the game?" ──► subpunkt1: ──► exit(0)
```

Seven labels in `main`, four more inside the two game modes, and the arrow keys arrive as
`getch()` returning `0` followed by a scan code — `80` for down, `72` for up, `77` and `75` for
right and left, `13` for Enter. Each `case` re-draws the whole menu.

A selection index and a redraw loop would have collapsed the entire thing to about forty lines.
The version that exists works, has been tested by an audience of one classroom, and is
completely impossible to modify without breaking something.

## One round, start to finish

Both game modes follow the same eight steps ([`Game_Mode_1`](../BoneMachine.c#L765)):

1. Ask for a balance with `scanf`, and loop while it is `<= 0`.
2. Ask for a number, and loop while it is outside 1–6. This is the entire input validation.
3. `Countdown_C4()` — detonate the bomb.
4. `Head_Machine_On()` — draw the face.
5. Roll three times with `random(6)+1`, and draw each result with a six-case `switch`,
   one `case` per die face, each calling `outtextxy` with a different string literal.
6. Compare, then paint the mouth green or red.
7. Adjust the balance: `+150` or `-30`.
8. Wait for `RETRY` or `EXIT`, and `goto again_mod_1` or fall through to the statistics screen.

Step 5 is the memorable one. The three rolls are not drawn on dice; they are drawn at
`(205,135)`, `(445,135)` and `(325,220)` — which are, respectively, the left pupil, the right
pupil and the nose. The machine's face *is* the reel display, and nothing in the code says so.

## The bugs worth knowing about

**The wait loops can never end on their own.**

```c
while (!Button_Click(180,420,300,440) || !Button_Click(360,420,480,440)) {
```

The pointer cannot be inside both buttons at once, so at least one call returns `0`, its
negation is `1`, and the condition is always true. Every one of these loops is exited by an
explicit `break` or `goto` in its body. Replacing `||` with `&&` would have been correct; the
code works anyway, for the wrong reason.

**The two game modes are one function typed twice.** [765–1006](../BoneMachine.c#L765-L1006)
and [1007–1254](../BoneMachine.c#L1007-L1254) differ by a second `scanf`, three extra terms in
one `if`, and the names of three counters. Roughly a third of the program is a duplicate.

**`randomize()` runs twice.** Once in `main`, and again on every call to `Graphics_Fon` —
which re-seeds from the system clock each time the menu is redrawn.

**The payouts were never checked against the odds.** Mode 1 wins 1 − (5/6)³ = 42.1% of rounds
at `+150` against `-30`, for an expected `+45.8` per round *to the player*. Mode 2 with two
distinct guesses wins 70.4% of the time: `+96.7` a round. The machine cannot be beaten because
it was never trying.

## What it gets right

It is easy to list the mistakes. These are harder to notice, and they are the reason the thing
is still playable nine years later:

- **Buttons are a function.** `Button()` and `Shadow_Button()` were extracted before there was
  any pressure to extract them. That instinct is the whole job.
- **Hover states.** Every button lights up under the pointer, in a program whose author had no
  UI framework to copy the idea from.
- **Two input methods, both complete.** The keyboard path and the mouse path each reach every
  screen. Most first projects manage one.
- **196 lines carry a comment**, in a file where nobody was going to check.
- **It finishes.** There is a title sequence, a menu, two modes, a confirmation dialog, an
  end-of-game statistics screen and a clean `closegraph()`. It is not a demo. It is a program.

<p align="center">
  <sub><a href="../README.md">← Back to the README</a> · <a href="RUN.md">How to run it →</a></sub>
</p>
