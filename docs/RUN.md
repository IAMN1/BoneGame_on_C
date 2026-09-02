<p align="center">
  <a href="../README.md">← Back to the README</a> ·
  <b>English</b> · <a href="RUN.ru.md">Русский</a>
</p>

# Running Bone Machine

The game calls `initgraph`, `int86` and `delay`. All three are DOS, so the fastest route is
still the one from 2017: a DOS emulator with Turbo C++ inside it. Twenty minutes, start to
finish.

## What you need

| | |
|---|---|
| **DOSBox** | [dosbox.com](https://www.dosbox.com) — or the maintained forks, [DOSBox Staging](https://dosbox-staging.github.io) and [DOSBox-X](https://dosbox-x.com). Any of them works |
| **Turbo C++ 3.0** | The Borland IDE. It is abandonware and easy to find; it unpacks to a `TURBOC3` folder |
| **`BoneMachine.c`** | From this repository |

## Setting it up

Make a folder on your own machine to hand to DOSBox — say `~/dos` — and put `TURBOC3` and
`BoneMachine.c` inside it. Then start DOSBox and type:

```
mount c ~/dos
c:
cd turboc3\bin
tc.exe
```

On Windows the first line is `mount c C:\dos` instead. To skip the typing every time, put those
four lines at the end of your `dosbox.conf` under `[autoexec]`.

Inside the Turbo C++ IDE:

1. **File → Open**, and pick `BoneMachine.c`.
2. **Options → Directories** — `Include` must be `C:\TURBOC3\INCLUDE`, `Library` must be
   `C:\TURBOC3\LIB`.
3. **Options → Linker → Libraries** — tick **Graphics library**. This one is not optional,
   and forgetting it is the single most common failure.
4. **Ctrl+F9** to compile and run.

You should get the loading logo, then the title, then the menu. Move with the arrow keys or the
mouse; `Enter` or a click selects.

## When it does not work

### Undefined symbol `_initgraph`

The graphics library is not linked. Go back to step 3 above: **Options → Linker → Libraries →
Graphics library**. Nothing else causes this.

### The BGI error

A black screen, or `BGI Error: Graphics not initialized`, means `initgraph` could not find its
driver. The path is hardcoded in [`BoneMachine.c`](../BoneMachine.c#L55):

```c
initgraph(&gdriver, &gmode, "c:\\turboc3\\bgi");
```

`EGAVGA.BGI` has to be in exactly that folder. Either move your Turbo C++ install to
`C:\TURBOC3`, or edit the string to point wherever it actually is. Note the doubled
backslashes — they are one backslash each once the compiler is done with them.

### The mouse does nothing

DOSBox provides the `INT 33h` mouse itself, so no driver is needed, but the emulator has to
have captured your pointer. Click inside the DOSBox window, or press `Ctrl+F10`. If the cursor
flickers, that is not a bug: [`Mouse_Regs`](../BoneMachine.c#L1316) shows and hides it once per
poll, thirty-three times a second.

### Everything is far too fast, or far too slow

`delay()` measures itself against the CPU at startup, and DOSBox's emulated CPU speed is
adjustable, so the countdown and the loading animation drift with it. `Ctrl+F12` speeds the
emulated CPU up, `Ctrl+F11` slows it down. Around 3000 cycles feels close to the machine this
was written on.

### It will not compile with GCC

It will not, and it cannot without changes. `graphics.h` and `dos.h` are Borland's, and
`int86` talks to real-mode DOS interrupts. Porting means replacing the drawing calls and the
mouse handling — see [Porting it](../README.md#porting-it).

## Playing it

- **Balance** — the game asks for a starting number before the first round. Anything above
  zero works; the game stops when it reaches zero.
- **Guess 1 of 3** — name one number from 1 to 6. Three dice are rolled. If any of them
  matches, `+150`; otherwise `-30`.
- **Guess 2 of 3** — name two numbers. Same three dice, so the odds go up but the payout does
  not change. This is the better mode, by a wide margin.
- **RETRY / EXIT** — after each round. `EXIT` goes to the statistics screen, not out of the
  program.

Both modes read the numbers with `scanf`, which means the input line appears over the graphics
rather than in a box. That is how it looked in 2017 too.

<p align="center">
  <sub><a href="../README.md">← Back to the README</a> · <a href="CODE-TOUR.md">How it works inside →</a></sub>
</p>
