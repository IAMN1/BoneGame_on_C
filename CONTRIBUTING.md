<p align="center">
  <a href="README.md">← Back to the README</a> ·
  <b>English</b> · <a href="CONTRIBUTING.ru.md">Русский</a>
</p>

# Contributing

This repository has an unusual rule, so it is worth stating plainly before you spend an evening
on a patch.

## The 2017 code is frozen

`BoneMachine.c` is an artefact, not a codebase. It is kept exactly as a tenth-grader left it on
18 May 2017, because a cleaned-up version would be a different and much less interesting thing.

That means pull requests which **improve the game** will be declined — with genuine thanks, but
declined. Specifically:

- replacing the `goto` navigation with a state machine,
- merging `Game_Mode_1` and `Game_Mode_2`,
- fixing `while (!Button_Click(a) || !Button_Click(b))`,
- giving `Mouse_Regs()` a return value,
- balancing the payouts so the house stops losing,
- reformatting, renaming, or modernising anything.

Every one of those is a real defect and every one of them is documented in
[docs/CODE-TOUR.md](docs/CODE-TOUR.md). Being catalogued is the job they do here.

The single exception: the author's real name was removed from the header comment. Nothing else
in the file has been touched, and nothing else will be.

## What is welcome

**Ports.** This is the contribution the repository actually wants. `graphics.h`, `dos.h` and
`int86` are the only things standing between this game and any modern platform, and the whole
program is fifteen functions. Put your port in your own repository, open an issue here, and it
gets linked from the README. SDL2, raylib, WebAssembly, the terminal — all of it is interesting.

**Documentation fixes.** If a line number has drifted, a claim is wrong, or an instruction does
not work on your machine, that is a bug in this repository and a pull request is the right
answer. The documentation makes specific factual claims — 1344 lines, 42.1%, fifteen functions —
and they should all hold up.

**Translations.** Currently English and Russian. To add a language:

1. Copy `README.md` to `README.<code>.md` using the ISO 639-1 code — `README.de.md`,
   `README.ja.md`, `README.pt-BR.md`.
2. Do the same for `docs/RUN.md` and `docs/CODE-TOUR.md`.
3. Add your language to the switcher line at the top of every existing file, in the same
   `English · Русский` style, so all versions stay reachable from all the others.
4. Keep the numbers and the code identifiers untranslated.

**Trouble running it.** Open an issue. Turbo C++ under DOSBox fails in a small number of ways
and [docs/RUN.md](docs/RUN.md) should cover all of them; if it missed yours, that is worth
knowing.

## The screenshots

The images in `docs/media/` are not photographs of a running emulator. They were reconstructed
from the BGI coordinates in the source — the same `bar3d`, `line` and `outtextxy` calls the
program makes — so if one of them disagrees with the code, the image is wrong. Open an issue
with the function and the line numbers.

## Pull request checklist

- One topic per pull request.
- Say which files you changed and why in the description.
- If you changed a factual claim, say where you checked it.
- Do not reformat files you did not otherwise need to touch.
