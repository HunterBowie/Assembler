
class ASMSyntaxError(Exception):
    """Raised when assembly language has syntax error."""

class ASMMemoryError(Exception):
    """Raised when assembly language has a memory error."""

class ASMNameError(Exception):
    """Raised when assembly language has unrecognized variable/label/def name."""

class ASMImportNotFoundError(Exception):
    """Raised when assembly language finds no such file to import."""
