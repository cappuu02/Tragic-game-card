# ExamBot — Telegram Lecture Booking Bot

A Telegram bot that allows students of the [Department of Mathematics and Computer Science](https://www.dmi.unipg.it/) at the **University of Perugia** to view and book seats for daily lectures, with real-time availability tracking.

> Developed by **Luca Capuccini** and **Edoardo Tommasi** for the *Software Engineering* course — Bachelor's Degree in Computer Science, University of Perugia.

---

## Features

- **Student authentication** — login via 6-digit student ID (*matricola*) and password
- **Daily lecture schedule** — fetched live from the university's room booking system (MRBS)
- **Seat booking** — reserve a seat in a lecture with real-time availability check per classroom
- **Booking cancellation** — cancel an existing reservation, which frees up the seat
- **Capacity enforcement** — each classroom has a defined maximum capacity; bookings are blocked when full

## Tech Stack

| Component | Technology |
|-----------|-----------|
| Bot framework | [pyTelegramBotAPI](https://github.com/eternnoir/pyTelegramBotAPI) |
| Database | SQLite3 |
| Schedule scraping | `requests` + `BeautifulSoup` |
| Language | Python 3 |

## Database Schema

Three tables managed in `database_tg.db`:

- **`freshman`** — student credentials (`matricola`, `password`)
- **`prenotazioni`** — bookings (`matricola`, `lezione`) — primary key on both columns prevents duplicates
- **`posti_prenotati`** — seat counter per lecture (`lezione`, `posti`)

## Bot Commands

| Command | Description |
|---------|-------------|
| `/start` | Start the bot and authenticate with student ID and password |
| `/lista_lezioni` | Show today's lecture schedule with room and time info |
| `/prenotazione_lezioni` | Book a seat in a lecture |
| `/cancella_prenotazione` | Cancel an existing booking |

## How It Works

1. The bot scrapes today's timetable from `servizi.dmi.unipg.it/mrbs` at startup.
2. The student logs in with their *matricola* and password (verified against the `freshman` table).
3. Once authenticated, the student can list available lectures, book one by name, or cancel a previous booking.
4. Before confirming a booking, the bot checks available seats by comparing booked seats against the room's capacity.

## Classroom Capacities

| Room | Capacity |
|------|----------|
| A0 | 180 |
| A2 | 180 |
| I1 | 215 |
| I2 | 90 |
| A3 | 70 |
| Riunioni | 40 |
| B3 | 35 |
| B1 | 30 |
| C3 | 25 |
| C2 | 20 |
| Verde | 18 |
| Gialla | 17 |

## Setup

1. Install dependencies:
   ```bash
   pip install pyTelegramBotAPI requests beautifulsoup4
   ```

2. Set your bot token in `Migliorato.py`:
   ```python
   TOKEN = "your_token_here"
   ```

3. Run the bot:
   ```bash
   python Migliorato.py
   ```
