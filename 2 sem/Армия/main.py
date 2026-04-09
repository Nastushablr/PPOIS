# main.py
from __future__ import annotations

from cli import CommandProcessor


def main() -> None:
    processor = CommandProcessor()
    processor.run()


if __name__ == "__main__":
    main()
