# TRAGIC — Terminal Card Game in C

Two-player turn-based card game for the terminal, inspired by Magic: The Gathering.  
Final project for the **C Programming Language** course — Università degli Studi di Perugia.  
**Author:** Luca Capuccini — matricola 347711

---

## Compile & Run

```bash
gcc Main.c Gamelib.c -o tragic
./tragic
```

> Run in a fullscreen terminal for correct ASCII art rendering.

---

## How It Works

Two wizards (20 HP each) take turns drawing and playing cards until one reaches 0 HP or empties their deck. The wizard with more HP at the end wins.

**Setup:** both players choose a name, a class, and a deck size (10–50 cards). Decks are generated randomly and sorted by card HP.

**Each turn:** draw once · play one card · attack up to 4 times · pass.

### Card Types

| Type | Effect |
|------|--------|
| Creature | Placed on field (max 4 slots); attacks enemies |
| Remove Creature | Instantly destroys a target enemy creature |
| Deal Damage | Damages an enemy creature or wizard |
| Heal | Heals your wizard or one of your creatures |

### Wizard Classes

| Class | Bonus applied to deck |
|-------|-----------------------|
| Vita (Life) | Creature cards +50% HP |
| Tenebre (Darkness) | Deal-damage cards ×2 HP |
| Luce (Light) | Heal cards ×3.5 HP |

---

## C Concepts Used

- **Structs & enums** — `struct Carta` (card), `struct Mago` (wizard), `enum Tipo_carta`, `enum Classe_mago`
- **Singly-linked list** — deck implemented as a linked list; cards allocated with `malloc` and freed with `free`
- **Pointer arrays** — hand (`mano[6]`) and battlefield (`campo[4]`) are arrays of `struct Carta*`
- **Dynamic memory** — `malloc`/`free` for every card node; cleanup functions prevent leaks
- **`qsort`** — sorts random HP values before inserting cards into the linked list
- **Variable-length arrays** — deck size set at runtime (`int mazzo[num_carte_mazzo]`)
- **Static variables** — turn counter, draw/play/attack flags persist across function calls
- **Preprocessor macros** — ANSI color codes defined in `Gamelib.h` via `#define`
- **`do-while` + `switch`** — input validation loops and menu dispatch throughout

---

## Files

| File | Role |
|------|------|
| `Main.c` | Entry point, main menu loop |
| `Gamelib.c` | All game logic (~2160 lines) |
| `Gamelib.h` | Structs, enums, color macros, declarations |
