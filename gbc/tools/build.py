# (AI-assisted) Native GB/GBC build entry point.
import runpy
from pathlib import Path
runpy.run_path(str(Path(__file__).with_name("build_shelf.py")),run_name="__main__")
