# TRAGIC — Terminal Card Game in C

A two-player turn-based card game for the terminal, written entirely in C.  
Developed as a final project for the **C Programming Language** course at the  
**Università degli Studi di Perugia** (Bachelor's degree).

**Author:** Luca Capuccini — matricola 347711

---

## Overview

Tragic is inspired by trading card games like Magic: The Gathering. Two wizards
duel each other on a windy plain near Ravnika, the City of Guilds. Each wizard
casts spells represented by a deck of cards. The last wizard standing — or the
one with more HP when the deck runs out — wins.

All interaction happens through numbered menus in the terminal, with ANSI color
output and an ASCII art title screen.

---

## Files

| File | Description |
|------|-------------|
| `Main.c` | Entry point. Drives the main menu loop. |
| `Gamelib.c` | All game logic: deck building, combat, card effects, I/O. |
| `Gamelib.h` | Structs, enums, ANSI color macros, and function declarations. |

---

## Data Structures

### `struct Carta` (Card)
A singly-linked list node representing a single card.

```c
struct Carta {
    enum Tipo_carta tipo;      // card type
    int             pv_carta;  // hit points / power value
    struct Carta   *carta_successiva;
};
```

### `struct Mago` (Wizard)
Represents one of the two players.

```c
struct Mago {
    char            nome_mago[256];  // player name
    unsigned short  pv_mago;         // wizard HP (starts at 20, max 100)
    enum Classe_mago classe;         // chosen class
    struct Carta   *inizio_mazzo;    // head of deck (linked list)
    struct Carta   *fine_mazzo;      // tail of deck
    struct Carta   *mano[6];         // hand: up to 6 cards
    struct Carta   *campo[4];        // battlefield: up to 4 slots
};
```

### `enum Tipo_carta` — Card Types

| Type | Italian name | Effect |
|------|-------------|--------|
| `creatura` | Creatura | Placed on the field; attacks opponents each turn |
| `rimuovi_creatura` | Rimuovi Creatura | Instantly destroys a target enemy creature |
| `infliggi_danno` | Infliggi Danno | Deals damage to an enemy creature or wizard |
| `guarisci_danno` | Guarisci Danno | Heals the wizard or one of their creatures |

### `enum Classe_mago` — Wizard Classes

Each wizard picks a class before the game. The class modifies card values in
their deck at setup time:

| Class | Italian | Bonus |
|-------|---------|-------|
| `vita` | Vita (Life) | All creature cards receive +50% HP |
| `tenebre` | Tenebre (Darkness) | All deal-damage cards receive ×2 HP |
| `luce` | Luce (Light) | All heal cards receive ×3.5 HP |

---

## How to Compile

Requires a C compiler with C99 or later support (e.g. GCC or Clang).

```bash
gcc Main.c Gamelib.c -o tragic
./tragic
```

> Run in a **fullscreen terminal** for correct ASCII art rendering.

---

## Gameplay

### Main Menu

```
1] Imposta Gioco   — Set up the game (names, classes, decks)
2] Combatti        — Start the battle
3] Termina Gioco   — Quit and free memory
4] Storia          — Lore/backstory
5] Regole          — Game rules
6] Trailer Tragic  — Link to the trailer video
```

### Setup Phase (`Imposta Gioco`)

1. Both players enter their wizard names.
2. Each player selects a class: **Tenebre**, **Vita**, or **Luce**.
3. Choose deck size (10–50 cards).
4. Decks are generated automatically:
   - Card HP values are drawn randomly in the range **1–8**.
   - Mago1's deck is sorted ascending; Mago2's descending.
   - Card types are assigned randomly with weighted probabilities:
     - 40% Creature
     - 25% Remove Creature
     - 20% Deal Damage
     - 15% Heal
   - Class bonuses are then applied to the entire deck.

### Battle Phase (`Combatti`)

- The first player to act is chosen randomly.
- Each player starts with **5 cards** drawn from their deck.
- On each turn, the active player can (in any order):

  | Action | Limit per turn |
  |--------|---------------|
  | Draw a card from deck | Once |
  | Play a card from hand | Once |
  | Attack with a creature | Up to 4 times |
  | Pass turn | Ends the turn |
  | Print hand / field / HP | Unlimited |

### Card Play Rules

- **Creature**: placed in a free field slot (max 4). Stays until destroyed.
- **Remove Creature**: immediately destroys a target enemy creature, then is discarded.
- **Deal Damage**: targets either an enemy creature or the enemy wizard directly (only if no enemy creatures are on the field), then is discarded.
- **Heal Damage**: heals either the wizard (capped at 100 HP) or a friendly creature, then is discarded.

### Combat Rules

A creature can attack:
- **An enemy creature** (always allowed if you have creatures on the field).
- **The enemy wizard directly** (only if the enemy field is empty).

Creature vs. creature resolution:
- Attacker HP > Defender HP → defender dies, attacker loses the defender's HP.
- Equal HP → both die.
- Attacker HP < Defender HP → attacker dies, defender loses the attacker's HP.

### Win Condition

The battle ends when:
- A wizard reaches **0 HP** → that wizard loses immediately.
- A wizard's **deck runs out** → the wizard with more HP wins.
- In case of equal HP → draw.

---

## Project Structure

```
Tragic-game-card/
├── Main.c       # main(), menu loop
├── Gamelib.h    # types, structs, ANSI color macros, declarations
└── Gamelib.c    # all game functions (~2160 lines)
```

### Key functions in `Gamelib.c`

| Function | Purpose |
|----------|---------|
| `imposta_gioco()` | Full setup flow: names, classes, deck generation |
| `combatti()` | Main game loop, turn management |
| `gioca_carta()` | Plays a card from hand and resolves its effect |
| `attacca()` | Resolves creature attacks |
| `pesca()` | Draws one card from the deck into the hand |
| `effetto_classe()` | Applies class bonuses to the deck |
| `inserisci_tipi_carte()` | Randomly assigns card types across the deck |
| `inserisci_carta()` | Appends a card node to the deck linked list |
| `delete_mazzo/mano/campo()` | Memory cleanup after the game |

---

## Technical Notes

- Dynamic memory allocation (`malloc` / `free`) is used for every card node.
- The deck is a **singly-linked list**; hand and battlefield are fixed-size pointer arrays.
- `qsort` from `<stdlib.h>` is used to sort card HP values before building the linked list.
- `srand(time(NULL))` seeds randomness once at setup.
- ANSI escape codes (`\e[...m`) provide colored output — defined as macros in `Gamelib.h`.

---

## Course Information

- **University:** Università degli Studi di Perugia
- **Degree:** Bachelor's (Triennale)
- **Course:** C Programming Language
- **Academic Year:** 2023/2024
